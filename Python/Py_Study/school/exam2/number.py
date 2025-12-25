n = input("输入5位数：")
print(n)

if n == n[::-1]:
    print(f"{n} 是回文数")
else:
    print(f"{n} 不是回文数")

