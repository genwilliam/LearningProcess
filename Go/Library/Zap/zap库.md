# zap的特性

- 高性能：zap 对日志输出进行了多项优化以提高它的性能
    
- 日志分级：有 Debug，Info，Warn，Error，DPanic，Panic，Fatal 等
    
- 日志记录结构化：日志内容记录是结构化的，比如 json 格式输出
    
- 自定义格式：用户可以自定义输出的日志格式
    
- 自定义公共字段：用户可以自定义公共字段，大家输出的日志内容就共同拥有了这些字段
    
- 调试：可以打印文件名、函数名、行号、日志时间等，便于调试程序
    
- 自定义调用栈级别：可以根据日志级别输出它的调用栈信息
    
- Namespace：日志命名空间。定义命名空间后，所有日志内容就在这个命名空间下。命名空间相当于一个文件夹
    
- 支持 hook 操作
# quickstart
zap 安装：
```bash
 go get -u go.uber.org/zap
```

zap 提供了 2 种日志记录器：`SugaredLogger` 和 `Logger`。

如果你追求 **高性能、结构化日志、类型安全** —— 用 `zap.Logger`；  
如果你想要 **更方便地记录日志、写得快、读得爽** —— 用 `zap.SugaredLogger`。
`SugaredLogger` 是对 `Logger` 的封装，提供了更友好的日志记录方法

example:
```go
func SugaredLogger() {  
    logger, _ := zap.NewProduction()  
    defer logger.Sync() // zap底层有缓冲。在任何情况下执行 defer logger.Sync() 是一个很好的习惯  
    sugar := logger.Sugar()  
    url := "example.com"  
    sugar.Infow("failed to fetch URL",  
       // 字段是松散类型，不是强类型  
       "url", url,  
       "attempt", 3,  
       "backoff", time.Second,  
    )  
    sugar.Infof("Failed to fetch URL: %s", url)  
}
```

当你想用sugar时，直接使用logger进行调用即可

当性能和类型安全很重要时，请使用 Logger。它比 SugaredLogger 更快，分配的资源更少，但它只支持结构化日志和强类型字段
```go
func LoggerDemo() {  
    logger, _ := zap.NewProduction()  
    defer logger.Sync()  
    url := "example.com"  
    logger.Info("failed to fetch URL",  
       // 字段是强类型，不是松散类型  
       zap.String("url", url),  
       zap.Int("attempt", 3),  
       zap.Duration("backoff", time.Second),  
    )  
}
```
# NewExample/NewDevelopment/NewProduction

zap 有三种快速创建 logger 的方法: `zap.NewProduction()`，`zap.NewDevelopment()`，`zap.NewExample()`。

见名思义，Example 一般用在测试代码中，Development 用在开发环境中，Production 用在生成环境中。这三种方法都预先设置好了配置信息。

## 对比
下面是一个测试代码，对比这三种方式的输出
```go
package zap_test  
  
import (  
    "go.uber.org/zap"  
    "testing")  
  
func Test_main(t *testing.T) {  
    logProduction()  
    logDevelopment()  
    logExample()  
}  
  
func logProduction() {  
    logger, _ := zap.NewProduction()  
    defer logger.Sync()  
    logger.Info("hello")  
    sugar := logger.Sugar()  
    defer sugar.Sync()  
    sugar.Info("hello, sugar")  
}  
  
func logDevelopment() {  
    logger, _ := zap.NewDevelopment()  
    defer logger.Sync()  
    logger.Info("hello, development")  
    sugar := logger.Sugar()  
    defer sugar.Sync()  
    sugar.Info("hello, sugar")  
}  
  
func logExample() {  
    logger := zap.NewExample()  
    defer logger.Sync()  
    logger.Info("hello, example")  
    sugar := logger.Sugar()  
    defer sugar.Sync()  
    sugar.Info("hello, sugar")  
}
```

输出：
```
{"level":"info","ts":1745305399.784637,"caller":"zap_test/sugardlogger_test.go:17","msg":"hello"}
{"level":"info","ts":1745305399.784637,"caller":"zap_test/sugardlogger_test.go:20","msg":"hello, sugar"}
2025-04-22T15:03:19.784+0800    INFO    zap_test/sugardlogger_test.go:26        hello, development
2025-04-22T15:03:19.802+0800    INFO    zap_test/sugardlogger_test.go:29        hello, sugar
{"level":"info","msg":"hello, example"}
{"level":"info","msg":"hello, sugar"}
```
可以看到，new的三种方式，输出格式每一种都不同，但是如果使用sugar，他们的输出格式都是一样的（我这里指的是同一种new的方式

### 当然你可能会想到，如果同一个sugar中，我使用info，infow，infof他们的输出会不会不一样呢

#### 1. 使用 `Info()`

```go
sugar.Info("hello")
```

输出（结构化 JSON）：

```json
{"level":"info","ts":...,"caller":"...","msg":"hello"}
```

#### 2. 使用 `Infof()`

```go
sugar.Infof("hello %s", "world")
```

输出：

```json
{"level":"info","ts":...,"caller":"...","msg":"hello world"}
```

#### 3. 使用 `Infow()`

```go
sugar.Infow("hello", "user", "william", "id", 123)
```

输出：

```json
{
  "level": "info",
  "ts": ...,
  "caller": "...",
  "msg": "hello",
  "user": "william",
  "id": 123
}
```

