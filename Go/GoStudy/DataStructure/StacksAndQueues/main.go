package main

import (
	. "GitHub/LianPeter/DataStructure/StacksAndQueues/Stack"
	"fmt"
)

// 实现Stack的main
func main() {
	stack := NewStack()

	stack.Push(1)
	stack.Push(3)
	stack.Push(2)
	stack.Push(5)
	stack.Push(4)

	peek := stack.Peek()
	pop := stack.Pop()
	size := stack.Size()
	isEmpty := stack.IsEmpty()

	fmt.Printf("Peek: %d\n", peek)
	fmt.Printf("Pop: %d\n", pop)
	fmt.Printf("Size: %d\n", size)
	fmt.Printf("Is Empty: %v\n", isEmpty)

}

// 实现Queues的main
/*func main() {

	// 初始化队列
	queue := list.New()

	// 元素入队
	queue.PushBack(1)
	queue.PushBack(3)
	queue.PushBack(2)
	queue.PushBack(5)
	queue.PushBack(4)

	// 访问队首元素
	peek := queue.Front().Value

	// 元素出队
	pop := queue.Front()
	queue.Remove(pop)

	// 获取队列的长度
	size := queue.Len()

	// 判断队列是否为空
	isEmpty := queue.Len() == 0

	fmt.Printf("Peek: %v\n", peek)
	fmt.Printf("Pop: %v\n", pop.Value)
	fmt.Printf("Size: %d\n", size)
	fmt.Printf("Is Empty: %v\n", isEmpty)
}*/
