package main

import (
	"fmt"

	"time"
)

func main() {
	ch1 := make(chan int)
	ch2 := make(chan int)


	go func() {
		ch1 <- 1
	}()

	go func() {

		ch2 <- 2
	}() 

	time.Sleep(1 * time.Second)
	select {
	case num := <-ch1:
		fmt.Println("num:", num)
	
	case num := <- ch2:
		fmt.Println("num:", num)
	}

}