package main

import "fmt"

/* 扩展数组长度 */
func extend(nums []int, enlarge int) []int {
	// 初始化一个扩展长度后的数组
	res := make([]int, len(nums)+enlarge)
	// 将原数组中的所有元素复制到新数组
	for i, num := range nums {
		res[i] = num
	}
	// 返回扩展后的新数组
	return res
}
func main() {
	nums := []int{1, 2, 3, 4, 5}
	fmt.Println(extend(nums, 3))

}
