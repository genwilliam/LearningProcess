package main

import "fmt"

// 使用defer关键字注册一个defer
//
// 当函数返回之前调用defer
// 如果defer后面有参数或值,
// 在注册defer时就要给参数值
//
// 如果defer后面跟函数,
// 那只会声明这个函数,而不会给函数里面的参数赋值..
func defer_exe() {
	fmt.Println("A")
	fmt.Println("B")
	defer fmt.Println("1")
	fmt.Println("C")
	defer fmt.Println("2")

	fmt.Println("D")
	defer fmt.Println("3")
}
