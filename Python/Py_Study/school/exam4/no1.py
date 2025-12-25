import statistics

def main():
    scores = []
    print("请输入10个成绩（整数，范围 0 到 100）：")

    while len(scores) < 10:
        try:
            score_input = input(f"请输入第{len(scores)+1}个成绩：")
            score = int(score_input)

            if 0 <= score <= 100:
                scores.append(score)
            else:
                print("成绩必须在 0 到 100 之间！")
        except ValueError:
            print("请输入有效的整数！")

    # 计算统计值
    average = round(statistics.mean(scores), 1)
    std_dev = round(statistics.stdev(scores), 1)
    median = statistics.median(scores)
    pass_rate = round((sum(1 for s in scores if s >= 60) / len(scores)) * 100, 1)

    # 输出结果
    print("\n统计结果：")
    print(f"平均值：{average}")
    print(f"标准差：{std_dev}")
    print(f"中位数：{median}")
    print(f"及格率：{pass_rate}%")

if __name__ == "__main__":
    main()