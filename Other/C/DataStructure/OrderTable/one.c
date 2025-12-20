#include <stdio.h>
#include <stdlib.h>

// 定义顺序表结构
typedef struct {
    int *elements;  // 指向元素数组的指针
    int capacity;   // 数组的最大容量
    int size;       // 当前表中的元素数量
} OrderTable;

// 函数声明
OrderTable * createEmptyOrderTable(int capacity);

int main() {
    // 创建一个初始容量为10的空顺序表
    OrderTable *table = createEmptyOrderTable(10);

    // 输出当前顺序表的状态
    printf("Order Table is empty: %s\n", table->size == 0 ? "true" : "false");
    printf("Capacity of the table: %d\n", table->capacity);
    printf("Size of the table: %d\n", table->size);

    // 释放分配给顺序表的内存
    free(table->elements);
    free(table);

    return 0;
}

// 创建一个空的顺序表
OrderTable* createEmptyOrderTable(int capacity) {
    OrderTable *table = (OrderTable*) malloc(sizeof(OrderTable));
    if (table == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    table->elements = (int*) malloc(capacity * sizeof(int));
    if (table->elements == NULL) {
        fprintf(stderr, "Memory allocation for elements failed.\n");
        free(table);
        exit(EXIT_FAILURE);
    }

    table->capacity = capacity;
    table->size = 0;

    return table;
}