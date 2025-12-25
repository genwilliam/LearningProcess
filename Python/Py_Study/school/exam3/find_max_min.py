def find_max_min(*args):
    if not args:
        return None

    max_val = args[0]
    min_val = args[0]

    # 遍历
    for num in args[1:]:
        if num > max_val:
            max_val = num
        if num < min_val:
            min_val = num
    return max_val, min_val

if __name__ == '__main__':
    args = input("请输入数字，用空格分开: ").split()

    # 转成列表
    numbers = [int(x) for x in args]

    result = find_max_min(*numbers)  # 用 * 将列表拆开传入函数
    print(result)