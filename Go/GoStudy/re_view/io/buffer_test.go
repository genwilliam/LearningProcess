package io_test

import (
	"bufio"
	"fmt"
	"io"
	"os"
	"strings"
	"testing"
)

func Test_buffer(t *testing.T) {
	if file, err := os.Open("data/write.txt"); err != nil {
		fmt.Println("open file failed:", err)
	} else {
		defer file.Close()

		bufferRead := bufio.NewReader(file)
		// 根据换行符进行读取
		for {
			line, err := bufferRead.ReadString('\n')

			if len(line) > 0 {
				// 把\n截取
				line = strings.TrimRight(line, "\n")
				fmt.Println(line)
			}
			if err == io.EOF { // end of file
				break
			}
		}

	}
}

func Test_write_buffer(t *testing.T) {
	file, err := os.OpenFile("data/write.txt", os.O_CREATE|os.O_TRUNC|os.O_RDWR, 0o666)
	if err != nil {
		fmt.Println("open file failed:", err)
	}
	defer file.Close()
	// 缓冲
	// 数据暂存在内存中
	// 缓冲区未满时不会自动写入
	writer := bufio.NewWriter(file)
	writer.WriteString("hello\n")
	writer.WriteString("world")

	// 强制写入
	writer.Flush()
}
