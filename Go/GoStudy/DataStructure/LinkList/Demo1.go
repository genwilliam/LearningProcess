package main

import "fmt"

// ListNode /* 链表节点结构体 */
type ListNode struct {
	Val  int       // 节点值
	Next *ListNode // 指向下一节点的指针
}

// NewListNode 构造函数，创建一个新的链表
func NewListNode(val int) *ListNode {
	return &ListNode{
		Val:  val,
		Next: nil,
	}
}
func main() {
	/*方式一：*/
	/* 初始化链表 1 -> 3 -> 2 -> 5 -> 4 */
	// 初始化各个节点
	n0 := NewListNode(1)
	n1 := NewListNode(3)
	n2 := NewListNode(2)
	n3 := NewListNode(5)
	n4 := NewListNode(4)
	// 构建节点之间的引用
	n0.Next = n1
	n1.Next = n2
	n2.Next = n3
	n3.Next = n4

	fmt.Println(n0.Val)

	/*方式二：*/
	//head := NewListNode(1)
	//head.Next = NewListNode(2)
	//head.Next.Next = NewListNode(3)
	//head.Next.Next.Next = NewListNode(4)
	//
	//fmt.Println(head)
	//fmt.Println(head.Next)
	//fmt.Println(head.Next.Next)
	//fmt.Println(head.Next.Next.Next)
	//
	//for head != nil {
	//	fmt.Printf("%d ", head.Val)
	//	head = head.Next
	//}
	//fmt.Println()

}
