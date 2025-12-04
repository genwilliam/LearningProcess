package panic

import "fmt"

// Defer_panic 发生Panic
//
// 1. runtime error
//
// 2.初始化阶段有问题就Panic
//
// Panic会执行:
//
// 1. 发生Panic之后,会执行已经注册的defer(后注册的先执行),
// 没有注册的defer不执行
//
// 2. 打印错误调用堆栈
//
// 3. 调用os.Exit(2)结束go进程
func Defer_panic() {
	defer func() {
		if r := recover(); r != nil {
			fmt.Println(r)
		}
	}()
	defer fmt.Println(1)
	var arr []int
	n := 0
	//defer fmt.Println(1 / n)
	defer func() {
		_ = arr[n]
		_ = 1 / n

		defer fmt.Println(2)
	}()
	defer fmt.Println(3)
}
