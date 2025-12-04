package main

import (
	"fmt"
)

func fallThrough() {
	a := func() int {
		return 4
	}

	// switch没有fallthrough,
	// 就不会执行满足条件之后的语句
	// fallthrough强制执行下一个 case 的语句块
	// 即使下一个 case 的条件不匹配
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
