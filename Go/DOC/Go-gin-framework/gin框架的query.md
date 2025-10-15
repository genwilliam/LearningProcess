在Gin框架中，`Query` 是用于获取 URL 中查询参数的方法。例如，当一个 HTTP 请求的 URL 包含 `?key=value` 这样的查询参数时，我们可以使用 `Query` 方法来获取这个参数的值。Gin 中的 `Query` 方法是非常常用的，因为在很多 GET 请求中会携带查询参数。

### 示例

假设我们有一个 URL 请求如下：

```
<http://localhost:8080/user?name=tom&age=25>

```

在这个请求中，`name` 和 `age` 就是查询参数，我们可以通过 `Query` 方法来获取它们的值。

在 Gin 中的使用方式如下：

```go
package main

import (
    "github.com/gin-gonic/gin"
    "net/http"
)

func main() {
    r := gin.Default()

    r.GET("/user", func(c *gin.Context) {
        name := c.Query("name") // 获取查询参数 "name" 的值
        age := c.Query("age")   // 获取查询参数 "age" 的值

        // 如果参数不存在，还可以设置默认值
        location := c.DefaultQuery("location", "unknown")

        c.JSON(http.StatusOK, gin.H{
            "name":     name,
            "age":      age,
            "location": location,
        })
    })

    r.Run(":8080") // 启动服务器，监听 8080 端口
}

```

在上面的代码中：

- `c.Query("name")` 会返回查询参数 `name` 的值，例如 `tom`。
- `c.Query("age")` 会返回查询参数 `age` 的值，例如 `25`。
- `c.DefaultQuery("location", "unknown")` 用于获取 `location` 参数，如果该参数不存在，则返回默认值 `unknown`。

### `Query` 和 `DefaultQuery` 的区别

- `Query` 方法：如果请求的 URL 中不存在指定的查询参数，返回的是空字符串 `""`。
- `DefaultQuery` 方法：如果请求的 URL 中不存在指定的查询参数，返回的是指定的默认值。

### 适用场景

在 RESTful API 中，查询参数通常用于过滤、分页、排序等操作，而 `Query` 方法正是帮助我们方便地获取这些参数，用于业务逻辑处理。