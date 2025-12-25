import math

def isPrime(n):
    if n < 2:
        return False
    for i in range(2, int(math.sqrt(n)) + 1):
        if n % i == 0:
            return False
    return True

if __name__ == "__main__":
    num = int(input('输入一个数字：'))
    if isPrime(num):
        print(f"{num} 是质数")
    else:
        print(f"{num} 不是质数")