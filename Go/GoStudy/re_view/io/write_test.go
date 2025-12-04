package io_test

import (
	"fmt"
	"os"
	"testing"
)

func Test_write(t *testing.T) {
	file, err := os.OpenFile("./data/write.txt", os.O_CREATE|os.O_TRUNC|os.O_RDWR, 0o666)

	if err != nil {
		fmt.Println("open file failed:", err)
	}
	defer file.Close()
	file.WriteString("hello\n" + "world\n" + "hi")

}