| 方法        | 是否结构化？ | `msg` 字段表现      | 附加字段如何输出？  |
| --------- | ------ | --------------- | ---------- |
| `Info()`  | 否      | 原样作为字符串输出       | 无法添加键值对    |
| `Infof()` | 否      | 格式化后字符串作为 `msg` | 无法添加键值对    |
| `Infow()` | 是      | 第一个参数是 `msg`    | 之后成对是结构化字段 |

所以：

- 想用格式化：用 `Infof()`（像 `fmt.Printf`）
    
- 想记录结构化字段（键值对）：用 `Infow()`
    
- 想简单输出消息：用 `Info()`
    

---

#### 提示：

即使 `Infow()` 产生的是结构化字段，它的输出格式也不会“变形”，因为 **Logger 的 Encoder 决定了一切格式**，而不是 `SugaredLogger` 的使用方式。

> 所以：**想改格式 → 改 `zap.Config` 的 `Encoding` 与 `EncoderConfig`；不是改 `sugar` 的方法名。**

## NewExample()使用

NewExample 构建一个 logger，专门为在 zap 的测试示例使用。它将 DebugLevel 及以上日志用 JSON 格式标准输出，但它省略了时间戳和调用函数，以保持示例输出的简短和确定性。
你可以理解为：它专门是为了文档、单元测试、教学示例设计的

为什么说 `zap.NewExample()` 是 zap 为我们提供快速创建 logger 的方法呢？

因为在这个方法里，zap 已经定义好了日志配置项部分默认值。来看它的代码：
```go
func NewExample(options ...Option) *Logger {  
    encoderCfg := zapcore.EncoderConfig{  
       MessageKey:     "msg",  
       LevelKey:       "level",  
       NameKey:        "logger",  
       EncodeLevel:    zapcore.LowercaseLevelEncoder,  
       EncodeTime:     zapcore.ISO8601TimeEncoder,  
       EncodeDuration: zapcore.StringDurationEncoder,  
    }  
    core := zapcore.NewCore(zapcore.NewJSONEncoder(encoderCfg), os.Stdout, DebugLevel)  
    return New(core).WithOptions(options...)  
}
```

example：
```go
package main  
  
import (  
"go.uber.org/zap"  
)  
  
func main() {  
    logger := zap.NewExample()  
    logger.Debug("this is debug message")  
    logger.Info("this is info message")  
    logger.Info("this is info message with fileds",  
       zap.Int("age", 37),  
       zap.String("agender", "man"),  
    )  
    logger.Warn("this is warn message")  
    logger.Error("this is error message")  
}
```

## NewDevelopment()
NewDevelopment() 构建一个开发使用的 Logger，它将 DebugLevel 及以上日志信息输出。它的底层使用`NewDevelopmentConfig().Build(...Option)` 构建。
它的各种日志格式设置在函数 `NewDevelopmentEncoderConfig()`里:
```go
func NewDevelopmentEncoderConfig() zapcore.EncoderConfig {
	return zapcore.EncoderConfig{
		// Keys can be anything except the empty string.
		TimeKey:        "T",
		LevelKey:       "L",
		NameKey:        "N",
		CallerKey:      "C",
		FunctionKey:    zapcore.OmitKey,
		MessageKey:     "M",
		StacktraceKey:  "S",
		LineEnding:     zapcore.DefaultLineEnding,
		EncodeLevel:    zapcore.CapitalLevelEncoder,
		EncodeTime:     zapcore.ISO8601TimeEncoder,
		EncodeDuration: zapcore.StringDurationEncoder,
		EncodeCaller:   zapcore.ShortCallerEncoder,
	}
}
```
example:
```go
package main  
  
import (  
"time"  
  
"go.uber.org/zap"  
)  
  
func main() {  
    logger, _ := zap.NewDevelopment()  
    defer logger.Sync()  
  
    logger.Info(
	   "failed to fetch url",  
       // 强类型字段：因为以下三个函数生成的字段是“类型安全”的
       zap.String("url", "http://example.com"),  
       zap.Int("attempt", 3),  
       zap.Duration("duration", time.Second),  
    )  
  
    logger.With(  
       // 强类型字段  
       zap.String("url", "http://development.com"),  
       zap.Int("attempt", 4),  
       zap.Duration("duration", time.Second*5),  
    ).Info("[With] failed to fetch url")  
}
```
### 关于info & with
- `Info(...)` 是**立即记录一条日志**。
    
- `With(...)` 是**构造一个带有预设字段的新 Logger 实例**，以后可以重复使用这些字段。
#### 1. 使用 `Info(...)`：

```go
logger.Info("failed to fetch url",  
    zap.String("url", "http://example.com"),  
    zap.Int("attempt", 3),  
    zap.Duration("duration", time.Second),
)
```

这段代码的意思是：**立即打印一条日志**，内容是“failed to fetch url”，并附加三个字段。字段只和这一条日志有关，下一条日志不会自动带上这些字段。

---

#### 2. 使用 `With(...).Info(...)`：

```go
logger.With(  
    zap.String("url", "http://development.com"),  
    zap.Int("attempt", 4),  
    zap.Duration("duration", time.Second*5),  
).Info("[With] failed to fetch url")
```

这段代码做了两件事：

1. **构造一个新的 logger**，它默认带上这些字段（url、attempt、duration）
    
2. 用这个新的 logger 打了一条日志。
    

如果你接下来还要打多条日志，使用 `With()` 就能避免重复写这些字段。

