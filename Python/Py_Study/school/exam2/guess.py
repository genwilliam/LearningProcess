import random

secret = random.randint(1, 1000)

count = 0

while True:
    guess_str = input("请输入你猜的数字：")

    if not guess_str.isdigit():
        print("请输入有效的整数！")
        continue

    guess = int(guess_str)
    count += 1

    if guess < secret:
        print("猜小了")
    elif guess > secret:
        print("猜大了")
    else:
        print(f"猜对了！答案是 {secret}")
        print(f"你总共猜了 {count} 次。")
        break

