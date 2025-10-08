# **Linux I/O **

## **文件描述符与标准 I/O**

Linux 中每个进程默认有三个文件描述符（FD）：

| **文件描述符** | **名称** | **默认指向** | **用途**               |
| -------------- | -------- | ------------ | ---------------------- |
| 0              | stdin    | 终端输入     | 接收用户输入，管道输入 |
| 1              | stdout   | 终端输出     | 正常输出数据           |
| 2              | stderr   | 终端输出     | 错误信息输出           |

- & 在重定向语法中表示 **文件描述符**，如 2>&1 表示 stderr 指向 stdout 的目标。

## **输出重定向（stdout）**

- **覆盖输出（会覆盖文件的内容）**：

```
command > file.txt
```

- **追加输出（在文件末尾追加）**：

```
command >> file.txt
```

- 示例：

```
ls /home > list.txt   # stdout 写入 list.txt
```



## **错误重定向（stderr）**

- **覆盖错误输出**：

```
command 2> error.txt
```

- **追加错误输出**：

```
command 2>> error.txt
```

- 示例：

```
ls /fake/directory 2> error.txt
```



## **同时重定向 stdout 和 stderr**

1. **标准方法**：

```
command > file.txt 2>&1
```

- stdout 先重定向到文件
- stderr 再重定向到 stdout 指向的文件



1. **Bash 简写（4+）**：

```
command &> file.txt
```

- 等价于 `> file.txt 2>&1`
- 注意：非 Bash Shell 可能不支持 &>



1. **追加方式**：

```
command >> file.txt 2>&1
command &>> file.txt  # Bash 简写
```



## **输入重定向（stdin）**



- **从文件读取输入**：

```
command < input.txt
```

- 示例：

```
cat < peanuts.txt > banana.txt
```



- 等价于：

```
cat peanuts.txt > banana.txt
```

> 区别：< 是将文件作为 stdin，适合管道或复杂脚本。



## **Linux 文件类型与 I/O 相关**



| **文件类型** | **符号** | **I/O 特性**             |
| ------------ | -------- | ------------------------ |
| 普通文件     | -        | 可读写、可重定向         |
| 目录         | d        | 不能直接写入，ls 可列出  |
| 符号链接     | l        | 跟随目标文件 I/O         |
| 块设备       | b        | 按块访问，如硬盘、USB    |
| 字符设备     | c        | 按字符访问，如终端、键盘 |
| FIFO 管道    | p        | 先进先出队列，进程间通信 |
| 套接字       | s        | 网络通信或本地进程间通信 |



- 文件描述符可以指向这些类型的文件，实现 I/O 重定向和通信。



## **背景执行与 I/O**



- 命令末尾 & → 后台执行命令

  

  - 输出仍默认到终端，需配合重定向：

  

```
long_task > log.txt 2>&1 &
```



- 这样后台运行时，stdout + stderr 都记录到文件。



## **常见注意事项**



1. **顺序很重要**

```
command 2>&1 > file.txt  # ❌ 不同于 > file.txt 2>&1
```

- stdout 先重定向，stderr 才跟随



2. **避免覆盖源文件**

> 如果写入到`/dev/null`就是丢弃内容，写入到`dev/null`的东西都会被抛弃

```
cat file > file   # ❌ 会清空原文件
```



1. **最小化环境可能没有 man 页**

   

   - 使用 whatis、man 查询命令时，可能因为 man 文件不存在而返回空
   - 可通过安装 man-db、manpages 或使用完整镜像解决

   

2. **管道与 stdin**

   

   - < 用于将文件作为标准输入
   - 与管道结合可实现复杂 I/O 流处理：

   



```
grep "hello" < input.txt | sort > output.txt
```



## **总结记忆**

- **标准流**：0 stdin → 输入 | 1 stdout → 输出 | 2 stderr → 错误
- **重定向顺序**：先 stdout，再 stderr (> file 2>&1)
- **快捷写法**：&> → Bash 全输出重定向
- **后台执行**：命令末尾 & → 后台执行，可配合 I/O 重定向
- **文件类型**影响 I/O：普通文件、设备文件、管道、套接字各有用途



> 建议：在写脚本或收集日志时，把 stdout、stderr 明确分开或统一重定向，并注意文件描述符顺序，避免数据丢失。