import math

def PrimeList(N):
    primes = []
    for num in range(2, N):  # 从2开始到N-1
        is_prime = True
        for i in range(2, int(math.sqrt(num)) + 1):
            if num % i == 0:
                is_prime = False
                break
        if is_prime:
            primes.append(num)
    return primes

if __name__ == "__main__":
    N = int(input("请输入一个整数N: "))
    prime_numbers = PrimeList(N)
    print(" ".join(map(str, prime_numbers)))