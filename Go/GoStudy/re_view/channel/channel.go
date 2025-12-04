package chann

import "fmt"

func Channel() {
	c := make(chan int, 8)
	for i := 0; i < 8; i++ {
		c <- i
	}
	close(c)
	fmt.Println(c)
	for v := range c {
		fmt.Println(v)
	}
}

// 只允许写入
func send(ch chan<- int) {
	ch <- 1
}

// 取出channel
func recv(ch <-chan int) {
	v := ch
	fmt.Println(v)
}
