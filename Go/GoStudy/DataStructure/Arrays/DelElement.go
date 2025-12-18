package main

import "fmt"

func main() {
	arr := []int{1, 2, 3, 4, 5}
	deleteElement(arr, 2)
	arr = arr[:len(arr)-1]
	fmt.Println(arr)
}

func deleteElement(arr []int, index int) { // 删除数组中指定索引的元素
	for i := index; i < len(arr)-1; i++ {
		arr[i] = arr[i+1]
	}
}