| 对比点      | `Info()`     | `With().Info()`             |
| -------- | ------------ | --------------------------- |
| 是否立即记录日志 | 是            |  否，`With()` 只是构建新 logger    |
| 字段的作用范围  | 只对当前这条日志有效   | 对**该 logger 后续所有日志都有效**     |
| 适合的使用场景  | 一次性打日志，字段临时用 | 某一类日志共用字段（如请求 ID、用户 ID、模块名） |
| 性能开销     | 小            | 创建新的 logger，略微多一点（但开销非常小）   |


- 日志结构字段比较随机、一次性，不会复用，就用info。
```go
logger.Info("file uploaded", zap.String("filename", "report.pdf"))
```


- 某个业务逻辑下的多条日志都需要附带相同的上下文信息就用with：
```go
requestLogger := logger.With(
    zap.String("request_id", req.ID),
    zap.String("user", req.UserName),
)

// 这之后所有日志都自动带上这两个字段
requestLogger.Info("start processing")
requestLogger.Info("fetching data from db")
requestLogger.Error("db timeout")
```


你也可以嵌套 `With()`：

```go
base := logger.With(zap.String("app", "MyService"))
reqLogger := base.With(zap.String("request_id", "abc123"))
reqLogger.Info("service started")
```
当你用production构建一个logger，会输出以下内容：
```
{"level":"info","ts":1745313165.2125587,"caller":"zap_test/sugardlogger_test.go:80","msg":"service started","app":"MyService","request_id":"abc123"}
```

|使用方式|用于|
|---|---|
|`logger.Info(...)`|记录一次性临时的日志|
|`logger.With(...).X`|创建上下文相关的子日志记录器|
|`newLogger := logger.With(...)`|建立一个专属子 logger，用于多条日志复用|

## NewProduction()

NewProduction() 构建了一个合理的 Prouction 日志记录器，它将 info 及以上的日志内容以 JSON 格式记写入标准错误里。

它的底层使用 `NewProductionConfig().Build(...Option)` 构建。它的日志格式设置在函数 NewProductionEncoderConfig里：
```go
func NewProduction(options ...Option) (*Logger, error) {  
    return NewProductionConfig().Build(options...)  
}

func NewProductionConfig() Config {  
    return Config{  
       Level:       NewAtomicLevelAt(InfoLevel),  
       Development: false,  
       Sampling: &SamplingConfig{  
          Initial:    100,  
          Thereafter: 100,  
       },  
       Encoding:         "json",  
       EncoderConfig:    NewProductionEncoderConfig(),  
       OutputPaths:      []string{"stderr"},  
       ErrorOutputPaths: []string{"stderr"},  
    }  
}
```

**使用例子**：
```go
package main
import (  
"time"  
  
"go.uber.org/zap"  
)  
  
func main() {  
    logger, _ := zap.NewProduction()  
    defer logger.Sync()  
  
    url := "example.com"  
    sugar := logger.Sugar()  
    sugar.Infow("failed to fetch URL",  
       "url", url,  
       "attempt", 3,  
       "time", time.Second,  
    )
  
    sugar.Infof("Failed to fetch URL: %s", url)
}
```
<font colore:red size=5>注意:</font>
使用`logger.Fatal("hello, fatal")`会**立刻终止程序**（相当于调用 `os.Exit(1)`）
- `logger.Fatal(...)`：调用后立即终止程序（os.Exit(1)），不执行 `defer`。
    
- `logger.Panic(...)`：调用后触发 panic，可恢复。
    
- 在测试环境中，应避免使用 `Fatal()`，除非你明确想终止测试流程。

# 使用配置

