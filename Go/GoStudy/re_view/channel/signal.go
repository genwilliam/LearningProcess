package chann

import (
	"fmt"
	"time"
)

// Broadcast 广播
func Broadcast() {
	ch := make(chan struct{})

	const P = 3
	for i := 0; i < P; i++ {
		go func() {
			<-ch
			fmt.Printf("%d 出发了\n", i)
		}()
	}

	time.Sleep(2 * time.Second)
	fmt.Println("大伙可以出发了")
	// 当close之后才能进行channel的读操作
	close(ch)

	time.Sleep(time.Second)
}

// CountDownLatch 等其他人都完成后，再执行
func CountDownLatch() {
	const P = 3
	ch := make(chan struct{}, P)
	for i := 0; i < P; i++ {
		go func() {
			time.Sleep(time.Duration(i) * time.Second)
			fmt.Printf("%d 完成工作了\n", i)
			ch <- struct{}{}
		}()
	}

	// 同步点。channel可以完成WaitGroup的功能
	for i := 0; i < P; i++ {
		<-ch
	}

	fmt.Println("别人执行完毕，开始执行")
}
