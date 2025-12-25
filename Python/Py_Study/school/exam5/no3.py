import jieba
from collections import Counter
from wordcloud import WordCloud
import matplotlib.pyplot as plt
import re


def analyze_characters():

    with open("/doc/novel.txt", "r", encoding="utf-8") as file:
        raw_text = file.read()

    clean_text = re.sub(r"[^\u4e00-\u9fa5]", "", raw_text)


    custom_names = ["悟空", "悟能", "悟净", "唐僧", "菩萨"]
    for name in custom_names:
        jieba.add_word(name, freq=20000)

    tokens = jieba.lcut(clean_text)


    remove_list = {"那里", "说道", "起来", "什么", "不是", "我们", "你们", "他们"}
    filtered = [t for t in tokens if len(t) > 1 and t not in remove_list]

    alias_dict = {
        "孙悟空": "悟空", "行者": "悟空", "大圣": "悟空",
        "猪八戒": "悟能", "八戒": "悟能",
        "沙和尚": "悟净", "沙僧": "悟净",
        "唐三藏": "唐僧", "三藏": "唐僧",
        "观音": "菩萨", "观世音": "菩萨"
    }

    normalized = [alias_dict.get(word, word) for word in filtered]

    # 统计词频
    freq = Counter(normalized)
    top5_people = freq.most_common(5)

    print("\n《西游记》中出现次数最多的五位人物：")
    for idx, (name, count) in enumerate(top5_people, 1):
        print(f"{idx}. {name} —— {count} 次")

    # 生成词云
    merged_words = " ".join(normalized)

    wc = WordCloud(
        font_path="C:\\Windows\\Fonts\\simhei.ttf",
        background_color="white",
        width=900,
        height=650,
        max_words=180,
        max_font_size=140
    ).generate(merged_words)

    plt.rcParams["font.sans-serif"] = ["SimHei"]
    plt.figure(figsize=(11, 8))
    plt.imshow(wc, interpolation="bilinear")
    plt.axis("off")
    plt.title("《西游记》人物出现词云", fontsize=18)
    plt.show()

    wc.to_file("novel_characters_cloud.png")
    print("\n词云图已保存为：novel_characters_cloud.png")


analyze_characters()