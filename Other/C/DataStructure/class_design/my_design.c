#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_FNUM 100   // 最大航班数量
#define MAX_SNUM 100   // 最大预定数量
#define MAX_STRING_LENGTH 100  // 最大字符长度

// 航班信息结构体
typedef struct
{
    char flight_no[MAX_STRING_LENGTH];  // 航班号
    char fly_city[MAX_STRING_LENGTH];  // 起飞城市
    char arrival_city[MAX_STRING_LENGTH];  // 到达城市
    char fly_time[MAX_STRING_LENGTH];  // 起飞时间
    char arrival_time[MAX_STRING_LENGTH];  // 到达时间
    float ticket_price;  // 票价
    float discount;  // 票价折扣
    int total_seats;  // 总座位数
    int book_seats;  // 已订座位数
} Flight;

// 客户信息结构体
typedef struct
{
    char name[MAX_STRING_LENGTH];  // 姓名
    char id_card[MAX_STRING_LENGTH];  // 证件号
    int booking_count;  // 订票数量
    Flight *flight;  // 订票的航班信息
} Customer;

// 订票信息结构体
typedef struct
{
    int book_id;  // 订票的编号
    Customer customer;  // 客户信息
    Flight *flight;  // 订票的航班
    int seat_count;  // 订票数量
} Booking;


Flight flights[MAX_FNUM];
Booking bookings[MAX_SNUM];
int flight_count = 0;  // 当前航班数量
int booking_count = 0;  // 当前预定数量

/**
 * @brief 检查输入的整数是否合法
 *
 * 该函数用于验证用户输入的整数是否有效。
 * @param prompt 提示消息
 * @return 返回有效的整数
 */
int get_int_input(const char* prompt)
{
    int value;
    while (1)
    {
        printf("%s", prompt);
        if (scanf("%d", &value) != 1)
        {
            while(getchar() != '\n'); // 清除输入缓冲区
            printf("输入无效，请重新输入。\n");
        }
        else
        {
            return value;
        }
    }
}

/**
 * @brief 检查输入的浮动数值是否合法
 *
 * 该函数用于验证用户输入的浮动数值是否有效。
 * @param prompt 提示消息
 * @return 返回有效的浮动数值
 */
float get_float_input(const char* prompt)
{
    float value;
    while (1)
    {
        printf("%s", prompt);
        if (scanf("%f", &value) != 1)
        {
            while(getchar() != '\n'); // 清除输入缓冲区
            printf("输入无效，请重新输入。\n");
        }
        else
        {
            return value;
        }
    }
}

/**
 * @brief 输入有效的字符串
 *
 * 该函数用于验证用户输入的字符串是否有效。
 * @param prompt 提示消息
 * @param input 存储用户输入的字符串
 * @return 无返回值
 */
void get_string_input(const char* prompt, char* input)
{
    while (1)
    {
        printf("%s", prompt);
        if (scanf("%s", input) == 1 && strlen(input) > 0)
        {
            break;
        }
        else
        {
            while (getchar() != '\n');  // 清除输入缓冲区
            printf("输入无效，请重新输入。\n");
        }
    }
}

/**
 * @brief 打印表格的分隔线
 *
 * 该函数用于打印表格的分隔线，增加表格的可读性。
 *
 * @param length 线的长度
 * @return 无返回值
 */
void print_line(int length)
{
    for (int i = 0; i < length; i++)
    {
        printf("-");
    }
    printf("\n");
}

/**
 * @brief 打印航班信息表格
 *
 * 该函数用于以表格形式打印航班信息。
 *
 * @param flight 航班信息
 * @return 无返回值
 */
void print_flight_table(Flight* flight)
{
    print_line(80);
    printf("| %-15s | %-15s | %-15s | %-15s | %-15s | %-10s | %-10s | %-10s | %-10s |\n", 
            "航班号", "起飞城市", "到达城市", "起飞时间", "到达时间", "票价", "折扣", "总座位数", "已订座位数");
    print_line(80);
    printf("| %-15s | %-15s | %-15s | %-15s | %-15s | %-10.2f | %-10.2f | %-10d | %-10d |\n", 
            flight->flight_no, flight->fly_city, flight->arrival_city, flight->fly_time, flight->arrival_time, 
            flight->ticket_price, flight->discount, flight->total_seats, flight->book_seats);
    print_line(80);
}

/**
 * @brief 录入航班信息
 *
 * 该函数用于向系统中添加新的航班信息。
 * 若当前已有航班数量已达到上限，则无法添加新航班并返回。
 * 否则，从键盘输入新航班的相关信息，并将其添加到航班列表中。
 *
 * @return 无返回值
 */
