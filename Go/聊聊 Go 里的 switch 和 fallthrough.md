# 聊聊 Go 里的 `switch` 和 `fallthrough`

这次不想写“语法菜谱”，而是从一个你已经写过的例子入手，把 Go 的 `switch` 和 `fallthrough` 讲清楚一点，也顺便聊聊它背后的设计思路。

先看代码：

```go
package main

import (
	"fmt"
)

func fallThrough() {
	a := func() int {
		return 4
	}

	switch a() {
	case 2:
		fmt.Println("2")
		fallthrough
	case 4:
		fmt.Println("4")
		fallthrough
	case 6:
		fmt.Println("6")
		fallthrough
	default:
		fmt.Println("end")
	}
}
```

`a()` 返回的是 `4`，肉眼一看，大概能猜到会从 `case 4` 开始执行。但真正有意思的地方在于：一旦用了 `fallthrough`，`switch` 的执行规则就跟我们默认的认知有点不一样了。

## 一、没有 `fallthrough` 时，Go 的 `switch` 是“自动刹车”的

先把 `fallthrough` 全部去掉，看一下最朴素的行为：

```go
switch a() {
case 2:
	fmt.Println("2")
case 4:
	fmt.Println("4")
case 6:
	fmt.Println("6")
default:
	fmt.Println("end")
}
```

`a()` 返回 `4`，所以匹配流程是：

1. 先拿到 `a()` 的结果：`4`
2. 自上而下检查 `case`：
   - `case 2`：不匹配
   - `case 4`：匹配，执行 `fmt.Println("4")`
3. 执行完 `case 4` 的语句块后，**自动结束整个 `switch`**，不会去看 `case 6`、不会走 `default`。

这个行为有几点需要刻意记一下：

- Go 里的 `switch` **默认不“贯穿”**，不像 C 那种要写 `break` 才能停；
- 你可以把 Go 的 `switch` 理解成：
   “匹配到一个 `case` → 执行它 → 自动 `break`”。

这也是 Go 的一贯风格：减少隐性错误，把容易踩坑的地方直接在语法层面堵住。

## 二、加上 `fallthrough`：人为解除“自动刹车”

现在看你原来的代码：

```go
switch a() {
case 2:
	fmt.Println("2")
	fallthrough
case 4:
	fmt.Println("4")
	fallthrough
case 6:
	fmt.Println("6")
	fallthrough
default:
	fmt.Println("end")
}
```

执行顺序具体是这样的：

1. `a()` 返回 `4`，进入 `case 4`
2. 执行 `fmt.Println("4")`
3. 遇到 `fallthrough`
   - 不做任何判断
   - 强制跳到“下一个 `case` 语句块的第一行”
4. 执行 `case 6` 里的 `fmt.Println("6")`
5. 再次遇到 `fallthrough`，继续强制跳到 `default`
6. 执行 `fmt.Println("end")`

最终输出：

```text
4
6
end
```

有几条规则需要刻意强调一下：

- `fallthrough` 不会重新匹配条件，只是“无脑往下掉一层”；
- 它只能出现在 `case` 子句的最后一行；
- 只能一次跳到**紧挨着的下一个** `case`，不能跨层乱跳；
- 一旦用了 `fallthrough`，当前这个 `case` 的“自动 break 行为”就等于被你手动拆掉了。

## 三、类比一下：`switch` 像楼梯，`fallthrough` 像你自己推了一把

可以这么想：

- 没有 `fallthrough` 的 `switch`：
  - 你走到第 N 级台阶（匹配到某个 `case`），站稳了，就停了；
- 加上 `fallthrough` 的 `switch`：
  - 你走到第 N 级台阶后，说了一句：
    - “我不想停，再往下一层台阶滑一下。”
  - 不管你下一层台阶写的是 `case 6` 还是 `default`，都会被执行。

所以 `fallthrough` 的意思其实很直白：
 —— 本来应该在这里停下来的，**但我想再往下执行一个 case**。

## 四、几个容易误解的小点

### 1. `fallthrough` 不会重新判断条件

很多人第一眼以为是 “如果下一个 `case` 满足，就继续执行”，实际上不是。

```go
n := 4
switch n {
case 4:
	fmt.Println("4")
	fallthrough
case 100:
	fmt.Println("100")
}
```

即使 `case 100` 完全对不上 `n == 100`，只要 `4` 这个分支里写了 `fallthrough`，`"100"` 还是会被打印。

`fallthrough` 根本不看条件，它浏览器都懒得打开，直接跳到下一块执行。

### 2. 顺序非常重要

比如这样：