在这 3 个函数中，可以传入一些配置项。为什么能传入配置项？我们来看看 [NewExample()](https://github.com/uber-go/zap/blob/v1.24.0/logger.go#L127) 函数定义：

`func NewExample(options ...Option) *Logger`

它的函数传参有一个 `...Option` 选项，是一个 interface 类型，它关联的是 Logger struct。只要返回 Option 就可以传进 NewExample() 里。在 [zap/options.go](https://github.com/uber-go/zap/blob/v1.24.0/options.go) 文件中可以看到很多返回 Option 的函数，也就是说这些函数都可以传入 NewExample 函数里。这里用到了 Go 里面的一个编码技巧，函数选项模式。

[zap.Fields()](https://github.com/uber-go/zap/blob/v1.24.0/options.go#L62) 添加字段到 Logger 中：
```go
package main  
  
import (  
"go.uber.org/zap"  
)  
  
func main() {  
    logger, _ := zap.NewProduction(zap.Fields(  
       zap.String("log_name", "testlog"),  
       zap.String("log_author", "prometheus"),  
    ))  
    defer logger.Sync()  
  
    logger.Info("test fields output")  
  
    logger.Warn("warn info")  
}
```
[zap.Hook()](https://github.com/uber-go/zap/blob/v1.24.0/options.go#L55) 添加回调函数：

Hook (钩子函数)回调函数为用户提供一种简单方法，在每次日志内容记录后运行这个回调函数，执行用户需要的操作。也就是说记录完日志后你还想做其它事情就可以调用这个函数。
```go
package main  
  
import (  
"fmt"  
  
"go.uber.org/zap"  
"go.uber.org/zap/zapcore"  
)  
  
func main() {  
    logger := zap.NewExample(zap.Hooks(func(entry zapcore.Entry) error {  
       fmt.Println("[zap.Hooks]test Hooks")  
       return nil  
    }))  
    defer logger.Sync()  
  
    logger.Info("test output")  
  
    logger.Warn("warn info")  
}
```

# logger和sugaredlogger区别
zap 有 2 种格式化日志方式：logger 和 sugared logger。

- sugared logger：
> 1. 它有很好的性能，比一般日志包快 4-10 倍。
> 2. 支持结构化的日志。
> 3. 支持 printf 风格的日志。
> 4. 日志字段不需要定义类型

- logger(没有sugar)：
> 1. **它的性能比 sugared logger 还要快**。
> 2. 它只支持强类型的结构化日志。
> 
> 它应用在对性能更加敏感日志记录中，它的内存分配次数更少。
> 
> 比如如果每一次内存分配都很重要的话可以使用这个。对类型安全有严格要求也可以使用这个。

logger 和 sugaredlogger 相互转换：
```go
// 创建 logger 
logger := zap.NewExample()
defer logger.Sync()
// 转换 SugaredLogger 
sugar := logger.Sugar()
// 转换 logger 
plain := sugar.Desugar()
```

怎么快速构建一个 logger 呢？有下面种几种方法：

- zap.NewProduction()
- zap.NewDevelopment()
- zap.Example()

主要区别：

- 记录日志信息和结构不同。
    
    **Example 和 Production 是 json 格式输出，Development 是普通一行格式输出，如果后面带有字段输出话用json格式。**
    

相同点：

- 默认情况下都会打印日志信息到 console 界面
- 都是通过 logger 调用 Info、Error 等方法

怎么选择：

- 需要不错的性能但不是很重要的情况下，可以选择 sugaredlogger。它支持结构化日志和 printf 风格的日志记录。sugaredlogger 的日志记录是松散类型的，不是强类型，能接受可变数量的键值对。如果你要用强类型字段记录，可以使用 SugaredLogger.With 方法。
- 如果是每次或每微秒记录日志都很重要情况下，可以使用 logger，它比 sugaredlogger 每次分配内存更少，性能更高。但它仅支持强类型的结构化日志记录。

# 自定义配置

快速构建 logger 日志记录器最简单的方法就是用 zap 预定义了配置的方法：`NewExample(), NewProduction()` 和`NewDevelopment()`，这 3 个方法通过单个函数调用就可以构建一个日志计记录器，也可以简单配置。

但是有的项目需要更多的定制，怎么办？zap 的 [Config](https://pkg.go.dev/go.uber.org/zap#Config) 结构和 zapcore 的 [EncoderConfig](https://pkg.go.dev/go.uber.org/zap/zapcore@v1.24.0#EncoderConfig) 结构可以帮助你，让你能够进行自定义配置。

## 配置结构说明

Config 配置项源码：
```go
// zap v1.24.0  
type Config struct {  
    // 动态改变日志级别，在运行时你可以安全改变日志级别  
    Level AtomicLevel `json:"level" yaml:"level"`  
    // 将日志记录器设置为开发模式，在 WarnLevel 及以上级别日志会包含堆栈跟踪信息  
    Development bool `json:"development" yaml:"development"`  
    // 在日志中停止调用函数所在文件名、行数  
    DisableCaller bool `json:"disableCaller" yaml:"disableCaller"`  
    // 完全禁止自动堆栈跟踪。默认情况下，在 development 中，warnlevel及以上日志级别会自动捕获堆栈跟踪信息  
    // 在 production 中，ErrorLevel 及以上也会自动捕获堆栈信息  
    DisableStacktrace bool `json:"disableStacktrace" yaml:"disableStacktrace"`  
    // 设置采样策略。没有 SamplingConfing 将禁止采样  
    Sampling *SamplingConfig `json:"sampling" yaml:"sampling"`  
    // 设置日志编码。可以设置为 console 和 json。也可以通过 RegisterEncoder 设置第三方编码格式  
    Encoding string `json:"encoding" yaml:"encoding"`  
    // 为encoder编码器设置选项。详细设置信息在 zapcore.zapcore.EncoderConfig    EncoderConfig zapcore.EncoderConfig `json:"encoderConfig" yaml:"encoderConfig"`  
    // 日志输出地址可以是一个 URLs 地址或文件路径，可以设置多个  
    OutputPaths []string `json:"outputPaths" yaml:"outputPaths"`  
    // 错误日志输出地址。默认输出标准错误信息  
    ErrorOutputPaths []string `json:"errorOutputPaths" yaml:"errorOutputPaths"`  
    // 可以添加自定义的字段信息到 root logger 中。也就是每条日志都会携带这些字段信息，公共字段  
    InitialFields map[string]interface{} `json:"initialFields" yaml:"initialFields"`  
}
```
EncoderConfig 结构源码，它里面也有很多配置选项
```go
// zapcore@v1.24.0  
type EncoderConfig struct {  
    // 为log entry设置key。如果 key 为空，那么在日志中的这部分信息也会省略  
    MessageKey     string `json:"messageKey" yaml:"messageKey"`//日志信息的健名，默认为msg  
    LevelKey       string `json:"levelKey" yaml:"levelKey"`//日志级别的健名，默认为level  
    TimeKey        string `json:"timeKey" yaml:"timeKey"`//记录日志时间的健名，默认为time  
    NameKey        string `json:"nameKey" yaml:"nameKey"`  
    CallerKey      string `json:"callerKey" yaml:"callerKey"`  
    FunctionKey    string `json:"functionKey" yaml:"functionKey"`  
    StacktraceKey  string `json:"stacktraceKey" yaml:"stacktraceKey"`  
    SkipLineEnding bool   `json:"skipLineEnding" yaml:"skipLineEnding"`  
    LineEnding     string `json:"lineEnding" yaml:"lineEnding"`  
    // 日志编码的一些设置项  
    EncodeLevel    LevelEncoder    `json:"levelEncoder" yaml:"levelEncoder"`  
    EncodeTime     TimeEncoder     `json:"timeEncoder" yaml:"timeEncoder"`  
    EncodeDuration DurationEncoder `json:"durationEncoder" yaml:"durationEncoder"`  
    EncodeCaller   CallerEncoder   `json:"callerEncoder" yaml:"callerEncoder"`  
    // 与其它编码器不同， 这个编码器可选  
    EncodeName NameEncoder `json:"nameEncoder" yaml:"nameEncoder"`  
    // 配置 interface{} 类型编码器。如果没设置，将用 json.Encoder 进行编码  
    NewReflectedEncoder func(io.Writer) ReflectedEncoder `json:"-" yaml:"-"`  
    // 配置 console 中字段分隔符。默认使用 tabConsoleSeparator string `json:"consoleSeparator" yaml:"consoleSeparator"`  
}  
type Entry struct {  
    Level      Level  
    Time       time.Time  
    LoggerName string  
    Message    string  
    Caller     EntryCaller  
    Stack      string  
}
```

# 例子1：基本配置

1. zap.Config 自定义配置，看官方的一个基本例子：
```go
package main  
  
import (  
"encoding/json"  
  
"go.uber.org/zap"  
)  
  
// https://pkg.go.dev/go.uber.org/zap@v1.24.0#hdr-Configuring_Zap  
func main() {  
    // 表示 zap.Config 的 json 原始编码  
    // outputPath: 设置日志输出路径，日志内容输出到标准输出和文件 logs.log    // errorOutputPaths：设置错误日志输出路径  
    rawJSON := []byte(`{  
      "level": "debug",      
      "encoding": "json",      
      "outputPaths": ["stdout", "./logs.log"],      
      "errorOutputPaths": ["stderr"],      
      "initialFields": {"foo": "bar"},      
      "encoderConfig": {        
      "messageKey": "message-customer",        
      "levelKey": "level",        
      "levelEncoder": "lowercase"      
      }    
      }`)  
  
    // 把 json 格式数据解析到 zap.Config struct    var cfg zap.Config  
    if err := json.Unmarshal(rawJSON, &cfg); err != nil {  
       panic(err)  
    }  
    // cfg.Build() 为配置对象创建一个 Logger    // zap.Must() 封装了 Logger，Must()函数如果返回值不是 nil，就会报 panic。也就是检查Build是否错误  
    logger := zap.Must(cfg.Build())  
    defer logger.Sync()  
  
    logger.Info("logger construction succeeded")  
}  
  
/*  
Must() 函数  
//  var logger = zap.Must(zap.NewProduction())  
func Must(logger *Logger, err error) *Logger {  
    if err != nil {        panic(err)    }  
    return logger}  
*/
```
# 例子2：高级配置

上面的配置只是基本的自定义配置，如果有一些复杂的需求，比如在多个文件之间分割日志。

或者输出到不是 file 的文件中，比如输出到 kafka 中，那么就需要使用 zapcore 包。

在下面的例子中，我们将把日志输出到 kafka 中，并且也输出到 console 里。并且我们对 kafka 不同主题进行编码设置，对输出到 console 编码进行设置，也希望处理高优先级的日志。

官方例子：
```go
package main  
  
import (  
"io"  
"os"  
  
"go.uber.org/zap"  
"go.uber.org/zap/zapcore"  
)  
  
func main() {  
    // 首先，定义不同级别日志处理逻辑  
    highPriority := zap.LevelEnablerFunc(func(lvl zapcore.Level) bool {  
       return lvl >= zapcore.ErrorLevel  
    })  
    lowPriority := zap.LevelEnablerFunc(func(lvl zapcore.Level) bool {  
       return lvl < zapcore.ErrorLevel  
    })  
  
    // 假设有2个kafka 的 topic，一个 debugging，一个 errors  
    // zapcore.AddSync 添加一个文件句柄。  
    topicDebugging := zapcore.AddSync(io.Discard)  
    topicErrors := zapcore.AddSync(io.Discard)  
  
    // 如果他们对并发使用不安全，我们可以用 zapcore.Lock 添加一个 mutex 互斥锁。  
    consoleDebugging := zapcore.Lock(os.Stdout)  
    consoleErrors := zapcore.Lock(os.Stderr)  
  
    // 设置 kafka 和 console 输出配置  
    kafkaEncoder := zapcore.NewJSONEncoder(zap.NewProductionEncoderConfig())  
    consoleEncoder := zapcore.NewConsoleEncoder(zap.NewDevelopmentEncoderConfig())  
  
    // 把上面的设置加入到 zapcore.NewCore() 函数里，然后再把他们加入到 zapcore.NewTee() 函数里  
    core := zapcore.NewTee(  
       zapcore.NewCore(kafkaEncoder, topicErrors, highPriority),  
       zapcore.NewCore(consoleEncoder, consoleErrors, highPriority),  
       zapcore.NewCore(kafkaEncoder, topicDebugging, lowPriority),  
       zapcore.NewCore(consoleEncoder, consoleDebugging, lowPriority),  
    )  
  
    // 最后调用 zap.New() 函数  
    logger := zap.New(core)  
    defer logger.Sync()  
    logger.Info("constructed a logger")  
}
```
# 例子3：日志写入文件

与上面例子2相似，但是比它简单
```go
package main  
  
import (  
"os"  
  
"go.uber.org/zap"  
"go.uber.org/zap/zapcore"  
)  
  
func main() {  
    writetofile()  
}  
  
func writetofile() {  
    // 设置一些配置参数  
    config := zap.NewProductionEncoderConfig()  
    config.EncodeTime = zapcore.ISO8601TimeEncoder  
    fileEncoder := zapcore.NewJSONEncoder(config)  
    defaultLogLevel := zapcore.DebugLevel // 设置 loglevel  
    logFile, _ := os.OpenFile("./log-test-zap.json", os.O_WRONLY|os.O_CREATE|os.O_APPEND, 06666)  
    // or os.Create()  
    writer := zapcore.AddSync(logFile)  
  
    logger := zap.New(  
       zapcore.NewCore(fileEncoder, writer, defaultLogLevel),  
       zap.AddCaller(),  
       zap.AddStacktrace(zapcore.ErrorLevel),  
    )  
    defer logger.Sync()  
  
    url := "http://www.test.com"  
    logger.Info("write log to file",  
       zap.String("url", url),  
       zap.Int("attemp", 3),  
    )  
}
```
# 例子4：根据日志级别写入不同文件

这个与上面例子2相似
```go
package main  
  
import (  
"os"  
  
"go.uber.org/zap"  
"go.uber.org/zap/zapcore"  
)  
  
func main() {  
    writeToFileWithLogLevel()  
}  
  
func writeToFileWithLogLevel() {  
    // 设置配置  
    config := zap.NewProductionEncoderConfig()  
    config.EncodeTime = zapcore.ISO8601TimeEncoder  
    fileEncoder := zapcore.NewJSONEncoder(config)  
  
    logFile, _ := os.OpenFile("./log-debug-zap.json", os.O_WRONLY|os.O_CREATE|os.O_APPEND, 0666) //日志记录debug信息  
  
    errFile, _ := os.OpenFile("./log-err-zap.json", os.O_WRONLY|os.O_CREATE|os.O_APPEND, 0666) //日志记录error信息  
  
    teecore := zapcore.NewTee(  
       zapcore.NewCore(fileEncoder, zapcore.AddSync(logFile), zap.DebugLevel),  
       zapcore.NewCore(fileEncoder, zapcore.AddSync(errFile), zap.ErrorLevel),  
    )  
  
    logger := zap.New(teecore, zap.AddCaller())  
    defer logger.Sync()  
  
    url := "http://www.diff-log-level.com"  
    logger.Info("write log to file",  
       zap.String("url", url),  
       zap.Int("time", 3),  
    )  
  
    logger.With(  
       zap.String("url", url),  
       zap.String("name", "jimmmyr"),  
    ).Error("test error ")  
}
```
# Hook和Namespace
[zap.Hook()](https://github.com/uber-go/zap/blob/v1.24.0/options.go#L55) ：

Hook (钩子函数)回调函数为用户提供一种简单方法，在每次日志内容记录后运行这个回调函数，执行用户需要的操作。也就是说记录完日志后你还想做其它事情就可以调用这个函数。
```go
package main  
  
import (  
"fmt"  
  
"go.uber.org/zap"  
"go.uber.org/zap/zapcore"  
)  
  
func main() {  
    logger := zap.NewExample(zap.Hooks(func(entry zapcore.Entry) error {  
       fmt.Println("[zap.Hooks]test Hooks")  
       return nil  
    }))  
    defer logger.Sync()  
  
    logger.Info("test output")  
  
    logger.Warn("warn info")  
}
```
[zap.Namespace()](https://github.com/uber-go/zap/blob/v1.24.0/field.go#L334):

创建一个命名空间，后面的字段都在这名字空间中。Namespace 就像一个文件夹，后面文件都放在这个文件夹里。
```GO
package main  
  
import (  
"go.uber.org/zap"  
)  
  
func main() {  
    logger := zap.NewExample()  
    defer logger.Sync()  
  
    logger.Info("some message",  
       zap.Namespace("shop"),  
       zap.String("name", "LiLei"),  
       zap.String("grade", "No2"),  
    )  
  
    logger.Error("some error message",  
       zap.Namespace("shop"),  
       zap.String("name", "LiLei"),  
       zap.String("grade", "No3"),  
    )  
}
```
# 日志切割归档
[lumberjack](https://github.com/natefinch/lumberjack) 这个库是按照日志大小切割日志文件。

安装 v2 版本：

> go get -u github.com/natefinch/lumberjack@v2


```GO
log.SetOutput(&lumberjack.Logger{ Filename: "/var/log/myapp/foo.log", // 文件位置 
MaxSize: 500, // megabytes，M 为单位，达到这个设置数后就进行日志切割
MaxBackups: 3, // 保留旧文件最大份数
MaxAge: 28, //days ， 旧文件最大保存天数
Compress: true, // disabled by default，是否压缩日志归档，默认不压缩 })
```
例子：
```GO
package main  
  
import (  
"fmt"  
  
"go.uber.org/zap"  
"go.uber.org/zap/zapcore"  
"gopkg.in/natefinch/lumberjack.v2"  
)  
  
func main() {  
    lumberjacklogger := &lumberjack.Logger{  
       Filename:   "./log-rotate-test.json",  
       MaxSize:    1, // megabytes  
       MaxBackups: 3,  
       MaxAge:     28,   //days  
       Compress:   true, // disabled by default  
    }  
    defer lumberjacklogger.Close()  
  
    config := zap.NewProductionEncoderConfig()  
  
    config.EncodeTime = zapcore.ISO8601TimeEncoder // 设置时间格式  
    fileEncoder := zapcore.NewJSONEncoder(config)  
  
    core := zapcore.NewCore(  
       fileEncoder,                       //编码设置  
       zapcore.AddSync(lumberjacklogger), //输出到文件  
       zap.InfoLevel,                     //日志等级  
    )  
  
    logger := zap.New(core)  
    defer logger.Sync()  
  
    // 测试分割日志  
    for i := 0; i < 8000; i++ {  
       logger.With(  
          zap.String("url", fmt.Sprintf("www.test%d.com", i)),  
          zap.String("name", "jimmmyr"),  
          zap.Int("age", 23),  
          zap.String("agradege", "no111-000222"),  
       ).Info("test info ")  
    }  
  
}
```
# 其它方法使用
## 全局 Logger

zap提供了 2 种全局 Logger，一个是 zap.Logger，调用 zap.L() 获取；  
另外一个是 zap.SugaredLogger ，调用 zap.S() 获取。

> 注意：直接调用 zap.L() 或 zap.S() 记录日志的话，它是不会记录任何日志信息。需要调用 ReplaceGlobals() 函数将它设置为全局 Logger。  
> ReplaceGlobals 替换全局 Logger 和 SugaredLogger，并返回一个函数来恢复原始值。  
> 并发使用它是安全的。

看看 [zap/global.go](https://github.com/uber-go/zap/blob/v1.24.0/global.go) 中的源码：
```GO
// https://github.com/uber-go/zap/blob/v1.24.0/global.go  
  
var (  
    _globalMu sync.RWMutex  
    _globalL  = NewNop()  
    _globalS  = _globalL.Sugar()  
)  
  
func L() *Logger {  
    _globalMu.RLock() // 加了读锁，所以并发使用是安全的  
    l := _globalL  
    _globalMu.RUnlock()  
    return l  
}  
  
func S() *SugaredLogger {  
    _globalMu.RLock() // 加了读锁，所以并发使用是安全的  
    s := _globalS  
    _globalMu.RUnlock()  
    return s  
}  
  
func ReplaceGlobals(logger *Logger) func() {  
    _globalMu.Lock()  
    prev := _globalL  
    _globalL = logger  
    _globalS = logger.Sugar()  
    _globalMu.Unlock()  
    return func() { ReplaceGlobals(prev) } // 返回一个函数类型  
}
```
上面源码中的关键是 _globalL = NewNop() , NewNop 函数源码在 zap/logger.go 中，这个函数返回初始化了的一个 *Logger：
```GO
// https://github.com/uber-go/zap/blob/v1.24.0/logger.go#L85  
  
func NewNop() *Logger {  
    return &Logger{  
       core:        zapcore.NewNopCore(),  
       errorOutput: zapcore.AddSync(io.Discard),  
       addStack:    zapcore.FatalLevel + 1,  
       clock:       zapcore.DefaultClock,  
    }  
}
```

上面是源码简析，下面给出一个简单使用的例子:
```GO
package main  
  
import (  
"go.uber.org/zap"  
)  
  
func main() {  
    // 直接调用是不会记录日志信息的，所以下面日志信息不会输出  
    zap.L().Info("no log info")  
    zap.S().Info("no log info [sugared]")  
  
    logger := zap.NewExample()  
    defer logger.Sync()  
  
    zap.ReplaceGlobals(logger) // 全局logger，zap.L() 和 zap.S() 需要调用 ReplaceGlobals 函数才会记录日志信息  
    zap.L().Info("log info")  
    zap.S().Info("log info [sugared]")  
}
```
## 与标准日志库搭配
zap 提供了一个函数 `NewStdLog`，可以把标准日志库 log 转换为 zap 的日志，这为我们从标准日志库转换到 zap 日志库的使用提供了简洁的转换操作。

例子：
```GO
package main  
  
import (  
"go.uber.org/zap"  
)  
  
func main() {  
    logger := zap.NewExample()  
    defer logger.Sync()  
  
    std := zap.NewStdLog(logger)  
    std.Print("standard logger wrapper")  
}
```

如果你还想设置日志级别，可以使用另外一个函数 `NewStdLogAt`，它的第二个参数就是日志级别:
```GO
NewStdLogAt(l *Logger, level zapcore.Level) (*log.Logger, error)
```
## 一段代码中使用log另外的使用zap
zap 还提供了另外一个函数 `RedirectStdLog`，它可以帮助我们在一段代码中使用标准日志库 log，其它地方还是使用 `zap.Logger`。如下例子：
```GO
package main  
  
import (  
"log"  
  
"go.uber.org/zap"  
)  
  
func main() {  
    logger := zap.NewExample()  
    defer logger.Sync()  
  
    undo := zap.RedirectStdLog(logger)  
    log.Print("redirected standard library")  
    undo()  
  
    log.Print("this zap logger")  
}
```
同样如果想增加日志级别，可以使用函数 `RedirectStdLogAt`:
```GO
func RedirectStdLogAt(l *Logger, level zapcore.Level) (func(), error)
```
## 输出调用堆栈

主要是调用函数 `zap.AddStacktrace()`
例子：
```go
package main  
  
import (  
"go.uber.org/zap"  
"go.uber.org/zap/zapcore"  
)  
  
func Hello() {  
    Warn("hello", zap.String("h", "world"), zap.Int("c", 1))  
}  
  
func Warn(msg string, fields ...zap.Field) {  
    zap.L().Warn(msg, fields...)  
}  
  
func main() {  
    logger, _ := zap.NewProduction(zap.AddStacktrace(zapcore.WarnLevel))  
    defer logger.Sync()  
  
    zap.ReplaceGlobals(logger)  
  
    Hello()  
}
```
## 输出文件名和行号

AddCaller 将 Logger 配置为使用 zap 调用者的文件名、行号和函数名称，把这些信息添加到日志记录中。它底层调用的是 `WithCaller`。

addcaller.go：
```go
package main  
  
import (  
"go.uber.org/zap"  
)  
  
func main() {  
    logger, _ := zap.NewProduction(zap.AddCaller())  
    defer logger.Sync()  
  
    logger.Info("AddCaller：line No and filename")  
}
```
logger.Info() 方法在第11行被调用。

zap 还提供了另外一个函数 `zap.AddCallerSkip(skip int) Option`，可以设置向上跳几层，然后记录文件名和行号。向上跳几层就是跳过调用者的数量。有时函数调用可能有嵌套，用这个函数可以定位到里面的函数。

addcallerskip.go
```go
package main  
  
import (  
"go.uber.org/zap"  
)  
  
func main() {  
    logger, _ := zap.NewProduction(zap.AddCaller(), zap.AddCallerSkip(1))  
    defer logger.Sync()  
  
    zap.ReplaceGlobals(logger)  
  
    Hello()  
}  
  
func Hello() {  
    Warn("hello", zap.String("h", "world"), zap.Int("c", 1))  
}  
  
func Warn(msg string, fields ...zap.Field) {  
    zap.L().Warn(msg, fields...)  
}
```
输出：
```
{"level":"warn","ts":1683308118.1684704,"caller":"zapdemos/addcallerskip.go:17","msg":"hello","h":"world","c":1}
```
日志中的 17 表示 Hello() 函数里的 Warn() 的行号。

如果 `zap.AddCallerSkip(2)` ，日志中显示行号为 13，表示 Hello() 的行号。

# zap使用总结

- zap 的使用，先创建 logger，再调用各个日志级别方法记录日志信息。比如 logger.Info()。
    
- zap 提供了三种快速创建 logger 的方法: `zap.Newproduction()`，`zap.NewDevelopment()`，`zap.NewExample()`。见名思义，Example 一般用在测试代码中，Development 用在开发环境中，Production 用在生成环境中。这三种方法都预先设置好了配置信息。它们的日志数据类型输出都是强类型。
    
- 当然，zap 也提供了给用户自定义的方法 `zap.New()`。比如用户可以自定义一些配置信息等。
    
- 在上面的例子中，几乎都有 `defer logger.Sync()` 这段代码，为什么？因为 zap 底层 API 允许缓冲日志以提高性能，在默认情况下，日志记录器是没有缓冲的。但是在进程退出之前调用 `Sync()` 方法是一个好习惯。
    
- 如果你在 zap 中使用了 **sugaredlogger**，把 zap 创建 logger 的三种方法用 `logger.Sugar()` 包装下，那么 zap 就支持 printf 风格的格式化输出，也支持以 w 结尾的方法。如 Infow，Infof 等。这种就是通用类型日志输出，不是强类型输出，不需要强制指定输出的数据类型。它们的性能区别，通用类型会比强类型下降 50% 左右。
    

比如 Infow 的输出形式，Infow 不需要 zap.String 这种指定字段的数据类型。如下代码：
```go
sugar := logger.Sugar()
sugar.Infow("failed to fetch URL",
"url", url,
"attempt", 3,
"backoff", 
time.Second, 
)
```
强类型输出，比如 Info 方法输出字段和值就需要指定数据类型：
```go
logger.Info("failed to fetch url", // 强类型字段
zap.String("url", "http://example.com"),
zap.Int("attempt", 3),
zap.Duration("backoff", time.Second), 
)
```

- **强类型**输出和**通用类型**输出区别
    
    通用类型输出，经过 interface{} 转换会有性能损失，标准库的 fmt.Printf 为了通用性就用了 interface{} 这种”万能型“的数据类型，另外它还使用了反射，性能进一步降低。
    
    zap 强类型输出，zap 为了提供日志输出性能，zap 的强类型输出没有使用 interface{} 和反射。zap 默认输出就是强类型。
    
    上面介绍，zap 中 3 种创建 logger 方式(`zap.Newproduction()`，`zap.NewDevelopment()`，`zap.NewExample()`)就是强类型日志字段，当然，也可以转化为通用类型，用 `logger.Sugar()` 方法创建 SugaredLogger。
    
- `zap.Namespace()` 创建一个命名空间，后面的字段都在这名字空间中。Namespace 就像一个文件夹，后面文件都放在这个文件夹里。

```go
logger.Info("some message",
zap.Namespace("shop"),
zap.String("shopid", "s1234323"), 
)
```


```
{"level":"info","msg":"some message","shop":{"shopid":"s1234323"}}
```













