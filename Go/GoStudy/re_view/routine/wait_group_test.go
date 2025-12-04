package concurrence_test

import (
	"fmt"
	"runtime"
	"sync"
	"sync/atomic"
	"testing"
	"time"
)

var wt = sync.WaitGroup{}

func g() {
	defer wt.Done()
	fmt.Println("grandson begin")
	fmt.Printf("routine num %d\n", runtime.NumGoroutine())
	time.Sleep(3 * time.Second)
	fmt.Printf("routine num %d\n", runtime.NumGoroutine())
	fmt.Println("grandson finish")
}

func c() {
	defer wt.Done()
	fmt.Println("child begin")
	go g()
	time.Sleep(100 * time.Millisecond)
	fmt.Println("child finish") //子协程退出后，孙协挰还在运行。所有协程都是平等的、独立的。一个协程的生命周期不受制于另一个协程（main协程除外）
}

func Test_SubRoutine(t *testing.T) { //main协程调用此函数
	wt.Add(2)
	go c()
	// time.Sleep(2 * time.Second)
	wt.Wait()
}

func WaitGroup() {
	const N = 10
	wg := sync.WaitGroup{}
	wg.Add(N) //加N
	for i := 0; i < N; i++ {
		go func(a, b int) { //开N个子协程
			defer wg.Done() //减1
			time.Sleep(10 * time.Millisecond)
			_ = a + b
			fmt.Printf("%d 结束\n", i)
		}(i, i+1)
	}
	fmt.Printf("当前协程数：%d\n", runtime.NumGoroutine()) //N+1
	wg.Wait()                                        //等待减为0
	fmt.Printf("当前协程数：%d\n", runtime.NumGoroutine()) //1
}

var (
	sum int64
)

const P = 10

func Sum() {
	sum = 0
	var wg sync.WaitGroup
	for i := 0; i < P; i++ {
		wg.Go(func() {
			atomic.AddInt64(&sum, 1)
		})
	}
	wg.Wait()
	fmt.Println(sum)
}
