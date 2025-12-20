#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdint.h>

#define OVFL_CNT 16

/* desired PI precision in digits */
static unsigned gDigPrec;

/* calculation precision in 4-byte words */
static unsigned gWordPrec;

static pthread_mutex_t gMutex;
static uint32_t *pi;
static unsigned gNextComp;
static unsigned gCompCount;
static unsigned gProgressStep, gNextProgress;

/* To print PI, the calculated value is multiplied several times by 1e9.
 * Products are computed piecewise. Each thread calculates own piece.
 * Overflow value is transferred to next thread.
 */
struct ProdPipeline {
	struct ProdPipeline *prev;	// to get previous PI piece overflow
	unsigned first, prec;		// PI piece to multiply
	uint32_t overflows[OVFL_CNT];
	unsigned ovflGetIdx;
	unsigned ovflPutIdx;
	unsigned ovflCount;
};

/* Adds to sum i-th component of Pi
 * Pi is calculated as:
 *		 pi = 0;
 *		 for(i = 0; i < gCompCount; ++i)
 *			  calc_pi_component(pi, i);
 */
static void calc_pi_component(uint32_t *sum, unsigned i)
{
	int firstnz, p2, j, sumOvl, loc;
	uint32_t dig, dig0, remainders[7], div[7];
	uint64_t dividend, resSum;

	p2 = 29 + 10 * i;
	firstnz = p2 >> 5;
	if( firstnz >= gWordPrec )
		return;
	dig0 = 0x80000000U >> (p2 & 0x1f);

	div[0] = 10 * i + 1;
	div[1] = 2560 * i + 2304;
	div[2] = 32 * i + 8;
	div[3] = 1024 * i + 768;
	div[4] = 40 * i + 12;
	div[5] = 640 * i + 320;
	div[6] = 640 * i + 448;

	resSum = sum[firstnz];
	for(j = 0; j < 7; ++j) {
		if( (i&1) == (j<2) ) {	// dividend is negative
			dividend = ((uint64_t)div[j] << 32) - dig0;
			resSum -= 1LL << 32;
		}else
			dividend = dig0;
		dig = dividend / div[j];
		remainders[j] = dividend - dig * div[j];
		resSum += dig;
	}
	sum[firstnz] = resSum;
	sumOvl = (int32_t)(resSum>>32);
	for(loc = firstnz - 1; sumOvl && loc >= 0; --loc ) {
		resSum = (int64_t)sum[loc] + sumOvl;
		sum[loc] = resSum;
		sumOvl = (int32_t)(resSum>>32);
	}
	while(++firstnz < gWordPrec) {
		resSum = sum[firstnz];
		for(j = 0; j < 7; ++j) {
			dividend = (uint64_t)remainders[j] << 32;
			dig = dividend / div[j];
			remainders[j] = dividend - dig * div[j];
			resSum += dig;
		}
		sum[firstnz] = resSum;
		sumOvl = (int32_t)(resSum>>32);
		for(loc = firstnz - 1; sumOvl && loc >= 0; --loc ) {
			resSum = (int64_t)sum[loc] + sumOvl;
			sum[loc] = resSum;
			sumOvl = (int32_t)(resSum>>32);
		}
	}
}

static void *piPartWorker(void *arg)
{
	uint32_t *pi_part;
	uint64_t sum;
	unsigned num;
	int idx;

	pi_part = calloc(gWordPrec, sizeof(uint32_t));
	while( 1 ) {
		pthread_mutex_lock(&gMutex);
		num = gNextComp;
		if( num < gCompCount ) {
			if( ++gNextComp >= gNextProgress ) {
				fputc('.', stderr);
				gNextProgress += gProgressStep;
			}
		}
		pthread_mutex_unlock(&gMutex);
		if( num == gCompCount )
			break;
		calc_pi_component(pi_part, num);
	}
	pthread_mutex_lock(&gMutex);
	// pi += pi_part
	sum = 0;
	for(idx = gWordPrec - 1; idx >= 0; --idx)
		pi[idx] = sum = (sum >> 32) + pi[idx] + pi_part[idx];
	pthread_mutex_unlock(&gMutex);
	free(pi_part);
	return NULL;
}

