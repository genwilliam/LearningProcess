/* 
 *  Short program to dump digits using the native binary TPI format 
 *
 *  (c) Copyright 2010 Fabrice Bellard 
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
*/
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <errno.h>

/* Note: compiled using gcc for Linux and Mingw for Windows */

#ifdef _WIN32
/* XXX: add 64 bit file support for Windows */
#define fseeko fseek
#endif

static inline int64_t min_int64(int64_t a, int64_t b)
{
    if (a < b)
        return a;
    else
        return b;
}

/* MPT file reader */

#define BASE10_EXP 19

typedef struct mpt_disk_header_t {
    uint8_t magic[8];
    uint64_t len;
    uint64_t allocated_len;
    uint64_t type;
    uint64_t negative; /* mpz, mpf */
    uint64_t base; /* mpz, mpf (XXX: not used yet) */
    int64_t expn; /* mpf */
} mpt_disk_header_t;

typedef struct {
    FILE *f;
    mpt_disk_header_t h;
    int base;
    uint64_t *buf;
    int64_t buf_pos, buf_len;
    int64_t pos;
    int start_digit;
    int base2_exp, base2_mask;

    /* digit parser */
    int cur_digit;
    uint64_t cur_limb2;
    uint8_t cur_limb10[BASE10_EXP];
} MPTReader;

static const uint8_t mpt_magic[8] = "MPT\1FILE";

#define MPT_TYPE_MPZ 1
#define MPT_TYPE_MPF 2

#define MPT_DISK_HEADER_SIZE 4096

#define MPT_MAX_BUF_LEN (1024 * 1024)

void mpt_reader_close(MPTReader *s)
{
    if (s->f)
        fclose(s->f);
    free(s->buf);
    free(s);
}

MPTReader *mpt_reader_open(const char *filename, int base, int64_t start_pos)
{
    MPTReader *s;
    int digits_per_limb;

    if (base != 10 && base != 2 && base != 16)
        return NULL;

    s = malloc(sizeof(MPTReader));
    if (!s)
        return NULL;
    memset(s, 0, sizeof(*s));

    s->f = fopen(filename, "rb");
    if (!s->f) 
        goto fail;
    if (fread(&s->h, 1, sizeof(s->h), s->f) != sizeof(s->h))
        goto fail;
    if (memcmp(s->h.magic, mpt_magic, 8) != 0)
        goto fail;
    if (s->h.type != MPT_TYPE_MPF)
        goto fail;
    if (s->h.expn < 0)
        goto fail;
    if (base == 10) {
        digits_per_limb = BASE10_EXP;
    } else {
        s->base2_exp = 1;
        while ((1 << s->base2_exp) != base)
            s->base2_exp++;
        digits_per_limb = 64;
        s->base2_mask = (1 << s->base2_exp) - 1;
        start_pos *= s->base2_exp;
    }
    s->base = base;
    s->buf = malloc(sizeof(uint64_t) * MPT_MAX_BUF_LEN);
    s->buf_len = 0;
    s->buf_pos = 0;
    s->pos = s->h.len - s->h.expn - (start_pos / digits_per_limb);
    if (s->pos <= 0)
        goto fail;
    s->start_digit = start_pos % digits_per_limb;
    return s;
 fail:
    mpt_reader_close(s);
    return NULL;
}

int mpt_reader_fill(MPTReader *s)
{
    int64_t len;
    len = min_int64(s->pos, MPT_MAX_BUF_LEN);
    if (len == 0)
        return -1;
    s->pos -= len;
    fseeko(s->f, MPT_DISK_HEADER_SIZE + s->pos * sizeof(uint64_t), SEEK_SET);
    if (fread(s->buf, 1, len * sizeof(uint64_t), s->f) != 
        (len * sizeof(uint64_t)))
        abort();
    s->buf_len = len;
    s->buf_pos = len;
    return 0;
}

static inline int mpt_reader_get_digit(MPTReader *s)
{
    if (s->base == 10) {
        if (s->cur_digit == 0) {
            uint64_t a;
            int i;
            if (s->buf_pos == 0) {
                if (mpt_reader_fill(s))
                    return -1;
            }
            s->buf_pos--;
            /* extract base 10 digits */
            a = s->buf[s->buf_pos];
            for(i = 0; i < BASE10_EXP; i++) {
                s->cur_limb10[i] = a % 10;
                a /= 10;
            }
            s->cur_digit = BASE10_EXP - s->start_digit;
            s->start_digit = 0;
        }
        s->cur_digit--;
        return s->cur_limb10[s->cur_digit];
    } else {
        if (s->cur_digit == 0) {
            if (s->buf_pos == 0) {
                if (mpt_reader_fill(s))
                    return -1;
            }
            s->buf_pos--;
            s->cur_limb2 = s->buf[s->buf_pos];
            s->cur_digit = 64 - s->start_digit;
            s->start_digit = 0;
        }
        s->cur_digit -= s->base2_exp;
        return (s->cur_limb2 >> s->cur_digit) & s->base2_mask;
    }
}

int mpt_reader_getc(MPTReader *s)
{
    int c;
    c = mpt_reader_get_digit(s);
    if (c < 0)
        return c;
    if (c < 10)
        c += '0';
    else
        c += 'A' - 10;
    return c;
}

void dump_digits(const char *filename, int base, int64_t pos, int64_t n)
{
    MPTReader *s;
    int64_t i;
    int c;

    s = mpt_reader_open(filename, base, pos - 1);
    if (!s) {
        fprintf(stderr, "%s: cannot display at this position\n", filename);
        exit(1);
    }
    for(i = 0; i < n; i++) {
        c = mpt_reader_getc(s);
        if (c < 0)
            break;
        putchar(c);
        if ((i % 10) == 9 && i != (n - 1))
            putchar(' ');
    }
    mpt_reader_close(s);
}

int main(int argc, char **argv)
{
    int64_t pos, n;
    const char *filename;
    int base;

    if (argc < 4) {
        printf("usage: tpidump filename base pos [nb_digits]\n"
               "\n"
               "Dump digits using tpi internal floating point format\n"
               "Example to display 50 digits starting from position 1:\n"
               "tpidump pi_base10 10 1\n"
               );
        exit(1);
    }

    filename = argv[1];
    base = atoi(argv[2]);
    pos = strtod(argv[3], NULL);
    if (argc >= 5) 
        n = atoi(argv[4]);
    else
        n = 50;
    dump_digits(filename, base, pos, n);
    printf("\n");
    return 0;
}

