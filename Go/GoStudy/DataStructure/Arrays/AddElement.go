package main

import "fmt"

func main() {
	// 方法一：循环
	arr := []int{1, 2, 3, 4, 5} // 定义一个数组（实际上这里用的是切片）

	fmt.Print("请输入一个索引：")
	var index int
	_, err := fmt.Scanf("%d", &index)
	if err != nil {
		fmt.Println("输入有误")
		return
	}
	fmt.Print("请输入一个元素：")
	var num int
	_, _ = fmt.Scanf("%d", &num)

	// 确保索引不会越界
	if index < 0 || index > len(arr) {
		fmt.Println("索引超出范围")
		return
	}

	// 插入元素
	arr = append(arr[:index], append([]int{num}, arr[index:]...)...)
	// 使用 ... 操作符将 arr[index:] 解包为单独的元素。

	/*
			arr[:index]:
		这部分表示从原切片 arr 的起始位置到索引 index-1 的子切片。
			[]int{num}:
		这是一个包含单个元素 num 的新切片。
		例如，如果 num 是 9，那么这部分就是 [9]。
			arr[index:]:
		这部分表示从索引 index 到原切片 arr 结束位置的子切片。
			append([]int{num}, arr[index:]...):
		这部分将包含单个元素 num 的切片与 arr[index:] 合并。
		使用 ... 操作符将 arr[index:] 解包为单独的元素。
	*/

	// 打印结果
	fmt.Println("插入后的数组:", arr)

	// 方法二：函数

	nums := []int{10, 20, 30, 40, 50}
	
	num1 := 2
	index1 := 2
	insert(nums, num1, index1)
	fmt.Println(nums)

}
func insert(nums []int, num int, index int) { // 最后一位数字被覆盖
	// 把索引 index 以及之后的所有元素向后移动一位
	for i := len(nums) - 1; i > index; i-- {
		nums[i] = nums[i-1]
	}
	// 将 num 赋给 index 处的元素
	nums[index] = num
}
