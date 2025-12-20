#include <stdio.h>

// 递归斐波那契函数
long int Fib(int N)
{
    if (N <= 1)
        return N;
    else
        return Fib(N - 1) + Fib(N - 2);
}

int main()
{
    int N = 10;
    printf("%ld", Fib(N));  // 使用 %ld 格式化长整型
    return 0;
}