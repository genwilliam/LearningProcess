def is_ji(n):
    if n <= 0:
        return 0
    if n % 2 == 1:
        return n + is_ji(n - 2)
    else:
        return is_ji(n - 1)

if __name__ == '__main__':
    n = int(input())
    result = is_ji(n)
    print(f"1~{n}的奇数和是{result}")