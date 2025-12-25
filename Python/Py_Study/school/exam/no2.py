import time
print("-----执行开始----")
for i in range(0, 101, 10):
    stars = '*' *(i // 10)
    b = '.' * (10 -(i // 10))
    print(f"{i}%[{stars+'->'+ b}]")
    time.sleep(0.1/1000)

print("-----执行结束----")
