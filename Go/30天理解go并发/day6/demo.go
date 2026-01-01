package main

import (
	"fmt"
	"sync"
)

func main() {
	n := 10
	ch := make(chan int, 2)

	var wg sync.WaitGroup
	wg.Add(n)

	go func() {
		for {
			// ok: true --> 能读取数据
			// 	   false: --> channel close
			// 	   如果channel没有close,也没有读取数据,则会阻塞
			num, ok := <-ch
			if !ok { // channel closed
				return
			}
			fmt.Println(num)
		}
	}()

	for i := 0; i < n; i++ {
		go func(i int) {
			defer wg.Done()
			ch <- i
		}(i)
	}

	wg.Wait()
	close(ch)

}
