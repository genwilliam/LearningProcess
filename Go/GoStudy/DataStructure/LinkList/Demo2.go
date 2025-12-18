package main

/* 在链表的节点 n0 之后插入节点 P */
func insertNode(n0 *ListNode, P *ListNode) {
	n1 := n0.Next
	n0.Next = P
	P.Next = n1
}
