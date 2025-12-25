def display_menu():
    print("\n通讯录管理系统")
    print("1. 添加联系人")
    print("2. 查询联系人")
    print("3. 修改联系人信息")
    print("4. 删除联系人")
    print("5. 显示所有联系人")
    print("6. 退出系统")


def add_contact(contacts):
    name = input("请输入联系人姓名：")
    if name in contacts:
        print("该联系人已存在！")
        return
    phone = input("请输入电话：")
    email = input("请输入邮箱：")
    company = input("请输入工作单位：")
    contacts[name] = {
        "电话": phone,
        "邮箱": email,
        "工作单位": company
    }
    print("添加成功！")


def query_contact(contacts):
    name = input("请输入要查询的联系人姓名：")
    if name in contacts:
        print(f"{name} 的信息如下：")
        for key, value in contacts[name].items():
            print(f"{key}：{value}")
    else:
        print("联系人不存在！")


def modify_contact(contacts):
    name = input("请输入要修改的联系人姓名：")
    if name in contacts:
        print("请输入新的信息（留空表示不修改）：")
        phone = input(f"电话（当前：{contacts[name]['电话']}）：")
        email = input(f"邮箱（当前：{contacts[name]['邮箱']}）：")
        company = input(f"工作单位（当前：{contacts[name]['工作单位']}）：")

        if phone:
            contacts[name]["电话"] = phone
        if email:
            contacts[name]["邮箱"] = email
        if company:
            contacts[name]["工作单位"] = company

        print("信息修改成功！")
    else:
        print("联系人不存在！")


def delete_contact(contacts):
    name = input("请输入要删除的联系人姓名：")
    if name in contacts:
        del contacts[name]
        print("🗑删除成功！")
    else:
        print("联系人不存在！")


def show_all_contacts(contacts):
    if not contacts:
        print("通讯录为空！")
        return
    print("\n所有联系人信息：")
    for name, info in contacts.items():
        print(f"\n姓名：{name}")
        for key, value in info.items():
            print(f"{key}：{value}")


def main():
    contacts = {}

    while True:
        display_menu()
        choice = input("请选择操作（1-6）：")

        if choice == "1":
            add_contact(contacts)
        elif choice == "2":
            query_contact(contacts)
        elif choice == "3":
            modify_contact(contacts)
        elif choice == "4":
            delete_contact(contacts)
        elif choice == "5":
            show_all_contacts(contacts)
        elif choice == "6":
            print("退出通讯录系统")
            break
        else:
            print("输入有误，请输入 1~6 的数字。")


if __name__ == "__main__":
    main()