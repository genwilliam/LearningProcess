package concurrence

import (
	"bufio"
	"fmt"
	"io"
	"io/fs"
	"os"
	"path/filepath"
	"strings"
	"sync"
)

const (
	READ_FILE_MAX_COUNT = 5
)

type FileLine struct {
	File string
	Line string
}

type ReadCtx struct {
	root       string
	fileList   chan string
	lineBuffer chan FileLine

	walkWG  sync.WaitGroup
	readWG  sync.WaitGroup
	printWG sync.WaitGroup

	allFiles []string
}

func newCtx(root string) *ReadCtx {
	return &ReadCtx{
		root:       root,
		fileList:   make(chan string, 20),
		lineBuffer: make(chan FileLine, 200),
		allFiles:   make([]string, 0),
	}
}

// ---------------------
// main 调用入口
// ---------------------
func ReadFile(root string) {
	ctx := newCtx(root)

	// 1. 扫描文件
	ctx.walkWG.Add(1)
	go walkAllFiles(ctx)

	// 2. 启动 Worker（读文件）
	ctx.readWG.Add(READ_FILE_MAX_COUNT)
	for i := 0; i < READ_FILE_MAX_COUNT; i++ {
		go readFileWorker(ctx)
	}

	// 3. 启动打印 Worker
	ctx.printWG.Add(1)
	go printLinesWorker(ctx)

	// ------------------------
	// 🚨 关键：等待所有工作完成
	// ------------------------
	go func() {
		ctx.walkWG.Wait()
		close(ctx.fileList)

		ctx.readWG.Wait()
		close(ctx.lineBuffer)

		ctx.printWG.Wait() // 打印完所有行
	}()

	// 主 goroutine 先打印文件列表
	ctx.walkWG.Wait()
	fmt.Println("------ 扫描到全部文件 ------")
	for _, f := range ctx.allFiles {
		fmt.Println(f)
	}

	// 必须等待 printWG 完成，否则 main 会提前退出！
	ctx.printWG.Wait()

	fmt.Println("------ 输出完成，任务结束 ------")
}

// -------------------------
// 扫描目录
// -------------------------
func walkAllFiles(ctx *ReadCtx) {
	defer ctx.walkWG.Done()

	filepath.WalkDir(ctx.root, func(path string, d fs.DirEntry, err error) error {
		if err != nil {
			fmt.Println("walk error:", err)
			return nil
		}

		if !d.IsDir() {
			ctx.allFiles = append(ctx.allFiles, path)
			ctx.fileList <- path
		}

		return nil
	})
}

// -------------------------
// Worker 读取文件内容
// -------------------------
func readFileWorker(ctx *ReadCtx) {
	defer ctx.readWG.Done()

	for filePath := range ctx.fileList {

		f, err := os.Open(filePath)
		if err != nil {
			fmt.Println("open file error:", err)
			continue
		}

		reader := bufio.NewReader(f)
		for {
			line, err := reader.ReadString('\n')
			if err != nil {
				if err == io.EOF {
					line = strings.TrimSpace(line)
					if line != "" {
						ctx.lineBuffer <- FileLine{File: filePath, Line: line}
					}
					break
				}
				fmt.Println("read line error:", err)
				break
			}

			line = strings.TrimSpace(line)
			if line != "" {
				ctx.lineBuffer <- FileLine{File: filePath, Line: line}
			}
		}
		f.Close()
	}

	fmt.Println("worker 退出")
}

// -------------------------
// 打印内容 Worker
// -------------------------
func printLinesWorker(ctx *ReadCtx) {
	defer ctx.printWG.Done()

	for fl := range ctx.lineBuffer {
		fmt.Printf("[文件: %s] %s\n", fl.File, fl.Line)
	}
}
