def p_loop(x, y):
    result = 1
    for _ in range(y):
        result *= x
    return result

if __name__ == "__main__":
    x = float(input('输入x: '))
    y = int(input('输入y: '))
    print(p_loop(x, y))