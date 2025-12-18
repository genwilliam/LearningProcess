package Stack

import "container/list"

// Stack 表示使用切片的简单堆栈。
type Stack struct {
	items []int
}

// NewStack 创建并初始化一个新堆栈。
func NewStack() *Stack {
	return &Stack{}
}

// Push 将一个元素添加到栈顶。
func (s *Stack) Push(item int) {
	s.items = append(s.items, item)
}

// Pop 从堆栈中删除并返回顶部元素。
func (s *Stack) Pop() int {
	if len(s.items) == 0 {
		return 0
	}
	top := s.items[len(s.items)-1]
	s.items = s.items[:len(s.items)-1]
	return top
}

// Peek 返回顶部元素而不删除它。
func (s *Stack) Peek() int {
	if len(s.items) == 0 {
		return 0
	}
	return s.items[len(s.items)-1]
}

// Size 返回堆栈中元素的数量。
func (s *Stack) Size() int {
	return len(s.items)
}

// IsEmpty 检查堆栈是否为空。
func (s *Stack) IsEmpty() bool {
	return len(s.items) == 0
}

// 基于链表实现栈的示例代码
type linkedListStack struct {
	// 使用内置包 list 来实现栈
	data *list.List
}

/* 初始化栈 */
func newLinkedListStack() *linkedListStack {
	return &linkedListStack{
		data: list.New(),
	}
}

/* 入栈 */
func (s *linkedListStack) push(value int) {
	s.data.PushBack(value)
}

/* 出栈 */
func (s *linkedListStack) pop() any {
	if s.isEmpty() {
		return nil
	}
	e := s.data.Back()
	s.data.Remove(e)
	return e.Value
}

/* 访问栈顶元素 */
func (s *linkedListStack) peek() any {
	if s.isEmpty() {
		return nil
	}
	e := s.data.Back()
	return e.Value
}

/* 获取栈的长度 */
func (s *linkedListStack) size() int {
	return s.data.Len()
}

/* 判断栈是否为空 */
func (s *linkedListStack) isEmpty() bool {
	return s.data.Len() == 0
}

/* 获取 List 用于打印 */
func (s *linkedListStack) toList() *list.List {
	return s.data
}

// 动态数组实现栈
/* 基于数组实现的栈 */
type arrayStack struct {
	data []int // 数据
}

/* 初始化栈 */
func newArrayStack() *arrayStack {
	return &arrayStack{
		// 设置栈的长度为 0，容量为 16
		data: make([]int, 0, 16),
	}
}

/* 栈的长度 */
func (s *arrayStack) size() int {
	return len(s.data)
}

/* 栈是否为空 */
func (s *arrayStack) isEmpty() bool {
	return s.size() == 0
}

/* 入栈 */
func (s *arrayStack) push(v int) {
	// 切片会自动扩容
	s.data = append(s.data, v)
}

/* 出栈 */
func (s *arrayStack) pop() any {
	val := s.peek()
	s.data = s.data[:len(s.data)-1]
	return val
}

/* 获取栈顶元素 */
func (s *arrayStack) peek() any {
	if s.isEmpty() {
		return nil
	}
	val := s.data[len(s.data)-1]
	return val
}

/* 获取 Slice 用于打印 */
func (s *arrayStack) toSlice() []int {
	return s.data
}
