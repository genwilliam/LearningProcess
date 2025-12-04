package data_struct

import "fmt"

// BasicData 基本的数据类型
func BasicData() {
	var name int // 声明
	fmt.Println(name)
	var a int = 8
	fmt.Println(a)
	var b = a // 自动推断
	_ = b     // 下划线 -> 占位符

	var (
		c uint16
		d int8
		f float32
		// ...
	)
	c = 05    // 前面有个0表示八进制
	d = 0o5   // 前缀0o表示八进制，后面的数字只能到7
	c = 0xab3 // 十六进制
	a = 5_0_123_7
	a = 13_000_000 // 13M

	f = 3.14
	f = 4.7612937490179051790571
	g := 34. // 这时候默认是float64
	_, _, _, _ = c, d, f, g

	// boolean
	var n bool = true // bool的零值是false
	fmt.Printf("%d , %f, %t\n", a, f, n)

	// %g 默认输出小数点后六位
	// %e 用科学计数法输出
	fmt.Printf("f = %g, f = %e\n", f, f)
	fmt.Printf("f = %.2f\n", f) // .2f 展示两位小数

	// [1]表示后面参数的第一个值
	fmt.Printf("f = %[1]f, g = %[2]f, g = %[2]g, f = %[1]e\n", f, g)
}

// Const 常量的演示
// 常量一旦定义不可改变
//
// 一般用大写的方式定义
//
// 如果常量定义但是没用是不报错的
func Const() {
	// 常量
	const PI float32 = 3.14
	_ = PI

	// 枚举
	// 本质还是常量
	const (
		ONE   = 1
		TWO   = 2
		THREE = 3
		FOUR  = 4
	)

	const (
		aa = 2
		bb
		cc
		dd
		ee
	)

	const (
		a = iota // 0
		b        // 往下依次加1
		c
		_ // 如果不想用 3 ，可以用下划线代替
		d
		e = 89
		f = iota // 可重新进行iota
	)

	const (
		//NOT_USE = 1 << (10 * iota)
		//KB      = 1 << (10 * iota)
		//MB      = 1 << (10 * iota)
		//GB      = 1 << (10 * iota)

		// 或者

		NOT_USE = 1 << (10 * iota)
		KB
		MB
		GB
	)

	// 使用了iota
	// 如果只有第一行有 = 等号
	// 接下来的每一行的 等号 和 等号后面的表达式 都是一样的（可以省略）
	// iota：第一行是0，后面每行都递增 1
	const (
		ss, mm = iota + 1, iota + 2 // iota = 0
		gg, tt                      // iota = 1
		ff, nn                      // iota = 2
	)
}
