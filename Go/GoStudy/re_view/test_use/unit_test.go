package test_use

import "testing"

// 基准测试:
//
// 用于一个函数或模块的输出是否正确
// 不关注性能
// 失败终止
//
// 使用testing.T
// 文件名必须是以_test.go作为后缀
//
// 函数名需要以Test_开头
func Test_main(t *testing.T) {
	got := Add(2, 3)
	want := 5
	if got != want {
		t.Errorf("Add(2,3) = %d; want %d", got, want)
	}
}
func Add(a, b int) int {
	return a + b
}