void add_flight()
{
    if (flight_count >= MAX_FNUM)
    {
        printf("航班数量已满，无法添加新航班。\n");
        return;
    }
    Flight new_flight;

    get_string_input("请输入航班号: ", new_flight.flight_no);
    get_string_input("请输入起飞城市: ", new_flight.fly_city);
    get_string_input("请输入到达城市: ", new_flight.arrival_city);
    get_string_input("请输入起飞时间: ", new_flight.fly_time);
    get_string_input("请输入到达时间: ", new_flight.arrival_time);
    new_flight.ticket_price = get_float_input("请输入票价: ");
    new_flight.discount = get_float_input("请输入票价折扣: ");
    new_flight.total_seats = get_int_input("请输入总座位数: ");
    new_flight.book_seats = 0;  // 航班初始订票座位为0

    // 将新建的航班信息添加到航班数组中
    flights[flight_count++] = new_flight;

    printf("航班添加成功。\n");
}

/**
 * @brief 查询航班信息
 *
 * 该函数用于根据用户输入的航班号查询航班信息。
 * 若找到匹配的航班号，则打印该航班的详细信息。
 * 若未找到匹配的航班号，则提示用户未找到航班。
 *
 * @param 无参数
 *
 * @return 无返回值
 */
void query_flight()
{
    char flight_no[MAX_STRING_LENGTH];  // 存储将要查询的航班号
    get_string_input("请输入航班号查询: ", flight_no);

    int found = 0;  // 是否找到航班信息
    for (int i = 0; i < flight_count; i++)
    {
        if (strcmp(flights[i].flight_no, flight_no) == 0)
        {
            found = 1;
            print_flight_table(&flights[i]);
            break;
        }
    }

    if (!found)
    {
        printf("未找到航班。\n");
    }
}

/**
 * @brief 订票功能
 *
 * 该函数用于根据用户输入的航班号和订票数量进行订票操作。
 * 若航班号存在且座位充足，则创建新的订票记录。
 * 否则，提示用户航班不存在或座位不足。
 *
 * @param 无参数
 *
 * @return 无返回值
 */
void book_ticket()
{
    char flight_no[MAX_STRING_LENGTH];
    int seat_count;  // 座位数量

    get_string_input("请输入航班号: ", flight_no);
    seat_count = get_int_input("请输入订票数量: ");

    int found = 0;  // 是否找到
    for (int i = 0; i < flight_count; i++)
    {
        if (strcmp(flights[i].flight_no, flight_no) == 0)
        {
            found = 1;
            // 座位满时
            if (flights[i].book_seats + seat_count > flights[i].total_seats)
            {
                printf("航班座位不足，无法完成订票。\n");
                return;
            }

            // 创建新的预定
            Booking new_booking;
            new_booking.book_id = booking_count + 1;
            new_booking.flight = &flights[i];
            new_booking.seat_count = seat_count;

            get_string_input("请输入客户姓名: ", new_booking.customer.name);
            get_string_input("请输入客户证件号: ", new_booking.customer.id_card);

            new_booking.customer.booking_count = seat_count;
            new_booking.customer.flight = &flights[i]; // 将当前航班信息添加到客户对象中

            bookings[booking_count++] = new_booking; // 将新订单添加到订单数组中
            flights[i].book_seats += seat_count;  // 更新航班座位数量

            printf("订票成功！订单编号: %d\n", new_booking.book_id);
            break;
        }
    }

    if (!found)
    {
        printf("未找到航班。\n");
    }
}

/**
 * @brief 退票功能
 *
 * 该函数用于根据用户输入的订单编号进行退票操作。
 * 若订单编号存在，则减少相应航班的已订座位数，并删除该订单。
 * 若未找到订单编号，则提示用户未找到订单。
 *
 * @param 无参数
 *
 * @return 无返回值
 */
void cancel_ticket()
{
    int booking_id;  // 要退票的编号
    booking_id = get_int_input("请输入订单编号: ");

    int found = 0;
    for (int i = 0; i < booking_count; i++)
    {
        if (bookings[i].book_id == booking_id)
        {
            found = 1;
            Flight *flight = bookings[i].flight;  // flight指向当前订单中预定的航班信息
            flight->book_seats -= bookings[i].seat_count;  // 减少航班已经订了座位的数量

            // 删除预定
            for (int j = i; j < booking_count - 1; j++)
            {
                bookings[j] = bookings[j + 1];
            }
            booking_count--;

            printf("退票成功！\n");
            break;
        }
    }

    if (!found)
    {
        printf("未找到订单。\n");
    }
}

// 主菜单
void display_menu()
{
    printf("\n=== 主菜单 ===\n");
    printf("1. 录入航班\n");
    printf("2. 查询航班\n");
    printf("3. 订票\n");
    printf("4. 退票\n");
    printf("5. 退出\n");
    printf("================\n");
}

// 主函数，程序入口点
int main()
{
    int choice;
    while (1)
    {
        display_menu();  // 显示菜单
        choice = get_int_input("请输入选择: ");

        switch (choice)
        {
        case 1:
            add_flight();
            break;
        case 2:
            query_flight();
            break;
        case 3:
            book_ticket();
            break;
        case 4:
            cancel_ticket();
            break;
        case 5:
            printf("退出程序。\n");
            return 0;
        default:
            printf("无效选择，请重新输入。\n");
        }
    }
    return 0;
}
