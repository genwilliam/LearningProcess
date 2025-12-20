#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  // 用于sleep函数

// 插入排序演示函数
void insertionSort(int arr[], int n) {
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;

        // 显示当前比较和交换
        printf("插入 %d, 比较过程: ", key);
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;

        // 显示数组状态
        for (int k = 0; k < n; k++) {
            printf("%d ", arr[k]);
        }
        printf("\n");

        sleep(1);  // 延迟1秒，便于观看每个步骤
    }
}

// 选择排序演示函数
void selectionSort(int arr[], int n) {
    int i, j, minIdx, temp;
    for (i = 0; i < n - 1; i++) {
        minIdx = i;
        for (j = i + 1; j < n; j++) {
            // 找到最小元素
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }

        // 交换最小元素与当前位置元素
        if (minIdx != i) {
            temp = arr[i];
            arr[i] = arr[minIdx];
            arr[minIdx] = temp;
        }

        // 显示数组状态
        printf("选择排序第%d轮: ", i + 1);
        for (int k = 0; k < n; k++) {
            printf("%d ", arr[k]);
        }
        printf("\n");

        sleep(1);  // 延迟1秒，便于观看每个步骤
    }
}

// 冒泡排序演示函数
void bubbleSort(int arr[], int n) {
    int i, j, temp;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - 1 - i; j++) {
            // 交换相邻元素
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }

        // 显示数组状态
        printf("冒泡排序第%d轮: ", i + 1);
        for (int k = 0; k < n; k++) {
            printf("%d ", arr[k]);
        }
        printf("\n");

        sleep(1);  // 延迟1秒，便于观看每个步骤
    }
}

// 用户交互界面
void displayMenu() {
    printf("选择排序算法演示:\n");
    printf("1. 插入排序\n");
    printf("2. 选择排序\n");
    printf("3. 冒泡排序\n");
    printf("0. 退出\n");
}

// 主函数
int main() {
    int choice;
    int arr[] = { 12, 11, 13, 5, 6 };  // 示例数组
    int n = sizeof(arr) / sizeof(arr[0]);

    while (1) {
        displayMenu();
        printf("请输入选择: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("\n开始插入排序演示:\n");
                insertionSort(arr, n);
                break;
            case 2:
                printf("\n开始选择排序演示:\n");
                selectionSort(arr, n);
                break;
            case 3:
                printf("\n开始冒泡排序演示:\n");
                bubbleSort(arr, n);
                break;
            case 0:
                printf("退出程序...\n");
                return 0;
            default:
                printf("无效选择，请重新选择.\n");
        }

        // 清空数组，避免排序结果影响后续排序
        int newArr[] = { 12, 11, 13, 5, 6 };
        for (int i = 0; i < n; i++) {
            arr[i] = newArr[i];
        }
    }

    return 0;
}
