def weighted_average(scores, credits):
    if len(scores) != len(credits):
        raise ValueError("成绩列表与学分列表长度不一致！")

    total_weighted_score = sum(score * credit for score, credit in zip(scores, credits))
    total_credits = sum(credits)

    average = round(total_weighted_score / total_credits, 2)
    return average


# 数据列表
credits = [6, 4, 3, 3, 4, 2]  # 学分列表
scores = [90, 85, 88, 95, 70, 78]  # 成绩列表

# 计算加权平均分
avg = weighted_average(scores, credits)
print(f"加权平均分为：{avg}")