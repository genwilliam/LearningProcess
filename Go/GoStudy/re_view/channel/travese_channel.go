package chann

import (
	"fmt"
	"time"
)

var chann = make(chan int, 2)

func CloseChannel() {
	chann <- 1
	go func() {
		time.Sleep(2 * time.Second)
		chann <- 2
	}()
	//channel关闭后读操作会立即返回，即使channel为空
	//channel关闭后就不允许再写入元素了,读可以
	//close(chann)

	i, ok := <-chann // ok: ture -- 管道里的,可以直接用 。 false -- 读取的值不能使用
	fmt.Println(i, ok)
	i, ok = <-chann
	fmt.Println(i, ok)

	// 遍历channel
	// 一边遍历
	// 一边取出来
	// 最后为空的channel
	for i := range chann {
		fmt.Println(i)
	}
}
