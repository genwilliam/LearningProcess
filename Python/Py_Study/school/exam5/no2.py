import csv  # 处理 CSV 文件格式


def analyze_students():
    # 存放每个学生的最终结果
    results = []

    # 用于统计各科累计成绩
    subjects_sum = {
        "C语言": 0.0,
        "高等数学": 0.0,
        "思想政治": 0.0,
        "计算机基础": 0.0
    }

    # 科目权重（固定）
    weight_map = {
        "C语言": 0.35,
        "高等数学": 0.30,
        "思想政治": 0.20,
        "计算机基础": 0.15
    }

    num_students = 0  # 统计人数

    # 读取 CSV 文件内容
    with open("student_dataset.csv", "r", encoding="gbk") as file:
        csv_reader = csv.DictReader(file)

        for row in csv_reader:
            num_students += 1
            stu_name = row.get("姓名", "")
            stu_id = row.get("学号", "")

            # 从 CSV 中提取成绩并转换为 float（若为空则记为 0）
            c_score = float(row["C语言成绩"].strip() or 0)
            math_score = float(row["高数成绩"].strip() or 0)
            politics_score = float(row["思修成绩"].strip() or 0)
            comp_score = float(row["计算机基础成绩"].strip() or 0)

            # 计算加权平均分
            weighted = (
                c_score * weight_map["C语言"]
                + math_score * weight_map["高等数学"]
                + politics_score * weight_map["思想政治"]
                + comp_score * weight_map["计算机基础"]
            )

            results.append({
                "姓名": stu_name,
                "学号": stu_id,
                "加权平均分": round(weighted, 2)
            })

            # 累加总分
            subjects_sum["C语言"] += c_score
            subjects_sum["高等数学"] += math_score
            subjects_sum["思想政治"] += politics_score
            subjects_sum["计算机基础"] += comp_score

    # 计算各科平均成绩
    averages = {
        subject: round(total / num_students, 2)
        for subject, total in subjects_sum.items()
    }

    # 输出每位学生的加权成绩
    print("=" * 55)
    print("学生加权平均成绩列表:")
    for info in results:
        print(f"姓名：{info['姓名']:>4} | 学号：{info['学号']:>10} | 加权平均分：{info['加权平均分']:>6.2f}")

    # 输出科目平均分
    print("\n" + "=" * 55)
    print("各科平均成绩:")
    for sub, avg in averages.items():
        print(f"{sub:>8}：{avg:.2f} 分")


# 执行程序
analyze_students()