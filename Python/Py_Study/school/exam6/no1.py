class BankAccount:
    """银行账户基类"""

    def __init__(self, account_id, name, balance=0.0):
        self.account_id = account_id
        self.name = name
        self.balance = balance

    def deposit(self, amount):
        if amount <= 0:
            print("存款金额必须大于 0")
            return
        self.balance += amount
        print(f"成功存入 {amount} 元")

    def withdraw(self, amount):
        """基类允许自由取款（由子类控制）"""
        if amount <= 0:
            print("取款金额必须大于 0")
            return
        self.balance -= amount
        print(f"✔ 成功取出 {amount} 元")

    def info(self):
        print("\n===== 账户信息 =====")
        print(f"账户编号：{self.account_id}")
        print(f"姓名：{self.name}")
        print(f"余额：{self.balance} 元")
        print("=====================\n")


# 储蓄账户
class SavingAccount(BankAccount):
    """不允许透支"""

    def withdraw(self, amount):
        if amount <= 0:
            print("取款金额必须大于 0")
            return

        if self.balance - amount < 0:
            print("余额不足")
            return

        self.balance -= amount
        print(f"✔ 储蓄账户成功取出 {amount} 元")


# 信用卡账户

class CreditAccount(BankAccount):
    """允许透支，有信用额度"""

    def __init__(self, account_id, name, balance=0.0, credit_limit=-10000):
        super().__init__(account_id, name, balance)
        self.credit_limit = credit_limit

    def withdraw(self, amount):
        if amount <= 0:
            print("取款金额必须大于 0")
            return

        if self.balance - amount < self.credit_limit:
            print("超过信用额度，无法取款")
            return

        self.balance -= amount
        print(f"✔ 信用卡成功取出 {amount} 元")



# 系统主体
class BankSystem:
    def __init__(self):
        self.accounts = {}  # 保存所有账户

    def create_account(self):
        print("\n请选择要开设的账户类型：")
        print("1. 储蓄账户")
        print("2. 信用卡账户")
        choice = input("输入数字选择：")

        account_id = input("请输入账户编号：")
        name = input("请输入持卡人姓名：")
        balance = float(input("请输入初始余额："))

        if choice == "1":
            acc = SavingAccount(account_id, name, balance)
            self.accounts[account_id] = acc
            print("✔ 储蓄账户创建成功！")
        elif choice == "2":
            limit = float(input("请输入信用额度（如 -10000）："))
            acc = CreditAccount(account_id, name, balance, limit)
            self.accounts[account_id] = acc
            print("✔ 信用卡账户创建成功！")
        else:
            print("无效选择")

    def get_account(self):
        account_id = input("请输入账户编号：")
        if account_id in self.accounts:
            return self.accounts[account_id]
        print("未找到该账户")
        return None

    def operate_account(self):
        acc = self.get_account()
        if not acc:
            return

        while True:
            print("\n===== 账户操作菜单 =====")
            print("1. 存款")
            print("2. 取款")
            print("3. 查询信息")
            print("4. 返回主菜单")
            choice = input("请选择操作：")

            if choice == "1":
                amount = float(input("请输入存款金额："))
                acc.deposit(amount)

            elif choice == "2":
                amount = float(input("请输入取款金额："))
                acc.withdraw(amount)

            elif choice == "3":
                acc.info()

            elif choice == "4":
                return

            else:
                print("无效选择！")

    def run(self):
        while True:
            print("\n====== 银行账户管理系统 ======")
            print("1. 创建账户")
            print("2. 操作账户")
            print("3. 退出系统")
            print("================================")

            choice = input("请选择功能：")

            if choice == "1":
                self.create_account()
            elif choice == "2":
                self.operate_account()
            elif choice == "3":
                print("已退出系统，再见！")
                break
            else:
                print("无效选择，请重新输入")


if __name__ == "__main__":
    bank = BankSystem()
    bank.run()