char = input("请输入一行字符：")

letters = 0   # 英文字母
number = 0    # 数字
spaces = 0    # 空格
others = 0    # 其他字符

# 遍历每个字符进行分类统计
for c in char:
    if c.isalpha():
        letters += 1
    elif c.isdigit():
        number += 1
    elif c.isspace():
        spaces += 1
    else:
        others += 1

# 输出结果
print(f"英文字符：{letters}")
print(f"数字字符：{number}")
print(f"空格字符：{spaces}")
print(f"其他字符：{others}")

