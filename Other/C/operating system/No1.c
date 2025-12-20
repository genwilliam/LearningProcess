#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

// process 结构体定义
typedef struct process {
    char name[10];        // 进程名称
    float arrivetime;     // 到达时间
    float servicetime;    // 服务时间
    float starttime;      // 开始时间
    float finishtime;     // 完成时间
    float turntime;       // 周转时间
    float weighttime;     // 带权周转时间
    bool finish_flag;     // 是否被完成执行的标志
} process;

// 所用函数声明
void printmenu();
void Init(process* p, int n);
void sortByArrivetime(process* p, int n);
void sortBystartTime(process* p, int n);
void FCFS_Algorithm(process* p, int n);
int findMin(process* p, int n, int curTime);  // 声明 findMin 函数
void SJF_Algorithm(process* p, int n);
void display(process* p, int n);

// 算法选择菜单目录
void printmenu() {
    printf("**********************进程调度算法***********************\n");
    printf("******************* 1.先来先服务算法 *****************\n");
    printf("******************* 2.最短作业优先算法 *****************\n");
    printf("******************* 0.退出 *****************\n");
    printf("*********************************************************\n");
}

// 进程的输入函数,对进程进行初始化
void Init(process* p, int n) {
    for (int i = 0; i < n; i++) {
        printf("请输入第%d个进程的名称: ", i + 1);
        scanf("%s", p[i].name);  // 使用 scanf
        printf("请输入第%d个进程的到达时间: ", i + 1);
        scanf("%f", &p[i].arrivetime);  // 使用 scanf
        printf("请输入第%d个进程的服务时间: ", i + 1);
        scanf("%f", &p[i].servicetime);  // 使用 scanf
        printf("\n");
    }
}

// 按照到达时间进行冒泡排序
void sortByArrivetime(process* p, int n) {
    int flag;
    process temp;
    for (int i = 0; i < n - 1; i++) {
        flag = 0;
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].arrivetime > p[j + 1].arrivetime) {
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
                flag = 1;
            }
        }
        if (flag == 0) {
            break;
        }
    }
}

/* 先来先服务算法（FCFS）
   系统按照作业到达的先后次序来进行调度，谁先到就给谁先提供服务
   简单公平，有利于长作业，不利于短作业 */
void FCFS_Algorithm(process* p, int n) {
    int preFinishTime = 0;  // 前一个作业的完成时间为下一作业的开始时间
    float avgTurnTime = 0;  // 平均周转时间
    float avgPowerTime = 0;  // 平均带权周转时间
    // 将所有的完成时间、周转时间、带权周转时间都初始化为 0
    for (int i = 0; i < n; i++) {
        p[i].finishtime = 0;
        p[i].turntime = 0;
        p[i].weighttime = 0;
    }
    // 如果第一个作业的到达时间不等于事先定义好的前一个作业的完成时间
    // 则将最先到达的进程的到达时间定为前一个作业的完成时间
    if (p[0].arrivetime != preFinishTime) {
        preFinishTime = p[0].arrivetime;
    }
    for (int i = 0; i < n; i++) {
        p[i].starttime = preFinishTime;  // 作业开始时间=上一个作业的完成时间
        // 作业的完成时间=上一个作业的完成时间（等待时间）+自身所需的服务时间
        p[i].finishtime = preFinishTime + p[i].servicetime;
        preFinishTime = p[i].finishtime;  // 更新上一个作业的完成时间
        // 周转时间=完成时间-到达时间
        p[i].turntime = p[i].finishtime - p[i].arrivetime;
        // 带权周转时间=作业的周转时间/完成作业所需服务时间
        p[i].weighttime = p[i].turntime / p[i].servicetime;
    }
    printf("进程调度：先来先服务算法（FCFS）\n");
    sortBystartTime(p, n);
    display(p, n);
    printf("此次进程的执行的顺序为：");
    for (int i = 0; i < n; i++) {
        avgTurnTime += p[i].turntime;
        avgPowerTime += p[i].weighttime;
        if (i == n - 1) {
            printf("%s", p[i].name);
        } else {
            printf("%s->", p[i].name);
        }
    }
    avgPowerTime = avgPowerTime / n;
    avgTurnTime = avgTurnTime / n;
    printf("\n 其平均周转时间为：%.3f\n", avgTurnTime);
    printf("其平均带权周转时间为：%.3f\n", avgPowerTime);
    printf("\n");
}

/* 最短作业优先算法
   系统从就绪队列中选择一个估计运行时间最短的作业，将处理机分配给它，使之立即执行
   以追求最短的平均等待时间，其平均等待时间、平均周转时间最少
   需要先对所有的进程按照到达时间进行升序排序，如果到达时间相同就按作业的长度（服务
   时间）升序排序 */
