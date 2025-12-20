#include <stdio.h>
#include <stdlib.h>

int Num_P, Num_S, Max[100][100], Allocation[100][100], Need[100][100], Available[100],
Work[100], Security[100];

char Name[100];

void init() {
    int i, j;

    // 输入可用资源种类数量
    printf("请输入可用资源的种类数量：");
    scanf_s("%d", &Num_S);

    // 输入每种资源的名称和初始数量
    for (i = 0; i < Num_S; i++) {
        printf("请输入第 %d 个可用资源的名称: ", i + 1);
        scanf_s(" %c", &Name[i], 1);  // 注意使用 " %c" 来防止换行符干扰输入
        printf("请输入初始可用资源 %c 的数量: ", Name[i]);
        scanf_s("%d", &Available[i]);
    }

    // 输入进程数量
    printf("\n请输入进程的数量：");
    scanf_s("%d", &Num_P);

    // 输入进程的 Max 矩阵
    printf("请输入进程的 Max 矩阵：\n");
    for (i = 0; i < Num_P; i++) {
        for (j = 0; j < Num_S; j++) {
            scanf_s("%d", &Max[i][j]);
        }
    }

    // 输入进程的 Allocation 矩阵
    printf("请输入进程的 Allocation 矩阵：\n");
    int temp[100] = { 0 }; // 用于统计资源分配情况
    for (i = 0; i < Num_P; i++) {
        for (j = 0; j < Num_S; j++) {
            scanf_s("%d", &Allocation[i][j]);
            Need[i][j] = Max[i][j] - Allocation[i][j];
            temp[j] += Allocation[i][j];
        }
    }

    // 更新可用资源
    for (j = 0; j < Num_S; j++) {
        Available[j] -= temp[j];
    }
}

void show() {
    printf("\t--------------------\n");
    printf("\t系统当前可用的资源数组 Available：\n");
    int i, j;
    for (i = 0; i < Num_S; i++) {
        printf("%c ", Name[i]);
    }
    printf("\n");
    for (i = 0; i < Num_S; i++) {
        printf("%d ", Available[i]);
    }
    printf("\n");

    printf("\t系统当前资源分配情况如下： \n");
    printf("\t    Max          Allocation           Need\n");
    printf("进程名  ");
    for (j = 0; j < Num_S; j++) {
        printf("%c ", Name[j]);
    }
    printf("\t    ");
    for (j = 0; j < Num_S; j++) {
        printf("%c ", Name[j]);
    }
    printf("\t    ");
    for (j = 0; j < Num_S; j++) {
        printf("%c ", Name[j]);
    }
    printf("\n");

    for (i = 0; i < Num_P; i++) {
        printf("P%d\t\t", i);
        for (j = 0; j < Num_S; j++) {
            printf("%d ", Max[i][j]);
        }
        printf("\t    ");
        for (j = 0; j < Num_S; j++) {
            printf("%d ", Allocation[i][j]);
        }
        printf("\t    ");
        for (j = 0; j < Num_S; j++) {
            printf("%d ", Need[i][j]);
        }
        printf("\n");
    }
}

int isSafe() {
    int Finish[100] = { 0 }; // 记录进程是否完成
    int i, j, k, m = 0, count = 0;
    for (i = 0; i < Num_S; i++) {
        Work[i] = Available[i]; // 初始化工作数组
    }

    for (i = 0; i < Num_P; i++) {
        count = 0;
        for (j = 0; j < Num_S; j++) {
            if (Finish[i] == 0 && Need[i][j] <= Work[j]) {
                count++;
                if (count == Num_S) { // 满足条件，说明可以完成该进程
                    Finish[i] = 1;
                    for (k = 0; k < Num_S; k++) {
                        Work[k] += Allocation[i][k]; // 释放资源
                    }
                    Security[m++] = i;
                    i = -1; // 重新检查
                    break;
                }
            }
        }
    }

    // 检查是否所有进程都已完成
    for (i = 0; i < Num_P; i++) {
        if (Finish[i] == 0) {
            printf("系统不安全\n");
            return -1;
        }
    }

    // 输出安全序列
    printf("系统安全\n");
    for (i = 0; i < Num_P; i++) {
        printf("P%d", Security[i]);
        if (i < Num_P - 1)
            printf("-->");
    }
    printf("\n");
    return 0;
}

int main() {
    printf("\t--------------------------\n");
    printf("\t||                         ||\n");
    printf("\t||        模拟银行家算法    ||\n");
    printf("\t||                         ||\n");
    printf("\t||        Wallstreet ||\n");
    printf("\t||                         ||\n");
    printf("\t--------------------------\n");

    init(); // 初始化输入数据
    show(); // 显示系统当前状态
    isSafe(); // 检查系统是否安全

    char choice;
    printf("\t-------------------------------------\n");
    printf("\t||                                                                  ||\n");
    printf("\t||                                                                  ||\n");
    printf("\t||               输入 E(e)退出程序          ||\n");
    printf("\t||                                                                  ||\n");
    printf("\t||                                                                  ||\n");
    printf("\t-------------------------------------\n");

    while (1) {
        scanf_s(" %c", &choice, 1); // 使用 " %c" 来防止换行符干扰输入
        if (choice == 'E' || choice == 'e') {
            exit(0);
        }
        else {
            printf("请正确选择\n");
        }
    }

    return 0;
}
