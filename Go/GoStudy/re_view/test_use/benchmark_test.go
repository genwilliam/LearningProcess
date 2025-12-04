package test_use

import "testing"

func Add1(a, b int) int {
	return a + b
}

// 基准测试:
// 测试代码运行效率（如函数执行次数/时间）
func BenchmarkAdd(b *testing.B) {
	for i := 0; i < b.N; i++ {
		Add1(1, 2)
	}
}
