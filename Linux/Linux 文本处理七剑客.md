# **Linux 文本处理七剑客**



这些命令的共同点是：

它们都是 “**过滤器（filter）**” —— 从输入中读数据，处理后吐出结果。

这也是 Unix 哲学的核心之一：“**让程序只做好一件事**”。



------





## **1.** **env—— 环境变量**





在 Linux 中，几乎所有程序都依赖“环境变量（Environment Variables）”，比如：



- PATH 决定去哪找可执行文件；
- HOME 指明用户家目录；
- LANG 决定语言与编码。





env 命令的作用，就是**查看、修改、或者带特定环境运行命令**。





### **查看当前环境变量**



```
env
```

输出一堆：

```
USER=william
HOME=/home/william
PATH=/usr/local/bin:/usr/bin:/bin
...
```



### **临时修改环境变量运行命令**



```
env LANG=C ls
```

这会在英语环境下执行 ls，不会影响你全局的 LANG。



**小结：**

> env 让你看到 Linux 程序运行的“生态环境”。



------





##  2.*cut*—— 精准剪刀手 





顾名思义，cut 是用来“切片”的。

它能从每行文本中取出你想要的部分，比如列或字符。





### **按分隔符取列**



```
cut -d ':' -f 1 /etc/passwd
```

意思是：



- -d ':' 表示以冒号为分隔符；
- -f 1 表示取第1列。





结果就是用户名列表。





### **按字符位置取内容**



```
echo "hello world" | cut -c 1-5
```

输出：

```
hello
```

**小结：**

> cut 就像 Excel 的“选中第几列”功能，但在命令行上更酷。



------





## **3.** **paste**—— 合并大师



paste 的作用正好与 cut 相反。

它是**把多个文件的行并排粘贴**在一起。



比如：

```
cat names.txt
Alice
Bob
Charlie

cat scores.txt
90
85
100
```

执行：

```
paste names.txt scores.txt
```

输出：

```
Alice   90
Bob     85
Charlie 100
```

**小结：**

> cut 是拆分，paste 是拼合。

> 二者搭配使用，天下无敌。



------





## **4.** **head**&**tail**—— 文本浏览双雄



这俩命令几乎是每个 Linux 用户都会用的“查看神器”。





### **👀** **head**：看前几行



```
head -n 5 filename.txt
```

显示文件的前5行（默认10行）。





### **tail：看后几行**



```
tail -n 10 syslog
```

显示日志文件最后10行。





### **实时监控日志**



```
tail -f /var/log/syslog
```

-f 意思是 “follow”，会持续输出新行。

就像看日志直播——**程序一打印，你就能看到。**



**小结：**

> head + tail = “只看重点”，不用全翻完！



------





## **5.** **expand**与unexpand—— 空格与制表符的魔术师



这俩命令是一对反向工具，专门处理**制表符（tab）**。



### *expand*：把 tab 变成空格



```
expand file.txt
```

制表符会被空格替换，常用于保证对齐一致。





### **unexpand：把空格变回 tab**



```
unexpand -a file.txt
```

适用于节省文件体积或遵守某些格式规范。



**小结：**

> expand 和 unexpand 是排版小助手，帮你搞定“空格地狱”。



------





## **6.** **join—— 文本版“SQL JOIN”**





没错！Linux 也有自己的“JOIN”操作。

它能根据某个“键”把两份文件按行对齐，就像数据库里的表连接。



比如：

```
cat users.txt
1 Alice
2 Bob
3 Charlie

cat scores.txt
1 90
2 85
3 100
```

执行：

```
join users.txt scores.txt
```

输出：

```
1 Alice 90
2 Bob 85
3 Charlie 100
```

**小结：**

> join = 数据库的“内连接（INNER JOIN）”。

> 对数据表格处理特别有用。



------





## **7.** **split—— 文件分割器**





有时候文件太大（比如几十G的日志），我们就可以用 split 拆成小块。

```
split -l 1000 bigfile.txt part_
```

这会把大文件每 1000 行拆成一个文件：

