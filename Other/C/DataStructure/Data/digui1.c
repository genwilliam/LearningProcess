#include <stdio.h>
/* 递归实现阶乘函数 */

// 定义Factorial函数
long int Factorial(int N) {
    if (N <= 1) {
        return 1;
    } else {
        return N * Factorial(N - 1);
    }
}

int main() {
    // 在main函数中调用Factorial函数
    int N = 10;
    printf("The factorial of %d is %ld\n", N, Factorial(N));
    return 0;
}