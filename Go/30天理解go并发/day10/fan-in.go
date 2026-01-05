package main

import (
	"fmt"
	"sync"
)

// fan-in mod
func main() {
	ch := make(chan int)
	var wg sync.WaitGroup

	// 启动多个生产者
	for i := 1; i <= 3; i++ {
		// 每个 Worker 开始前 Add
		wg.Add(1)
		go func(workerID int) {
			defer wg.Done()
			for c := 1; c <= 5; c++ {
				ch <- c // 多个 worker 往同一个 ch 写
			}
		}(i)
	}

	// 开启一个守护协程负责关闭通道
	// 另开协程,因为 wg.Wait() 会阻塞，如果不异步，代码就运行不到后面的读取环节了
	go func() {
		wg.Wait()
		close(ch)
	}()

	// 消费者留在主协程
	// range 会持续读取，直到 ch 被上面的守护协程关闭
	for i := range ch {
		fmt.Println("收到结果:", i)
	}

	// 当 range 退出时，说明所有数据都处理完了，程序正常结束
	fmt.Println("所有任务处理完毕，Fan-in 结束")
}