```
part_aa
part_ab
part_ac
...
```

你甚至可以：

```
cat part_* > bigfile.txt
```

重新拼回来。



**小结：**

> split = 文件界的“切割刀”，方便分段处理大文件。



------





## **8.** **tr**—— 字符变换器





tr（translate）是最灵活的小工具之一，能替换、删除、压缩字符。





### **替换**



```
echo "hello linux" | tr 'a-z' 'A-Z'
```

输出：

```
HELLO LINUX
```



### **删除字符**



```
echo "123abc456" | tr -d '0-9'
```

输出：

```
abc
```



### **去重连续字符**



```
echo "a     b" | tr -s ' '
```

输出：

```
a b
```

**小结：**

> tr 就像文本清洗器。

> 字符替换、过滤、规范化，全靠它！



------





## **9.** **uniq—— 去重神器**





uniq 的名字就是“unique”，作用是**去掉连续重复的行**。

```
cat list.txt
apple
apple
banana
banana
cherry

uniq list.txt
```

输出：

```
apple
banana
cherry
```



### **加上** **-c参数还能计数**



```
uniq -c list.txt
```

输出：

```
2 apple
2 banana
1 cherry
```

 **小结：**

> 注意：uniq 只去掉**连续**重复的行！

> 记得先 sort 一下👇

```
sort list.txt | uniq
```



## **10.** **wc**与 **nl**—— 统计员与编号员



### ***wc***：统计文件信息（word count）



```
wc file.txt
```

输出：

```
12 45 301 file.txt
```

代表：



> 行数（12）、单词数（45）、字符数（301）



你可以用参数细分：



- -l 行数
- -w 单词数
- -c 字节数







###  **nl：给每行加编号（number lines）**



```
nl file.txt
```

输出：

```
     1  First line
     2  Second line
```

**小结：**

> wc 统计，nl 编号。

> 一个负责分析，一个负责整齐排版。



------





## **11.** **grep** **—— 文本搜索的灵魂工具**





“**给我一句话，我能在百万行日志里找到它。**”

这就是 grep。





### **基本用法**



```
grep "error" logfile.txt
```

匹配并输出所有包含 “error” 的行。





### ** 显示行号**



```
grep -n "error" logfile.txt
```



### **反向匹配**



```
grep -v "info" logfile.txt
```

输出**不包含 info** 的行。





### **正则匹配**



```
grep -E "foo|bar" file.txt
```

匹配 foo 或 bar。



**小结：**

> grep 是 Linux 世界的“放大镜”。

> 想查日志、过滤输出，它是第一选择。



------





# **总结大表**



| **命令**          | **功能**           | **关键词** |
| ----------------- | ------------------ | ---------- |
| env               | 查看环境变量       | 环境配置   |
| cut               | 按列剪切文本       | 切片       |
| paste             | 横向合并文件       | 拼接       |
| head / tail       | 查看文件头/尾      | 快速预览   |
| expand / unexpand | Tab 与空格互转     | 排版       |
| join              | 文件按键合并       | 数据表关联 |
| split             | 按行或大小分割文件 | 拆分大文件 |
| tr                | 字符替换/删除/压缩 | 文本清洗   |
| uniq              | 去重统计           | 唯一化     |
| wc                | 统计行、词、字节   | 计数       |
| nl                | 给行编号           | 格式化     |
| grep              | 搜索匹配           | 文本查找   |



------





# **最后一点感悟**





这些命令看似简单，

但组合起来——就能构建出惊人的数据处理能力。



比如：

```
cat access.log | grep "404" | cut -d ' ' -f 1 | sort | uniq -c | sort -nr | head
```

这一行，就能告诉你：



> “哪些 IP 发出了最多的 404 请求。”



—— 这，就是 Linux 命令行的魔力。



------



想真正学懂 Linux，

别怕命令长、多、难记。

它们其实是一种“语言”，

一旦你能读懂这些小命令在“说什么”，

就能开始**和系统对话**啦 🧑‍💻✨