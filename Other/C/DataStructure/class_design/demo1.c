#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 定义客户结构体，包含客户编号、到达时间、办理业务所需时间、是否为VIP标识
typedef struct Customer {
    int customerId;
    int arrivalTime;
    int serviceTime;
    int isVIP;
    struct Customer *next;  // 新增这一行，用于指向下一个客户节点，构建链表队列
} Customer;


// 定义窗口结构体，包含窗口编号、当前客户、排队队列
typedef struct Window {
    int windowId;
    Customer *currentCustomer;
    struct Queue *queue;
} Window;

// 定义队列结构体，包含队列头指针、队列尾指针、队列长度
typedef struct Queue {
    Customer *front;
    Customer *rear;
    int length;
} Queue;

// 初始化队列
void initQueue(Queue *queue) {
    queue->front = queue->rear = NULL;
    queue->length = 0;
}

// 判断队列是否为空
int isQueueEmpty(Queue *queue) {
    return queue->front == NULL;
}

// 入队操作
void enqueue(Queue *queue, Customer customer) {
    Customer *newCustomer = (Customer *)malloc(sizeof(Customer));
    *newCustomer = customer;
    newCustomer->next = NULL;
    if (isQueueEmpty(queue)) {
        queue->front = queue->rear = newCustomer;
    } else {
        queue->rear->next = newCustomer;
        queue->rear = newCustomer;
    }
    queue->length++;
}

// 出队操作
Customer dequeue(Queue *queue) {
    if (isQueueEmpty(queue)) {
        // 队列为空，返回一个默认的客户结构体
        Customer emptyCustomer = {-1, -1, -1, -1};
        return emptyCustomer;
    }
    Customer *temp = queue->front;
    Customer customer = *temp;
    queue->front = queue->front->next;
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    free(temp);
    queue->length--;
    return customer;
}

// 初始化窗口
void initWindow(Window *window, int windowId) {
    window->windowId = windowId;
    window->currentCustomer = NULL;
    initQueue(window->queue);
}

// 寻找空闲的普通窗口（非VIP窗口）
Window *findAvailableRegularWindow(Window *windows, int numWindows, int numVIPWindows) {
    for (int i = numVIPWindows; i < numWindows; i++) {
        if (windows[i].currentCustomer == NULL && isQueueEmpty(windows[i].queue)) {
            return &windows[i];
        }
    }
    return NULL;
}

// 寻找最短队列的普通窗口（非VIP窗口）
Window *findShortestQueueRegularWindow(Window *windows, int numWindows, int numVIPWindows) {
    Window *shortestWindow = NULL;
    int minQueueLength = -1;
    for (int i = numVIPWindows; i < numWindows; i++) {
        int queueLength = windows[i].queue->length;
        if (shortestWindow == NULL || queueLength < minQueueLength) {
            shortestWindow = &windows[i];
            minQueueLength = queueLength;
        }
    }
    return shortestWindow;
}

// 寻找空闲的VIP窗口
Window *findAvailableVIPWindow(Window *windows, int numVIPWindows) {
    for (int i = 0; i < numVIPWindows; i++) {
        if (windows[i].currentCustomer == NULL && isQueueEmpty(windows[i].queue)) {
            return &windows[i];
        }
    }
    return NULL;
}

int main() {
    int numWindows, numCustomers, numVIPWindows;
    printf("请输入银行窗口总数量: ");
    scanf("%d", &numWindows);
    printf("请输入VIP窗口数量: ");
    scanf("%d", &numVIPWindows);
    printf("请输入客户数量: ");
    scanf("%d", &numCustomers);

    Window *windows = (Window *)malloc(numWindows * sizeof(Window));
    for (int i = 0; i < numWindows; i++) {
        initWindow(&windows[i], i + 1);
    }

    for (int i = 0; i < numCustomers; i++) {
        Customer customer;
        customer.customerId = i + 1;
        printf("请输入客户 %d 的到达时间、办理业务所需时间（空格隔开），再输入0（普通顾客）或1（VIP顾客）: ", customer.customerId);
        scanf("%d %d %d", &customer.arrivalTime, &customer.serviceTime, &customer.isVIP);

        if (customer.isVIP) {
            Window *availableVIPWindow = findAvailableVIPWindow(windows, numVIPWindows);
            if (availableVIPWindow!= NULL) {
                availableVIPWindow->currentCustomer = &customer;
            } else {
                // 如果VIP窗口都忙，这里可以考虑其他策略，比如提示VIP顾客稍等或者也加入普通队列（根据实际规则定），这里暂简单提示
                printf("当前VIP窗口繁忙，请稍后再试\n");
            }
        } else {
            Window *availableRegularWindow = findAvailableRegularWindow(windows, numWindows, numVIPWindows);
            if (availableRegularWindow!= NULL) {
                availableRegularWindow->currentCustomer = &customer;
            } else {
                Window *shortestQueueRegularWindow = findShortestQueueRegularWindow(windows, numWindows, numVIPWindows);
                enqueue(shortestQueueRegularWindow->queue, customer);
            }
        }
    }

    // 模拟叫号过程
    for (int i = 0; i < numWindows; i++) {
        if (windows[i].currentCustomer!= NULL) {
            printf("窗口 %d 正在为客户 %d 办理业务，办理时间为 %d 分钟\n",
                   windows[i].windowId,
                   windows[i].currentCustomer->customerId,
                   windows[i].currentCustomer->serviceTime);
        } else if (!isQueueEmpty(windows[i].queue)) {
            Customer nextCustomer = dequeue(windows[i].queue);
            windows[i].currentCustomer = &nextCustomer;
            printf("窗口 %d 呼叫客户 %d 前来办理业务，办理时间为 %d 分钟\n",
                   windows[i].windowId,
                   nextCustomer.customerId,
                   nextCustomer.serviceTime);
        }
    }

    // 释放内存
    for (int i = 0; i < numWindows; i++) {
        while (!isQueueEmpty(windows[i].queue)) {
            dequeue(windows[i].queue);
        }
    }
    free(windows);

    return 0;
}