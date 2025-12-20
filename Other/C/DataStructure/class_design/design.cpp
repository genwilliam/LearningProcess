#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

#define MAX_FNUM 100   // 最大航班数量
#define MAX_SNUM 100   // 最大预定数量

// 航班信息类
class Flight {
public:
    std::string flight_no;        // 航班号
    std::string fly_city;         // 起飞城市
    std::string arrival_city;     // 到达城市
    std::string fly_time;         // 起飞时间
    std::string arrival_time;     // 到达时间
    float ticket_price;           // 票价
    float discount;               // 票价折扣
    int total_seats;              // 总座位数
    int book_seats;               // 已订座位数

    // 构造函数
    Flight() : ticket_price(0), discount(1.0), total_seats(0), book_seats(0) {}

    void display() const {
        std::cout << "航班号: " << flight_no << "\n"
                  << "起飞城市: " << fly_city << "\n"
                  << "到达城市: " << arrival_city << "\n"
                  << "起飞时间: " << fly_time << "\n"
                  << "到达时间: " << arrival_time << "\n"
                  << "票价: " << ticket_price << "\n"
                  << "票价折扣: " << discount << "\n"
                  << "已订座位数: " << book_seats << "\n"
                  << "总座位数: " << total_seats << "\n";
    }
};

// 客户信息类
class Customer {
public:
    std::string name;       // 姓名
    std::string id_card;    // 证件号
    int booking_count;      // 订票数量
    Flight *flight;         // 订票的航班信息

    // 构造函数
    Customer() : booking_count(0), flight(nullptr) {}
};

// 订票信息类
class Booking {
public:
    int book_id;          // 订票的编号
    Customer customer;    // 客户信息
    Flight *flight;       // 订票的航班
    int seat_count;       // 订票数量

    // 构造函数
    Booking() : book_id(0), flight(nullptr), seat_count(0) {}
};

// 航班列表和预定列表
std::vector<Flight> flights;
std::vector<Booking> bookings;
int flight_count = 0;  // 当前航班数量
int booking_count = 0; // 当前预定数量

// 录入航班信息
void add_flight() {
    if (flight_count >= MAX_FNUM) {
        std::cout << "航班数量已满，无法添加新航班。\n";
        return;
    }
    Flight new_flight;
    std::cout << "请输入航班号: ";
    std::cin >> new_flight.flight_no;
    std::cout << "请输入起飞城市: ";
    std::cin >> new_flight.fly_city;
    std::cout << "请输入到达城市: ";
    std::cin >> new_flight.arrival_city;
    std::cout << "请输入起飞时间: ";
    std::cin >> new_flight.fly_time;
    std::cout << "请输入到达时间: ";
    std::cin >> new_flight.arrival_time;
    std::cout << "请输入票价: ";
    std::cin >> new_flight.ticket_price;
    std::cout << "请输入票价折扣: ";
    std::cin >> new_flight.discount;
    std::cout << "请输入总座位数: ";
    std::cin >> new_flight.total_seats;
    new_flight.book_seats = 0;  // 航班初始订票座位为0

    flights.push_back(new_flight);
    flight_count++;

    std::cout << "航班添加成功。\n";
}

// 查询航班信息
void query_flight() {
    std::string flight_no;
    std::cout << "请输入航班号查询: ";
    std::cin >> flight_no;

    bool found = false;
    for (const auto& flight : flights) {
        if (flight.flight_no == flight_no) {
            flight.display();
            found = true;
            break;
        }
    }

    if (!found) {
        std::cout << "未找到航班。\n";
    }
}

// 订票功能
void book_ticket() {
    std::string flight_no;
    int seat_count;

    std::cout << "请输入航班号: ";
    std::cin >> flight_no;
    std::cout << "请输入订票数量: ";
    std::cin >> seat_count;

    bool found = false;
    for (auto& flight : flights) {
        if (flight.flight_no == flight_no) {
            found = true;
            if (flight.book_seats + seat_count > flight.total_seats) {
                std::cout << "航班座位不足，无法完成订票。\n";
                return;
            }

            Booking new_booking;
            new_booking.book_id = ++booking_count;
            new_booking.flight = &flight;
            new_booking.seat_count = seat_count;

            std::cout << "请输入客户姓名: ";
            std::cin >> new_booking.customer.name;
            std::cout << "请输入客户证件号: ";
            std::cin >> new_booking.customer.id_card;

            new_booking.customer.booking_count = seat_count;
            new_booking.customer.flight = &flight;

            bookings.push_back(new_booking);

            flight.book_seats += seat_count;

            std::cout << "订票成功！订单编号: " << new_booking.book_id << "\n";
            break;
        }
    }

    if (!found) {
        std::cout << "未找到航班。\n";
    }
}

// 退票功能
void cancel_ticket() {
    int booking_id;
    std::cout << "请输入订单编号: ";
    std::cin >> booking_id;

    bool found = false;
    for (size_t i = 0; i < bookings.size(); i++) {
        if (bookings[i].book_id == booking_id) {
            found = true;
            Flight* flight = bookings[i].flight;
            flight->book_seats -= bookings[i].seat_count;

            bookings.erase(bookings.begin() + i);  // 删除预定记录
            std::cout << "退票成功！\n";
            break;
        }
    }

    if (!found) {
        std::cout << "未找到订单。\n";
    }
}

// 显示主菜单
void display_menu() {
    std::cout << "\n主菜单:\n";
    std::cout << "1. 录入航班\n";
    std::cout << "2. 查询航班\n";
    std::cout << "3. 订票\n";
    std::cout << "4. 退票\n";
    std::cout << "5. 退出\n";
}

// 主函数
int main() {
    int choice;
    while (true) {
        display_menu();
        std::cout << "请输入选择: ";
        std::cin >> choice;

        switch (choice) {
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
                std::cout << "退出系统。\n";
                return 0;
            default:
                std::cout << "无效选择，请重新输入。\n";
        }
    }
    return 0;
}
