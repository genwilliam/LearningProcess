earth_weight = 100

# 月球重力比例
moon_ratio = 0.165

# 每年体重增加
INCREASE = 0.5

# 计算未来10年
print("年 | 地球体重(kg) | 月球体重(kg)")
for year in range(1, 11):
    # 计算当前年的月球体重
    moon_weight = earth_weight * moon_ratio
    print(f"{year:2d} | {earth_weight:10.2f} | {moon_weight:10.2f}")

    # 下一年地球体重增加
    earth_weight += INCREASE