static void *printPiWorker(void *arg)
{
	struct ProdPipeline *pp = arg;
	uint32_t overflow;
	uint64_t sum;
	int idx, digitsRemain;

	for(digitsRemain = gDigPrec; digitsRemain >= 0; digitsRemain -= 9) {
		if( pp->prev ) {
			int isReady = 0;
			while( ! isReady ) {
				pthread_mutex_lock(&gMutex);
				isReady = pp->prev->ovflCount > 0;
				if( isReady ) {
					overflow = pp->prev->overflows[pp->prev->ovflGetIdx];
					if( ++pp->prev->ovflGetIdx == OVFL_CNT )
						pp->prev->ovflGetIdx = 0;
					--pp->prev->ovflCount;
				}
				pthread_mutex_unlock(&gMutex);
			}
		}else
			overflow = 0;
		sum = (uint64_t)overflow << 32;
		for(idx = pp->first + pp->prec-1; idx >= pp->first; --idx)
			pi[idx] = sum = 1000000000ULL * pi[idx] + (sum >> 32);
		overflow = sum >> 32;
		if( pp->first == 1 ) {
			if( digitsRemain > 9 ) {
				printf("%09u", overflow);
			}else{
				char buf[12];
				sprintf(buf, "%09u", overflow);
				printf("%.*s\n", digitsRemain, buf);
			}
		}else{
			int isReady = 0;
			while( ! isReady ) {
				pthread_mutex_lock(&gMutex);
				isReady = pp->ovflCount < OVFL_CNT;
				if( isReady ) {
					pp->overflows[pp->ovflPutIdx] = overflow;
					if( ++pp->ovflPutIdx == OVFL_CNT )
						pp->ovflPutIdx = 0;
					++pp->ovflCount;
				}
				pthread_mutex_unlock(&gMutex);
			}
		}
	}
	return NULL;
}

int main(int argc, char *argv[])
{
	pthread_t *threads;
	struct ProdPipeline *pp;
	struct timeval tm_beg, tm_end, tm_diff;
	unsigned i, threadCount, argno;
	int isSingleThreaded = 0, isPrintingSingle = 0;

	for(argno = 1; argno < argc && argv[argno][0] == '-'; ++argno) {
		for(i = 1; argv[argno][i]; ++i) {
			if( argv[argno][i] == '1' )
				isSingleThreaded = 1;
			else if( argv[argno][i] == 'P' )
				isPrintingSingle = 1;
		}
	}
	if( argno == argc ) {
		fprintf(stderr, "usage:\n");
		fprintf(stderr, "   pi [-1] [-P] <thousands of digits>\n\n");
		fprintf(stderr, "options:\n");
		fprintf(stderr, "   -1		- single threaded\n");
		fprintf(stderr, "   -P		- print using one thread\n\n");
		return 0;
	}
	gDigPrec = 1000 * atoi(argv[argno]);
	if( gDigPrec < 1 || gDigPrec > 10000000 ) {
		fprintf(stderr, "  argument out of range\n");
		return 1;
	}
	// 104/1000 ~= 1/log(2^32)
	gWordPrec = gDigPrec * 104 / 1000 + 2;
	gCompCount = (32 * gWordPrec + 11) / 10;
	// expression: 2560 * gCompCount + 2304 cannot exceed UINT_MAX
	if( gCompCount > 1677721 ) {
		fprintf(stderr, "precision too big\n");
		return 1;
	}
	gettimeofday(&tm_beg, NULL);
	pthread_mutex_init(&gMutex, NULL);
	gProgressStep = gCompCount / 81;
	gNextProgress = gCompCount - 80 * gProgressStep + 1;
	threadCount = isSingleThreaded ? 1 : sysconf(_SC_NPROCESSORS_ONLN);
	if( threadCount >= gWordPrec )
		threadCount = gWordPrec - 1;
	pp = malloc(threadCount * sizeof(struct ProdPipeline));
	pi = calloc(gWordPrec, sizeof(uint32_t));
	threads = malloc((threadCount-1) * sizeof(pthread_t));
	for(i = 1; i < threadCount; ++i)
		pthread_create(threads + i - 1, NULL, piPartWorker, NULL);
	piPartWorker(pp);
	for(i = 1; i < threadCount; ++i)
		pthread_join(threads[i-1], NULL);
	fprintf(stderr, "\n");
	if( isPrintingSingle )
		threadCount = 1;
	for(i = 0; i < threadCount; ++i) {
		pp[i].first = 1 + (i * (gWordPrec-1)) / threadCount;
		pp[i].prec = ((i+1) * (gWordPrec-1)) / threadCount -
			(i*(gWordPrec-1)) / threadCount;
		pp[i].prev = i == threadCount - 1 ? NULL : pp + i + 1;
		pp[i].ovflGetIdx = 0;
		pp[i].ovflPutIdx = 0;
		pp[i].ovflCount = 0;
	}
	for(i = 1; i < threadCount; ++i)
		pthread_create(threads + i - 1, NULL, printPiWorker, pp + i);
	printf("%u.", pi[0]);
	printPiWorker(pp);
	for(i = 1; i < threadCount; ++i)
		pthread_join(threads[i-1], NULL);
	free(pp);
	free(pi);
	free(threads);
	gettimeofday(&tm_end, NULL);
	timersub(&tm_end, &tm_beg, &tm_diff);
	fprintf(stderr, "exec time: %.3f s\n",
			tm_diff.tv_sec + (tm_diff.tv_usec/1000000.0));
	return 0;
}

