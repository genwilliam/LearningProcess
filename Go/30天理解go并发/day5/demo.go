package main

import (
	"fmt"
	"sync"
)

func main() {
	var wg sync.WaitGroup
	wg.Add(5)
	go func() {
		defer wg.Done()
		fmt.Println(1)
	}()
	go func() {
		defer wg.Done()
		fmt.Println(2)
	}()
	go func() {
		defer wg.Done()
		fmt.Println(3)
	}()
	go func() {
		defer wg.Done()
		fmt.Println(4)
	}()
	go func() {
		defer wg.Done()
		fmt.Println(5)
	}()

	wg.Wait()
}