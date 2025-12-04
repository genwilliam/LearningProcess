package concurrence_test

import (
	"fmt"
	"runtime"
	"testing"
	"time"
)

func Test_show_cpu(t *testing.T) {
	cpu := runtime.NumCPU()

	// 本进程最多用多少核
	//runtime.GOMAXPROCS(2)

	fmt.Println("cpu个数:", cpu)
	fmt.Println("协程数", runtime.NumGoroutine())

	go add(1, 2)
	go child()

	fmt.Println("协程数", runtime.NumGoroutine())
	time.Sleep(4 * time.Second)
}

func add(a, b int) {
	fmt.Println(a + b)
}

func child() {
	fmt.Println("child begin")
	go grandson()
	time.Sleep(2 * time.Second)
	fmt.Println("child finish")
}

func grandson() {
	fmt.Println("grandson begin")
	fmt.Println("grandson,协程数", runtime.NumGoroutine())
	time.Sleep(3 * time.Second)
	fmt.Println("grandson finish")
}
