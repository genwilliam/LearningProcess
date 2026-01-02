package main

import (
	"fmt"
	"sync"
)

func main() {
	// stage1: generate number 1~10
	// stage2: number + 1
	// stage3: sum

	ch1 := make(chan int, 2)
	ch2 := make(chan int, 2)
	result := make(chan int, 1)

	var wg sync.WaitGroup
	wg.Add(3)

	// stage1
	go func() {
		defer wg.Done()
		defer close(ch1)
		for i := 1; i <= 10; i++ {
			ch1 <- i
		}

	}()
	// stage2
	go func() {
		defer wg.Done()
		defer close(ch2)
		for n := range ch1 {
			ch2 <- (n + 1)
		}

	}()

	// stage3
	go func() {
		defer wg.Done()
		defer close(result)
		sum := 0
		for n := range ch2 {
			sum += n
		}
		result <- sum
	}()

	wg.Wait()

	fmt.Println("num:", <-result)
}
