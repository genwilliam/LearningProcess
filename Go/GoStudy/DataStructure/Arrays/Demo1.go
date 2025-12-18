package main

import (
	"fmt"
	"math/rand"
)

/* 随机访问元素 */
func randomAccess(nums []int) (randomNum int) {
	// 在区间 [0, nums.length) 中随机抽取一个数字
	randomIndex := rand.Intn(len(nums))
	// 获取并返回随机元素
	randomNum = nums[randomIndex]
	return randomNum
}
func main() {
	num := randomAccess([]int{1, 2, 3, 4, 5, 6, 7, 8})
	fmt.Println(num)
}
