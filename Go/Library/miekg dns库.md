[miekg/dns]([https://github.com/miekg/dns](https://github.com/miekg/dns))这是一个用于 Go 语言的 DNS 库，它提供了丰富的功能来处理 DNS 查询、响应、解析和构建 DNS 消息。

# 主要功能

1. DNS 查询与响应：
    - 支持各种类型的 DNS 查询（如 A、AAAA、MX、NS、TXT 等）。
    - 支持发送和接收 DNS 消息。
2. DNS 消息构建与解析：
    - 提供便捷的方法来构建 DNS 消息（如请求和响应）。
    - 能够解析 DNS 消息并提取所需信息。
3. DNS 服务器：
    - 可以用来构建自定义的 DNS 服务器。
    - 支持处理多种类型的 DNS 请求。
4. 扩展性：
    - 支持扩展和自定义，允许用户添加自己的功能和处理逻辑。

###### 安装
```bash
go get github.com/miekg/dns
```

接下来可以写一个基础的代码：
```go
package main

import (
	"fmt"
	"github.com/miekg/dns"
)

func main() {
	// 构造一个新的 DNS 请求消息
	m := new(dns.Msg)

	// 注意最后有个 . ，这是 DNS 协议里表示“根结尾”，规范格式。
	m.SetQuestion("example.com.", dns.TypeA)  // 设置要查询的域名和查询类型

	// 创建 DNS 客户端
	c := new(dns.Client)

	// 发送请求到 DNS 服务器（例如 8.8.8.8）
	resp, _, err := c.Exchange(m, "8.8.8.8:53")  // 第二个返回值是 `rtt`（请求耗时），这里没有
	if err != nil {
		panic(err)
	}

	// 遍历输出结果
	for _, ans := range resp.Answer {
		fmt.Println(ans.String())
	}
}

```
解释：
- `dns.Msg` 是“DNS 消息”，无论你是客户端还是服务器，请求和响应都要用这个结构。
    
- `new(dns.Msg)` 创建一个新的 DNS 请求。
    
- `SetQuestion("example.com.", dns.TypeA)` 设置我们想查询的内容：
    
    - `"example.com."` 是目标域名，注意最后有个 **`.`**，这是 DNS 协议里表示“根结尾”，规范格式。注意有`.` 否则某些解析器会认为是局域网域名（例如变成 `example.com.local`）。
        
    - `dns.TypeA` 表示我们要查询 IPv4 地址（A 记录）。
	    - `dns.TypeA` 是常用的类型之一，常见的还有：

		- `dns.TypeAAAA`：IPv6 地址
    
		- `dns.TypeMX`：邮件交换记录
    
		- `dns.TypeTXT`：文本记录

- `dns.Client` 是客户端结构，用它发送请求。
    
- `c.Exchange(m, "8.8.8.8:53")` 表示：
    
    - `m` 是我们刚刚创建的查询请求
    - Exchange是同步函数，会等待服务器响应。
    - `"8.8.8.8:53"` 是 Google 的公共 DNS 地址和端口（DNS 默认端口是 53）

我们来看另一种方法：
```go
func Demo() {  
    var msg dns.Msg  
    // 将域名转换为 FQDN：结尾自动加上 .    fqdn := dns.Fqdn("example.com")  
    msg.SetQuestion(fqdn, dns.TypeA)  
    // in 是 DNS 服务器返回的响应消息  
    in, err := dns.Exchange(&msg, "8.8.8.8:53")  
  
    if err != nil {  
       panic(err)  
    }  
  
    if len(in.Answer) < 1 { // 没有记录  
       fmt.Println("No records")  
       return  
    }  
    for _, answer := range in.Answer {  
       if a, ok := answer.(*dns.A); ok { // answer.(*dns.A)：断言类型为 dns.A          fmt.Println(a.A)  
       }  
    }  
}
```

综上，你可以new一个msg，或者通过定义变量的方式，传递你要查询的域名，注意，new的话需要在域名后面拼接一个`.` 
# 两种方式创建`dns.Msg` 对象

| 方式   | 语法                    | 说明                               |
| ---- | --------------------- | -------------------------------- |
| 方法 1 | `msg := new(dns.Msg)` | 用 `new` 创建一个指针，类型是 `*dns.Msg`    |
| 方法 2 | `var msg dns.Msg`     | 直接声明一个变量，类型是 `dns.Msg`，是值类型（非指针） |


-  `new(dns.Msg)`，函数传参时直接用 `msg`，因为它已经是指针。
    
-  `var msg dns.Msg`，传参时要写成 `&msg`，因为 `Exchange` 需要指针。
    

比如：

```go
msg := new(dns.Msg)
msg.SetQuestion("example.com.", dns.TypeA)
dns.Exchange(msg, "8.8.8.8:53")
```

和：

```go
var msg dns.Msg
msg.SetQuestion("example.com.", dns.TypeA)
dns.Exchange(&msg, "8.8.8.8:53")
```

这两种写法 **功能一模一样**，你想用哪一种都可以。

---

### 注意要加`.`
加`.`，但**不是因为用了 `new()` 就必须拼 `.`**，而是：

#### DNS 协议要求：**查询的域名必须是 FQDN（以点结尾）**

所以**无论你怎么创建 `msg`，你都应该保证你传进去的域名是完整的 FQDN**。

你可以手动拼接：

```go
msg.SetQuestion("example.com.", dns.TypeA)
```

也可以用库函数自动帮你拼好：

```go
fqdn := dns.Fqdn("example.com") // 自动加点 → example.com.
msg.SetQuestion(fqdn, dns.TypeA)
```

#### 总结：

| 情况     | 正确做法                                |
| ------ | ----------------------------------- |
| 自己写字符串 | 加上 `.`：例如 `"example.com."`          |
| 为了保险起见 | 用 `dns.Fqdn("example.com")` 自动补 `.` |


>  1. `new(dns.Msg)` 和 `var msg dns.Msg` 都可以创建消息对象  
>  2. 传参时记得：`new` 不用加 `&`，`var` 要加 `&`  
>  3. 重点在于域名必须是 **全限定域名（FQDN）**，即结尾有 `.`  
>  4. 推荐用 `dns.Fqdn()`，避免手动漏掉 `.` 而导致查询失败

# 关于Exchange
有两种方法：
1. dns.Exchange() —— 快捷调用
2. **使用 dns.Client —— 灵活可控**
```go
in, err := dns.Exchange(&msg, "8.8.8.8:53")
```
这是一个 **封装好默认设置的简洁版本**，底层其实就是：
```go
client := new(dns.Client)
return client.Exchange(msg, addr)
```
## 方式1：dns.Exchange() —— 快捷调用
### 特点：

- 快捷：适合简单用例，几行代码就能发 DNS 请求。
    
- 内部自动创建一个 `dns.Client` 对象。
    
- 使用的是默认配置（比如 UDP 协议、2 秒超时等）。
    

### 缺点：

- **无法自定义任何客户端参数**，比如：
    
    - 是否使用 TCP？
        
    - 超时时间？
        
    - 本地地址绑定？
        
    - 自定义 DNS 解析重试策略？
## 方式2：使用 dns.Client —— 灵活可控
```go
c := new(dns.Client)
in, _, err := c.Exchange(&msg, "8.8.8.8:53")
```
适合对网络配置有特殊需求或想做进一步的拓展，你可以设置 `dns.Client` 结构体中的很多参数：
```go
c := &dns.Client{
    Net:     "udp",       // 或 "tcp"
    Timeout: 3 * time.Second,
    // UDPSize: 4096,
    // SingleInflight: true,
    // Dialer: 自定义 Dial 函数
}

```

| 字段名            | 作用                                         |
| -------------- | ------------------------------------------ |
| Net            | 使用的网络协议：`udp`、`tcp`、`tcp-tls`、`https`（DoH） |
| Timeout        | 设置超时时间                                     |
| Dialer         | 使用自定义 `net.Dialer`                         |
| UDPSize        | 设置 UDP 报文大小（默认 512，EDNS 支持更大）              |
| SingleInflight | 多个请求合并为一次请求（缓存用）                           |

## 比如：你要查询 DNS over TCP（例如防止被污染）

```go
c := &dns.Client{
    Net: "tcp",
    Timeout: 5 * time.Second,
}
msg := new(dns.Msg)
msg.SetQuestion(dns.Fqdn("google.com"), dns.TypeA)
in, _, err := c.Exchange(msg, "8.8.8.8:53")
```

---

## 总结对比表

| 比较项           | `dns.Exchange()`    | `client.Exchange()` |
| ------------- | ------------------- | ------------------- |
| 简洁            | ✅                   | ❌（多一步创建）            |
| 自定义配置         | ❌                   | ✅                   |
| 协议切换（UDP/TCP） | ❌                   | ✅                   |
| 更适合谁          | 初学者、快速测试            | 进阶用户、复杂场景           |
| 可控性           | 低                   | 高                   |
| 本质            | 自动创建一个 `dns.Client` | 你手动创建并配置            |

---

## 推荐用法：

| 场景                  | 推荐方式               |
| ------------------- | ------------------ |
| 快速写个脚本查域名 IP        | `dns.Exchange()`   |
| 需要自定义协议、超时、使用 TCP   | `dns.Client`       |
| 做 DNS 工具或服务端、需要复用连接 | `dns.Client`（支持优化） |

---

如果你想进一步玩转，比如实现：

- 支持 TCP/UDP 自动切换
    
- 查询 DoH（DNS-over-HTTPS）
    
- 同时查多个服务器比较响应
    
- 加缓存/并发/超时重试机制
    

这些都必须用 `dns.Client` 来完成。


# 子域名猜测
## 命令行参数解析
#### 什么是命令行参数 解析
比如在一个函数中，传入了很多运行参数，比如要扫描哪个域名、用哪个字典、使用几个并发线程等。
如果你的程序不能接收这些参数，那每次都得**写死在代码里改来改去**，太麻烦、太不优雅了。
于是 Go 提供了一个非常强大的标准库：`flag`，专门做这个事情。

例如：
```go
package main

import (
  "flag"
)

func main() {
  var (
    flDomain      = flag.String("domain", "", "The domain to perform guessing against.")
    flWordlist    = flag.String("wordlist", "", "The wordlist to use for guessing.")
    flWorkerCount = flag.Int("c", 100, "The amount of workers to use.")
    flServerAddr  = flag.String("server", "8.8.8.8:53", "The DNS server to use.")
  )
    flag.Parse()
}
```

这里定义了 4 个命令行参数，每一个都表示某个配置项：

|参数名|示例|类型|说明|
|---|---|---|---|
|`-domain`|`-domain example.com`|`string`|要爆破的主域名|
|`-wordlist`|`-wordlist words.txt`|`string`|存放所有待猜子域名的字典文件路径|
|`-c`|`-c 100`|`int`|工作线程数量，控制并发度|
|`-server`|`-server 1.1.1.1:53`|`string`|要使用的 DNS 服务器地址，默认是 `8.8.8.8:53`|

这些参数分别用 `flag.String` 或 `flag.Int` 来声明：

- 第一个参数是命令行参数名（不带 `-`）
    
- 第二个参数是默认值
    
- 第三个参数是该参数的说明文字（会出现在 `-h` 帮助中）
    

---

```go
flag.Parse()
```

最后这行代码**触发参数解析**，告诉 Go 去读取命令行传入的实际值并填入你定义的变量中。

当你写完上面这段代码，然后运行程序：

```bash
go run main.go -domain example.com -wordlist words.txt -c 300 -server 1.1.1.1:53
```

你会得到如下变量值：

```go
*flDomain     => "example.com"
*flWordlist   => "words.txt"
*flWorkerCount => 300
*flServerAddr => "1.1.1.1:53"
```

注意⚠️：这些变量的类型是**指针（*string, *int）**，所以你访问时要写成 `*flDomain`，不是直接 `flDomain`。
## 总结

| 步骤                | 说明                               |
| ----------------- | -------------------------------- |
| 引入 `flag` 包       | 处理命令行参数                          |
| 定义参数              | 用 `flag.String()` 和 `flag.Int()` |
| 调用 `flag.Parse()` | 开始解析命令行参数                        |
| 访问参数值             | 通过 `*变量名` 获取实际值                  |
> 注意：可能已经注意到这个示例违反了Unix条例，因为示例中定义了非可选的参数。请随意使用 _os.Args_。我们只是发现 `flag` 包更简单、更快。

# 手动解析 `os.Args`
```go
package unit  
  
import (  
    "fmt"  
    "os"    "strconv"    "testing")  
  
func parseArgs(args []string) (domain, wordlist, server string, workers int) {  
    // 设置默认值  
    domain = "baidu.com"  
    wordlist = ""  
    server = "8.8.8.8:53"  
    workers = 100  
  
    // 简单的参数解析  
    for i := 0; i < len(args); i++ {  
       switch args[i] {  
       case "-domain":  
          if i+1 < len(args) {  
             domain = args[i+1]  
             i++  
          }  
       case "-wordlist":  
          if i+1 < len(args) {  
             wordlist = args[i+1]  
             i++  
          }  
       case "-server":  
          if i+1 < len(args) {  
             server = args[i+1]  
             i++  
          }  
       case "-c":  
          if i+1 < len(args) {  
             if v, err := strconv.Atoi(args[i+1]); err == nil {  
                workers = v  
             }  
             i++  
          }  
       }  
    }  
    return  
}  
  
func TestUseArgs(t *testing.T) {  
    // 模拟命令行参数  
    os.Args = []string{"test", "-domain", "example.com", "-wordlist", "dict.txt", "-server", "1.1.1.1:53", "-c", "50"}  
  
    // 去掉第一个参数（程序名）  
    args := os.Args[1:]  
  
    // 解析参数  
    domain, wordlist, server, workers := parseArgs(args)  
  
    // 输出测试值  
    fmt.Println("domain:", domain)  
    fmt.Println("wordlist:", wordlist)  
    fmt.Println("server:", server)  
    fmt.Println("workers:", workers)  
  
    // 测试断言  
    if domain != "example.com" {  
       t.Errorf("Expected domain to be example.com, got %s", domain)  
    }  
}
```

## 实际应用场景

### 构建命令行工具（CLI 工具）

手动解析 `os.Args` 的方式非常适合用来开发：

- 域名探测工具（子域爆破、DNS记录解析）
    
- 文件扫描器、安全测试脚本
    
- 数据处理工具（比如 `grep`、`cat`、`mv` 的 Go 版本）
    
- 网络工具（如 ping、curl 的精简版）
    

比如：

```bash
./subdomain_finder -domain baidu.com -wordlist dict.txt -server 8.8.8.8:53 -c 100
```

你的 `main()` 函数只需要用 `parseArgs(os.Args[1:])` 来获取参数，逻辑就非常清晰。

---

### 测试参数行为（尤其是在单元测试中）

`flag.Parse()` 只能调用一次，而 `os.Args` 是 **可控的全局变量**，你可以在测试中轻松模拟各种参数组合。

**例如测试一个错误的端口：**

```go
os.Args = []string{"test", "-server", "invalid:abc"}
```

你可以在测试函数中断言程序的容错逻辑是否处理得当。

---

### 作为嵌入式脚本或插件接口的参数解析

比如你开发的是一个插件模块，它不使用标准输入输出，而是从 `os.Args` 中读取命令。

- 可以内嵌到 CI/CD 系统
    
- 可以作为其他程序调用的命令工具
    

---

### 替代 flag 包，避免副作用

在需要运行多个子命令、重复解析参数的场景中，flag 是不适合的，而 `os.Args` 的自定义解析完全避免了这些坑。

例如你写了下面的测试逻辑：

```go
func TestManyArgs(t *testing.T) {
    os.Args = []string{"tool", "-c", "10"}  // OK
    parseArgs(os.Args[1:])
    os.Args = []string{"tool", "-c", "abc"} // Wrong
    parseArgs(os.Args[1:])                 // flag 就不行了
}
```

---

## 它的用处是什么？

|用途|描述|
|---|---|
|命令行解析|支持用户自定义运行参数，例如 `-domain`、`-c`、`-server`|
|灵活性|你可以用任何风格来写参数解析（长短选项、组合参数等）|
|测试方便|可以自由在测试代码中设置 `os.Args` 模拟输入|
|跨平台无依赖|不依赖于 `flag`、`cobra`、`urfave/cli` 等库，轻量干净|
|和 UNIX 哲学一致|单一职责、文本接口、组合优于复杂结构|

---

## 总结：

| 优点          | 缺点                   |
| ----------- | -------------------- |
| 无副作用，适合测试   | 没有参数帮助（unless 你自己打印） |
| 适用于轻量化命令行工具 | 没有自动校验或类型转换          |
| 灵活可扩展       | 手动解析比使用库略繁琐          |
| 贴近系统原始输入    | 需要自己写健壮性判断逻辑         |

## 什么是wordlist

简单说：  
**`wordlist` 是一个包含大量“可能的子域名前缀”的文本文件**。  
程序会从这个文件中一行一行地读取单词，然后将每个单词拼接在目标域名的前面去尝试解析 DNS 记录。

假设你有一个目标域名是：

```
example.com
```

而你的 `wordlist.txt` 内容如下：

```
www
mail
ftp
admin
dev
```

程序读取这些行，然后自动组合出以下完整的子域名：

```
www.example.com
mail.example.com
ftp.example.com
admin.example.com
dev.example.com
```

接下来，程序会对这些子域名逐个发起 DNS 查询请求（通常查 A 记录，查看是否存在 IP），判断这个子域是否存在。
###  wordlist 来源

你可以使用一些开源字典，比如：

- [SecLists](https://github.com/danielmiessler/SecLists)（安全测试字典集合）
    
    - 路径：`Discovery/DNS/subdomains-top1million-5000.txt`
        
- 自己维护的高频子域列表
    
- 从网络爬虫/日志中提取的历史子域名

|功能|解释|
|---|---|
|子域猜测来源|用作子域名的候选前缀列表|
|字典爆破|实现 DNS 枚举的“爆破”部分|
|模拟攻击|模拟攻击者可能尝试访问的子域|
|安全审计|找到系统中暴露的开发/测试环境|
|被动信息收集|搭配 DNS 查询构建目标的网络轮廓|

- **wordlist 越大，覆盖越全，但速度越慢**
    
- 推荐做并发（Goroutines + Channel）处理，提高查询速度
    
- 有些子域名不会响应 DNS（比如 behind firewall），所以可能要加上 HTTP 验证、CDN探测等

