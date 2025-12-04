package concurrence_test

import (
	"bufio"
	"fmt"
	"io"
	"io/fs"
	"os"
	"path/filepath"
	"strings"
	"sync"
	"testing"
)

const (
	READ_FILE_MAX_COUNT = 5
)

var (
	fileList   = make(chan string, 10)  // 文件路径队列
	lineBuffer = make(chan string, 100) // 内容行队列
	walkWG     sync.WaitGroup
	readWG     sync.WaitGroup
	printWG    sync.WaitGroup
)

func Test_dir(t *testing.T) {
	walkWG.Add(1)
	go walkAllFiles("./dir")

	// 并发读取文件
	readWG.Add(READ_FILE_MAX_COUNT)
	for i := 0; i < READ_FILE_MAX_COUNT; i++ {
		go readFileWorker()
	}

	// 行消费者，防止 lineBuffer 堆满阻塞
	printWG.Add(1)
	go printLinesWorker()

	// 控制 channel 的关闭顺序
	go func() {
		walkWG.Wait()
		close(fileList)

		readWG.Wait()
		close(lineBuffer)

		printWG.Wait()
	}()

	// 主协程读取扫描到的文件输出
	for file := range fileList {
		fmt.Println("扫描到文件:", file)
	}
}

// 扫描目录
func walkAllFiles(root string) {
	defer walkWG.Done()

	err := filepath.WalkDir(root, func(path string, d fs.DirEntry, err error) error {
		if err != nil {
			return err
		}

		// 只处理文件
		if !d.IsDir() {
			fileList <- path // 🔥 使用完整路径，避免路径错误
		}
		return nil
	})

	if err != nil {
		fmt.Println("walk error:", err)
	}
}

// 读取文件
func readFileWorker() {
	defer readWG.Done()

	for filePath := range fileList {
		fileOpen, err := os.Open(filePath)
		if err != nil {
			fmt.Println("open file error:", err)
			continue
		}

		reader := bufio.NewReader(fileOpen)
		for {
			line, err := reader.ReadString('\n')
			if err != nil {
				if err == io.EOF {
					line = strings.TrimSpace(line)
					if line != "" {
						lineBuffer <- line
					}
					break
				} else {
					fmt.Println("read line error:", err)
					break
				}
			}

			line = strings.TrimSpace(line)
			if line != "" {
				lineBuffer <- line
			}
		}

		fileOpen.Close()
	}

	fmt.Println("worker 退出")
}

func printLinesWorker() {
	defer printWG.Done()

	for line := range lineBuffer {
		fmt.Println("读取到行:", line)
	}
}
