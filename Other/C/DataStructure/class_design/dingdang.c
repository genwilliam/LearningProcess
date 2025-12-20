#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_QUEUE 1010
#define MAX_WINDOWS 10

typedef struct {
    int arrival_time;  // 顾客到达时间
    int service_time;  // 顾客办理业务的时间
    int is_vip;        // 顾客是否VIP (1为VIP，0为普通顾客)
    int queue_number;  // 顾客排队号码
} Customer;

typedef struct {
    int is_busy;                // 窗口是否正在忙碌
    int finish_time;            // 窗口何时空闲
    int current_customer_id;    // 当前窗口正在处理的顾客ID
} Window;

Customer queue[MAX_QUEUE];
Window windows[MAX_WINDOWS];
int total_customers = 0;
int total_vip_customers = 0;
int total_served_customers = 0;

void simulate_bank_service(int n_windows) {
    int front = 0, rear = 0;
    int current_time = 0;
    int service_count[MAX_WINDOWS] = {0};

    // 模拟过程
    while (front < total_customers) {
        int free_window = -1;

        // 查找空闲窗口
        for (int i = 0; i < n_windows; i++) {
            if (windows[i].finish_time <= current_time && windows[i].is_busy == 0) {
                free_window = i;
                break;
            }
        }

        if (free_window != -1) {
            // 顾客排队
            if (queue[front].arrival_time <= current_time) {
                printf("Customer %d arrived at time %d, Queue Number: %d, Waiting Customers: %d\n",
                    front + 1, current_time, queue[front].queue_number, rear - front);

                // 处理普通顾客
                if (queue[front].is_vip == 0) {
                    windows[free_window].is_busy = 1;
                    windows[free_window].finish_time = current_time + queue[front].service_time;
                    windows[free_window].current_customer_id = front;
                    service_count[free_window]++;
                    total_served_customers++;

                    printf("Window %d serving customer %d (normal) from %d to %d\n",
                        free_window + 1, front + 1, current_time, windows[free_window].finish_time);

                    front++;  // 顾客办理完毕，队列前进
                } else {
                    // VIP顾客立即服务
                    windows[free_window].is_busy = 1;
                    windows[free_window].finish_time = current_time + queue[front].service_time;
                    windows[free_window].current_customer_id = front;
                    service_count[free_window]++;
                    total_vip_customers++;

                    printf("VIP Window %d serving customer %d (VIP) from %d to %d\n",
                        free_window + 1, front + 1, current_time, windows[free_window].finish_time);

                    front++;
                }
            }
        } else {
            // 没有窗口空闲，顾客需要等待
            current_time++;
        }
    }

    // 输出窗口服务统计信息
    printf("\nService Summary:\n");
    for (int i = 0; i < n_windows; i++) {
        printf("Window %d served %d customers\n", i + 1, service_count[i]);
    }

    printf("Total served customers: %d\n", total_served_customers);
    printf("Total VIP customers: %d\n", total_vip_customers);
}

int main() {
    int n_windows, num_customers;

    printf("Enter number of windows: ");
    scanf("%d", &n_windows);  // 输入窗口数量
    printf("Enter number of customers: ");
    scanf("%d", &num_customers);  // 输入顾客数量

    total_customers = num_customers;

    // 初始化窗口状态
    for (int i = 0; i < n_windows; i++) {
        windows[i].is_busy = 0;
        windows[i].finish_time = 0;
        windows[i].current_customer_id = -1;
    }

    // 输入顾客信息
    printf("Enter customer details (arrival_time service_time is_vip):\n");
    for (int i = 0; i < num_customers; i++) {
        printf("Customer %d: ", i + 1);
        scanf("%d %d %d", &queue[i].arrival_time, &queue[i].service_time, &queue[i].is_vip);
        queue[i].queue_number = i + 1;
    }

    // 开始模拟银行服务
    simulate_bank_service(n_windows);

    return 0;
}
