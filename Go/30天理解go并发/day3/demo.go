package main

func main() {
	// buffered
	ch1 := make(chan int, 2)

	// unbuffered
	ch2 := make(chan int)

	// 有缓冲可以写入n个值(2)
	ch1 <- 1
	ch1 <- 2

	// 无缓冲不能写入,直到有接收者
	// 
	// main协程和其他协程互不干扰
	// main 协程结束,其他协程也结束
	go func() {
		ch2 <- 3
		ch2 <- 4
	}()

	// fmt.Println(<-ch2)


}