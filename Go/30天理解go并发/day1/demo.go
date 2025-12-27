package main

import (
	"fmt"
	"sync"
)

// func main() {
// 	go func() {
// 		for i := 1; i <= 10; i++ {
// 			fmt.Println(i)
// 		}
// 	}()
// 	time.Sleep(1 * time.Second)
// }

func main() {
	var wg sync.WaitGroup
	wg.Add(1)  // WaitGroup添加一个goroutine
	go func() {
		defer wg.Done()  // wg 减1,如果wg不为0,则一直停留在wait()
		for i:= 1; i <= 10;i ++ {
			fmt.Println(i)
		}
	}()

	wg.Wait()
}