```go
n := 4
switch {
case n > 10:
	fmt.Println(">10")
	fallthrough
case n > 3:
	fmt.Println(">3")
}
```

这里的 `switch` 是“无标签”的写法，相当于 `switch true { ... }`。

执行流程：

- `n > 10` 为 `false`，跳过第一个
- `n > 3` 为 `true`，进入第二个 case
- 打印 `>3`
- 然后不存在下一层 `case` 了，结束

如果你写反过来：

```go
switch {
case n > 3:
	fmt.Println(">3")
	fallthrough
case n > 10:
	fmt.Println(">10")
}
```

结果会变成：

```text
>3
>10
```

第二个 `case n > 10` 明明条件是 false，但照样会执行。

这一点在写“范围逻辑”或者“级联规则”时，要格外小心逻辑的表达方式。

## 五、`fallthrough` 适合干什么？什么时候应该少用？

老实讲，Go 官方对 `fallthrough` 的态度一直比较保守：
 —— 有用，但很容易写出让人看不懂的代码。

比较合理、说得过去的使用场景，大概是这种“逐级生效”的逻辑：

### 场景一：权限等级逐层叠加

比如一个用户的权限级别从低到高：visitor、member、admin
 等级越高，具备的能力越多：

```go
func printPermission(level string) {
	switch level {
	case "admin":
		fmt.Println("可以删除用户")
		fallthrough
	case "member":
		fmt.Println("可以发帖")
		fallthrough
	case "visitor":
		fmt.Println("可以浏览")
	default:
		fmt.Println("未知权限")
	}
}
```

- 传入 `"admin"`：
  - 打印：
    - 可以删除用户
    - 可以发帖
    - 可以浏览
- 传入 `"member"`：
  - 打印：
    - 可以发帖
    - 可以浏览

这种“高等级包含低等级”的结构，用 `fallthrough` 写，逻辑反而很直观。

### 场景二：日志或提示信息逐层追加

比如根据错误级别打印信息：

```go
switch level {
case "fatal":
	fmt.Println("程序即将退出")
	fallthrough
case "error":
	fmt.Println("发生错误，需要处理")
	fallthrough
case "warn":
	fmt.Println("有潜在风险")
	fallthrough
case "info":
	fmt.Println("普通信息")
}
```

这里也是：等级越高，信息越“全”。
 如果你不用 `fallthrough`，要么重复代码，要么搞一堆 if 嵌套，整体会比较啰嗦。

### 什么时候建议别用？

- 分支逻辑本来就比较复杂；
- case 很多，而且条件之间没有“层级关系”；
- 团队里有很多不熟 Go 的人，看代码成本会变得很高。

这种情况，宁可多写几个 `case` 或多层 `if`，也比 `fallthrough` 滥用更好。

## 六、顺带说一下：Go 的 `switch` 设计思路

`fallthrough` 只是其中一个点。要理解它，顺便把 Go 的 `switch` 思路也捋一捋：

1. **默认不贯穿**
    避免像 C 那样忘写 `break` 导致一连串 case 被莫名执行；

2. **支持无标签 `switch`**

   ```go
   switch {
   case x > 10:
   case x > 5:
   }
   ```

   等价于 `switch true`，更像 if-else 链；

3. **支持 `type switch`**
    面向接口类型做分支：

   ```go
   switch v := x.(type) {
   case int:
       fmt.Println("int", v)
   case string:
       fmt.Println("string", v)
   }
   ```

你可以把 Go 的 `switch` 当成一个“半高级”的控制结构：
 比 `if-else` 强一点，比模式匹配（比如一些函数式语言）简单一点。
 `fallthrough` 就是它给你留的一扇“后门”，让你可以偶尔写出“沿路往下执行”的逻辑。

## 七、总结

1. Go 的 `switch`：
   - 匹配一个 `case` 后，默认自动结束，不贯穿。
2. `fallthrough` 的作用：
   - 不看条件、强制执行下一个 `case` 的语句块。
3. 使用时的注意点：
   - 只能写在 `case` 的最后一行；
   - 只会跳到“紧挨着的下一个 case”，不会多级跳；
   - 过度使用会让逻辑变得很难读。
4. 比较适合的使用场景：
   - 权限、等级这种“高包含低”的叠加逻辑；
   - 多层提示、日志逐级输出的场景。

你可以把 `fallthrough` 当作一种“我很确定自己在干什么”的语法开关。
 正常写业务代码时，你完全可以一行也不用；
 但一旦你碰到那种“本来就该从这个等级一路往下生效”的场景，它刚好能帮你把逻辑写得既短又清晰。