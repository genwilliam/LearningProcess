package main

// access 访问链表中索引为 index 的节点
func access(head *ListNode, index int) *ListNode {
	for i := 0; i < index; i++ {
		if head == nil {
			return nil
		}
		head = head.Next
	}
	return head
}

// findNode 在链表中查找值为 target 的首个节点
func findNode(head *ListNode, target int) int {
	index := 0
	for head != nil {
		if head.Val == target {
			return index
		}
		head = head.Next
		index++
	}
	return -1
}

func DelElement(head *ListNode, nums []int) {
	/* 清空列表 */
	nums = nil

	/* 在尾部添加元素 */
	nums = append(nums, 1)
	nums = append(nums, 3)
	nums = append(nums, 2)
	nums = append(nums, 5)
	nums = append(nums, 4)

	/* 在中间插入元素 */
	nums = append(nums[:3], append([]int{6}, nums[3:]...)...) // 在索引 3 处插入数字 6

	/* 删除元素 */
	nums = append(nums[:3], nums[4:]...) // 删除索引 3 处的元素
}

// Select 通过索引遍历列表
func Select(head *ListNode, nums []int) {
	count := 0
	for i := 0; i < len(nums); i++ {
		count += nums[i]
	}
	/* 直接遍历列表元素 */

}
