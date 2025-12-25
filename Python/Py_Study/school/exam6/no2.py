# 商品类

class Product:
    def __init__(self, name, price):
        self.name = name
        self.price = float(price)

    def __str__(self):
        return f"{self.name} - ￥{self.price}"


# 折扣策略基类
class DiscountStrategy:
    def apply(self, total_price):
        """子类重写折扣算法"""
        return total_price


# 无折扣策略
class NoDiscount(DiscountStrategy):
    def apply(self, total_price):
        return total_price


# 百分比折扣
class PercentageDiscount(DiscountStrategy):
    def __init__(self, percent):
        self.percent = percent  # 例如 0.8 表示打 8 折

    def apply(self, total_price):
        return total_price * self.percent


# 满减策略
class FullReductionDiscount(DiscountStrategy):
    def __init__(self, full, minus):
        self.full = full
        self.minus = minus

    def apply(self, total_price):
        if total_price >= self.full:
            return total_price - self.minus
        return total_price


# 购物车类
class ShoppingCart:
    def __init__(self):
        # 商品名: {"product": Product, "quantity": int}
        self.items = {}

    def add_product(self, product):
        if product.name in self.items:
            self.items[product.name]["quantity"] += 1
        else:
            self.items[product.name] = {"product": product, "quantity": 1}
        print(f"已添加：{product.name}")

    def remove_product(self, product_name):
        if product_name not in self.items:
            print("购物车中没有该商品！")
            return

        if self.items[product_name]["quantity"] > 1:
            self.items[product_name]["quantity"] -= 1
        else:
            del self.items[product_name]
        print(f"已删除：{product_name}")

    def show_cart(self):
        if not self.items:
            print("购物车是空的。")
            return

        print("\n———— 当前购物车 ————")
        for name, info in self.items.items():
            print(f"{name} × {info['quantity']} | 单价：￥{info['product'].price} ")
        print("——————————————\n")

    def calculate_total(self):
        total = 0
        for info in self.items.values():
            total += info["product"].price * info["quantity"]
        return total


# 系统主程序（交互式）
def main():
    cart = ShoppingCart()
    discount = NoDiscount()  # 默认无折扣

    # 预设一些商品
    products = {
        "苹果": Product("苹果", 3.5),
        "香蕉": Product("香蕉", 2.0),
        "牛奶": Product("牛奶", 8.0),
        "面包": Product("面包", 5.0)
    }

    while True:
        print("""
=============== 购物车系统 ===============
1. 添加商品
2. 删除商品
3. 查看购物车
4. 选择折扣策略
5. 结算
6. 退出
=========================================
""")

        choice = input("请输入操作编号：")

        # 添加商品
        if choice == "1":
            print("可添加商品：", ", ".join(products.keys()))
            name = input("输入商品名称：")
            if name in products:
                cart.add_product(products[name])
            else:
                print("商品不存在！")

        # 删除商品
        elif choice == "2":
            name = input("输入要删除的商品名称：")
            cart.remove_product(name)

        # 查看购物车
        elif choice == "3":
            cart.show_cart()

        # 选择折扣策略
        elif choice == "4":
            print("""
折扣策略：
1. 无折扣
2. 打折
3. 满减
""")
            d = input("选择折扣类型：")
            if d == "1":
                discount = NoDiscount()
                print("已选择：无折扣")
            elif d == "2":
                percent = float(input("输入折扣，例如 0.8 表示 8 折："))
                discount = PercentageDiscount(percent)
                print("已选择：折扣策略")
            elif d == "3":
                full = float(input("满多少："))
                minus = float(input("减多少："))
                discount = FullReductionDiscount(full, minus)
                print("已选择：满减策略")
            else:
                print("无效的选择！")

        # 结算
        elif choice == "5":
            total = cart.calculate_total()
            final_price = discount.apply(total)
            print("\n———— 结算 ————")
            print(f"原价：￥{total}")
            print(f"折后价：￥{final_price}")
            print("——————————\n")

        # 退出
        elif choice == "6":
            print("感谢使用购物车系统！")
            break

        else:
            print("无效输入，请重新选择！")


if __name__ == "__main__":
    main()