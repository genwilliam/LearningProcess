# Go 结构体与指针详解

## 一、结构体是什么？

在 Go 中，`struct`（结构体）就像是一个小“数据包”，可以把多个不同类型的变量打包成一个整体。

```go
type User struct {
	ID      int
	Name    string
	address string
	Score   float64
}
```

你可以把它想成是一个“用户”的模具，
 以后每次用这个模具造出来的对象（`User`）都长一个样：
 里面有 `ID`、`Name`、`address`、`Score` 这些字段。

------

## 二、结构体的使用

```go
var u = User{ID: 100, Name: "william", address: "cn", Score: 90.2}
fmt.Println(u)
```

Go 会自动为没赋值的字段使用“零值”：

- `int` → `0`
- `bool` → `false`
- `string` → `""`

当然，你也可以省略字段名，但必须按照定义顺序传值。

------

## 三、结构体方法（method）

```go
func (u User) say() {
	fmt.Println("hello", u.Name)
}
```

- `(u User)` 表示“方法接收者”，意思是这个方法属于 `User`。

- 必须通过实例来调用：

  ```go
  u.say()
  ```

方法接收者可以是值类型或指针类型。
 如果你改成：

```go
func (u *User) say() { ... }
```

那么这个方法的接收者就是指针类型，通常用于在方法内部修改结构体字段。

------

## 四、匿名结构体

有时候，你只想在函数内部临时用一个结构体，不想单独定义类型，就可以用匿名结构体：

```go
var student struct {
	name string
	age  int
}
student.name = "Peter"
student.age = 35
fmt.Println(student)
```

匿名结构体像一次性杯子，用完就扔，不能复用。

------

## 五、取地址符号 & 和解引用 *

```go
u2 := &u // 取址符号，u2 是 *User 类型
fmt.Println("u的地址", &u, "u2的地址", &u2)
```

### 1. &：取地址

`&u` 表示“拿到变量 u 的地址”，类型是 `*User`。
 可以理解成：“告诉我这栋房子在哪”。

### 2. *：解引用

`*u2` 表示“去那个地址找到结构体本身”。

```go
fmt.Println((*u2).Name)
```

### 3. 自动解引用

Go 编译器会自动帮你加上 `*`，所以可以直接写：

```go
u2.Name // 等价于 (*u2).Name
```

------

## 六、fmt.Println 打印结构体与指针的行为

当你打印结构体或指针时，Go 会自动决定打印什么：

```go
fmt.Println(&u)
```

输出：

```
&{100 william cn 90.2}
```

这是因为 `fmt` 包会检测类型，如果类型是结构体指针，它会自动展开字段。
 如果你打印双重指针，比如：

```go
fmt.Println(&u2)
```

输出类似：

```
0x14000110038
```

因为 `**User` 没有定义格式化逻辑，只能打印内存地址。

------

## 七、实现 String() 方法

如果你想控制打印格式，可以为结构体实现 `String()` 方法。

```go
func (u User) String() string {
	return fmt.Sprintf("User(%d, %s, %s, %.1f)", u.ID, u.Name, u.address, u.Score)
}
```

当你这样写后：

```go
u := User{100, "William", "CN", 90.2}
fmt.Println(&u)
```

输出：

```
User(100, William, CN, 90.2)
```

### 为什么 `&u` 也能触发 `String()`？

`fmt` 包会自动检查指针是否实现了 `fmt.Stringer` 接口，如果结构体的值类型有 `String()` 方法，Go 会自动帮指针解引用并调用它。

换句话说：

- 你实现了 `(u User) String() string`
- 打印 `&u` 时，Go 自动调用 `(*u).String()`
- 所以不需要再额外实现 `(*User).String()`。

这种行为叫做 **隐式解引用**。

------

## 八、String() 的应用场景

1. **打印更人性化**
    让结构体输出更可读：

   ```go
   fmt.Println(u)  // 默认：{100 william cn 90.2}
   // 改造后：User(ID=100, Name=william, Address=cn, Score=90.2)
   ```

2. **调试与日志**
    可以在调试时快速看到关键字段，避免打印整块内存。

3. **接口自动调用**
    `fmt.Stringer` 接口定义如下：

   ```go
   type Stringer interface {
       String() string
   }
   ```

   实现了这个方法后，任何打印函数（`fmt.Printf`、`fmt.Println` 等）都会自动调用它。

------

## 九、new 的用法

```go
u3 := new(User)
u3.Name = "John"
fmt.Println(u3.Name)
```

`new(User)` 会创建一个空结构体，并返回它的指针。
 等价于：

```go
var temp User
u3 := &temp
```

------

## 十、总结

| 概念        | 含义                   | 说明                     |
| ----------- | ---------------------- | ------------------------ |
| `&`         | 取地址                 | 获取变量的地址           |
| `*`         | 解引用                 | 通过地址取值             |
| `u`         | 值                     | 普通结构体变量           |
| `&u`        | 指针                   | 指向结构体的地址         |
| `(*u).Name` | 手动解引用访问字段     | 可以简写为 `u.Name`      |
| `String()`  | 自定义打印逻辑         | 实现 `fmt.Stringer` 接口 |
| `new(User)` | 创建空结构体并返回指针 | 常用于初始化指针对象     |

------

## 十一、完整示例

```go
package data_struct

import "fmt"

type User struct {
	ID      int
	Name    string
	address string
	Score   float64
}

func (u User) say() {
	fmt.Println("hello", u.Name)
}

// String 方法控制结构体打印格式
func (u User) String() string {
	return fmt.Sprintf("User(ID=%d, Name=%s, Address=%s, Score=%.1f)", u.ID, u.Name, u.address, u.Score)
}

func StructDemo() {
	var u = User{ID: 100, Name: "william", address: "cn", Score: 90.2}
	fmt.Println(u)
	u.say()

	var student struct {
		name string
		age  int
	}
	student.name = "Peter"
	student.age = 35
	fmt.Println(student)

	u2 := &u
	fmt.Println("u的地址", &u, "u2的地址", &u2)
	fmt.Println((*u2).Name)
	fmt.Println(u2.Name)

	u3 := new(User)
	u3.Name = "John"
	fmt.Println(u3)
}
```

------

## 十二、总的来说

> `&` 取地址，`*` 取值。
>  `u2 := &u` 拿到“房子的门牌号”，
>  `u2.Name` 打开门直接读房子里的人名，
>  而 `String()` 方法则决定你“看这栋房子时，它怎么介绍自己”。