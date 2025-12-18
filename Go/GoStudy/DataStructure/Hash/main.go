package main

import (
	. "GitHub/LianPeter/DataStructure/Hash/map"
	"fmt"
)

func main() {
	hmap := Start()
	fmt.Println(hmap)
	/* 查询操作 */
	// 向哈希表中输入键 key ，得到值 value
	name := hmap[15937]
	fmt.Println("找到键为15937的值为：" + name)

	/* 删除操作 */
	// 在哈希表中删除键值对 (key, value)
	delete(hmap, 10583)
	fmt.Println(hmap)

	// 遍历键值对
	for key, value := range hmap {
		fmt.Println(key, "-->", value)
	}

	// 遍历键
	for key := range hmap {
		fmt.Println(key)
	}
	// 遍历值
	for _, value := range hmap {
		fmt.Println(value)
	}
}
