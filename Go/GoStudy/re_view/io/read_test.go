package io_test

import (
	"fmt"
	"os"
	"testing"
)

func Test_read(t *testing.T) {
	read, err := os.Open("data/write.txt")
	if err != nil {
		fmt.Println("read file failed:", err)
	}
	defer read.Close()

	bs := make([]byte, 10)
	read.Read(bs)

	fmt.Println(bs)
	fmt.Println(string(bs))

}
