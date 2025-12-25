s=input("")
if s[0:3]in['RMB']:
    U=eval(s[3:])/6.78
    print("USD{:.2f}".format(U))
elif s[0:3] in['USD']:
    R=eval(s[3:])*6.78
    print("RMB{:.2f}".format(R))
else:
    print("输入格式错误")
