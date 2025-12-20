#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

#define MAX_WINDOWS 5    // 假设银行最多有5个窗口

// 顾客结构体
typedef struct {
    int id;             // 顾客ID
    int arrivalTime;    // 到达时间
    int serviceTime;    // 服务时间
    bool isVIP;         // 是否VIP顾客
} Customer;

// 队列节点
typedef struct Node {
    Customer data;
    struct Node* next;
} Node;

// 队列结构体
typedef struct {
    Node* front;
    Node* rear;
    int size;
} Queue;

// 窗口结构体
typedef struct {
    int id;                 // 窗口ID
    Customer* currentCustomer;  // 当前正在服务的顾客
    int serviceTimeRemaining;    // 剩余服务时间
} Window;

// 顾客离开队列的操作
void removeCustomerFromQueue(Queue* queue, int customerId) {
    if (queue->size == 0) {
        printf("Queue is empty!\n");
        return;
    }

    Node* current = queue->front;
    Node* prev = NULL;

    while (current != NULL) {
        if (current->data.id == customerId) {
            if (prev == NULL) {
                queue->front = current->next;
                if (queue->front == NULL) {
                    queue->rear = NULL;
                }
            } else {
                prev->next = current->next;
                if (current->next == NULL) {
                    queue->rear = prev;
                }
            }
            free(current);
            queue->size--;
            printf("Customer %d has left the queue.\n", customerId);
            return;
        }
        prev = current;
        current = current->next;
    }
    printf("Customer %d not found in the queue.\n", customerId);
}

// 初始化队列
void initQueue(Queue* q) {
    q->front = q->rear = NULL;
    q->size = 0;
}

// 入队操作
void enqueue(Queue* q, Customer customer) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = customer;
    newNode->next = NULL;

    if (q->rear == NULL) {
        q->front = q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
    q->size++;
}

// 出队操作
Customer dequeue(Queue* q) {
    if (q->size == 0) {
        printf("Queue is empty!\n");
        exit(1);
    }
    Node* temp = q->front;
    Customer customer = temp->data;
    q->front = q->front->next;
    if (q->front == NULL) {
        q->rear = NULL;
    }
    free(temp);
    q->size--;
    return customer;
}

// 查看队列头部元素
Customer peek(Queue* q) {
    if (q->size == 0) {
        printf("Queue is empty!\n");
        exit(1);
    }
    return q->front->data;
}

// 检查队列是否为空
bool isQueueEmpty(Queue* q) {
    return q->size == 0;
}

// 初始化窗口
void initWindow(Window* window, int id) {
    window->id = id;
    window->currentCustomer = NULL;
    window->serviceTimeRemaining = 0;
}

// 处理窗口中的顾客
void processWindow(Window* window) {
    if (window->currentCustomer != NULL) {
        window->serviceTimeRemaining--;
        if (window->serviceTimeRemaining == 0) {
            printf("Window %d finished serving Customer %d\n", window->id, window->currentCustomer->id);
            window->currentCustomer = NULL;
        }
    }
}

// 显示窗口状态
void showWindowStatus(Window windows[], int numWindows) {
    for (int i = 0; i < numWindows; i++) {
        if (windows[i].currentCustomer != NULL) {
            printf("Window %d is serving Customer %d, remaining service time: %d\n", 
                   windows[i].id, windows[i].currentCustomer->id, windows[i].serviceTimeRemaining);
        } else {
            printf("Window %d is idle.\n", windows[i].id);
        }
    }
}

// 查询已办理业务的顾客数量
void showProcessedCustomers(int processedCount) {
    printf("Total customers processed: %d\n", processedCount);
}

// 随机生成顾客数据并存储到文件
void generateCustomerData(const char* filename, int numCustomers) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("Failed to open file for writing.\n");
        return;
    }

    srand(time(NULL));  // 设置随机数种子

    for (int i = 0; i < numCustomers; i++) {
        int arrivalTime = rand() % 100;  // 随机到达时间，假设最大时间为100
        int serviceTime = rand() % 10 + 1;  // 随机服务时间，1-10
        int isVIP = rand() % 2;  // 随机决定是否是VIP
        fprintf(file, "%d %d %d %d\n", i+1, arrivalTime, serviceTime, isVIP);
    }

    fclose(file);
}

// 从文件中加载顾客数据
void loadCustomerData(const char* filename, Queue* normalQueue, Queue* vipQueue) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Failed to open file for reading.\n");
        return;
    }

    int id, arrivalTime, serviceTime, isVIP;
    while (fscanf(file, "%d %d %d %d", &id, &arrivalTime, &serviceTime, &isVIP) != EOF) {
        Customer customer = {id, arrivalTime, serviceTime, isVIP};
        if (isVIP) {
            enqueue(vipQueue, customer);  // VIP顾客进入VIP队列
        } else {
            enqueue(normalQueue, customer);  // 普通顾客进入普通队列
        }
    }

    fclose(file);
}

int main() {
    Queue normalQueue, vipQueue;
    initQueue(&normalQueue);
    initQueue(&vipQueue);

    Window windows[MAX_WINDOWS];
    for (int i = 0; i < MAX_WINDOWS; i++) {
        initWindow(&windows[i], i + 1);
    }

    // 生成顾客数据并存储到文件
    generateCustomerData("customers.txt", 10);  // 生成10个顾客的数据

    // 从文件中加载顾客数据
    loadCustomerData("customers.txt", &normalQueue, &vipQueue);

    int processedCount = 0;
    for (int time = 0; time < 50; time++) {  // 模拟50个时间单位
        printf("\nTime: %d\n", time);

        // 为VIP窗口分配顾客
        if (!isQueueEmpty(&vipQueue)) {
            Customer vip = dequeue(&vipQueue);
            for (int i = 0; i < MAX_WINDOWS; i++) {
                if (windows[i].currentCustomer == NULL) {
                    windows[i].currentCustomer = &vip;
                    windows[i].serviceTimeRemaining = vip.serviceTime;
                    processedCount++;
                    break;
                }
            }
        }

        // 为普通窗口分配顾客
        for (int i = 0; i < MAX_WINDOWS; i++) {
            if (windows[i].currentCustomer == NULL && !isQueueEmpty(&normalQueue)) {
                Customer normal = dequeue(&normalQueue);
                windows[i].currentCustomer = &normal;
                windows[i].serviceTimeRemaining = normal.serviceTime;
                processedCount++;
            }
        }

        // 处理窗口中的顾客
        for (int i = 0; i < MAX_WINDOWS; i++) {
            processWindow(&windows[i]);
        }

        // 显示窗口状态
        showWindowStatus(windows, MAX_WINDOWS);

        // 显示处理过的顾客数
        showProcessedCustomers(processedCount);
    }

    return 0;
}
