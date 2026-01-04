package main

import (
	"fmt"
	"sync"
)

// Fan-out mod
func main() {
	var wg sync.WaitGroup
	wg.Add(3)
	ch := make(chan int, 2)

	go func() {
		defer close(ch)
		for i := 1; i <= 20; i++ {
			ch <- i
		}
	}()

	for i := 0; i < 3; i++ {
		go func(id int) {
			defer wg.Done()

			// range 直接作用于 channel
			for task := range ch {
				fmt.Printf("Worker %d 处理了任务: %d\n", id, task)
			}
		}(i)
	}

	wg.Wait()
}