void SJF_Algorithm(process* p, int n) {
    int preFinishTime = 0;  // 前一个作业的完成时间为下一作业的开始时间
    int currentTime = 0;    // 当前时间
    float avgTurnTime = 0;  // 平均周转时间
    float avgPowerTime = 0;  // 平均带权周转时间
    sortByArrivetime(p, n);  // 首先将所有进程按照到达时间进行升序排序
    // 将所有的完成时间、周转时间、带权周转时间都初始化为 0
    for (int i = 0; i < n; i++) {
        p[i].finishtime = 0;
        p[i].turntime = 0;
        p[i].weighttime = 0;
        p[i].finish_flag = false;
    }
    // 如果第一个作业的到达时间不等于事先定义好的前一个作业的完成时间
    // 则将最先到达的进程的到达时间定为前一个作业的完成时间
    if (p[0].arrivetime != preFinishTime) {
        preFinishTime = p[0].arrivetime;
    }
    p[0].starttime = preFinishTime;
    p[0].finishtime = p[0].arrivetime + p[0].servicetime;
    p[0].turntime = p[0].finishtime - p[0].arrivetime;
    p[0].weighttime = p[0].turntime / p[0].servicetime;
    currentTime += p[0].finishtime;
    preFinishTime = p[0].finishtime;
    int count = 1, key = 0;
    while (count < n) {  // 修改这里
        key = findMin(p, n, currentTime);  // 找到服务时间最短的进程
        p[key].starttime = preFinishTime;
        p[key].finishtime = preFinishTime + p[key].servicetime;
        preFinishTime = p[key].finishtime;
        p[key].turntime = p[key].finishtime - p[key].arrivetime;
        p[key].weighttime = p[key].turntime / p[key].servicetime;
        p[key].finish_flag = true;
        count++;
        currentTime = p[key].finishtime;  // 更新当前时间为该进程的完成时间
    }
    display(p, n);
    for (int i = 0; i < n; i++) {
        avgTurnTime += p[i].turntime;
        avgPowerTime += p[i].weighttime;
        if (i == n - 1) {
            printf("%s", p[i].name);
        } else {
            printf("%s->", p[i].name);
        }
    }
    avgPowerTime = avgPowerTime / n;
    avgTurnTime = avgTurnTime / n;
    printf("\n 其平均周转时间为：%.3f\n", avgTurnTime);
    printf("其平均带权周转时间为：%.3f\n", avgPowerTime);
    printf("\n");
}

// 按照开始时间对进程进行升序排序
void sortBystartTime(process* p, int n) {
    int flag;
    process temp;
    for (int i = 0; i < n - 1; i++) {
        flag = 0;
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].starttime > p[j + 1].starttime) {
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
                flag = 1;
            }
        }
        if (flag == 0) {
            break;
        }
    }
}

// 打印进程的详细信息
void display(process* p, int n) {
    printf("进程名称\t到达时间\t服务时间\t开始时间\t完成时间\t周转时间\t带权周转时间\n");
    for (int i = 0; i < n; i++) {
        printf("%s\t%.3f\t%.3f\t%.3f\t%.3f\t%.3f\t%.3f\n", p[i].name,
            p[i].arrivetime, p[i].servicetime, p[i].starttime, p[i].finishtime,
            p[i].turntime, p[i].weighttime);
    }
}

// findMin 函数实现
int findMin(process* p, int n, int curTime) {
    int minIndex = -1;
    float minServiceTime = 999999;  // 初始化为一个非常大的数
    for (int i = 0; i < n; i++) {
        // 找到未完成的进程，并且该进程的到达时间小于等于当前时间
        if (p[i].arrivetime <= curTime && !p[i].finish_flag) {
            // 找到服务时间最短的进程
            if (p[i].servicetime < minServiceTime) {
                minServiceTime = p[i].servicetime;
                minIndex = i;
            }
        }
    }
    return minIndex;  // 返回服务时间最短的进程索引
}

// 主函数
int main() {
    int choice, n;
    printf("请输入进程数: ");
    scanf("%d", &n);
    process* p = (process*)malloc(n * sizeof(process));
    Init(p, n);

    do {
        printmenu();
        printf("请输入你选择的算法: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                FCFS_Algorithm(p, n);
                break;
            case 2:
                SJF_Algorithm(p, n);
                break;
            case 0:
                printf("程序结束！\n");
                break;
            default:
                printf("输入无效，请重新选择。\n");
                break;
        }
    } while (choice != 0);

    free(p);
    return 0;
}
