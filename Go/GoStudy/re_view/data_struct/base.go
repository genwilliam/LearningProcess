package data_struct

import "fmt"

// TenBase 计算excel表格有多少列
//
// 比如数字  3003003
//
// 十进制可表示为3 * 10^7 + 3 * 10^3 + 3 * 10^0
//
// 八进制可表示为3 * 8^7 + 3 * 8^3 + 3 * 8^0
//
// excel 的列是用英文字母表示最对是到 ： XFD
func TenBase() {
	fmt.Printf("A = %d Z = %d\n", 'A', 'Z')
	var base int = 'Z' - 'A' + 1 //几进制（26）
	fmt.Println(base, "进制")
	// 总和
	var total int
	total += 'D' - 'A' + 1
	total += base * ('F' - 'A' + 1)

	total += base * base * ('X' - 'A' + 1)
	fmt.Println("total", total) // 16384
}
