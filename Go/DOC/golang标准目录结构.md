
遵循 [标准的 Go 项目布局规范（Standard Go Project Layout）](https://github.com/golang-standards/project-layout)

---

### 顶层目录结构说明：

| 目录             | 说明                                                                |
| -------------- | ----------------------------------------------------------------- |
| `api/`         | 存放 API 接口定义，比如 Protobuf、OpenAPI、GraphQL 等接口文件。常见于 gRPC 或 REST 项目。 |
| `assets/`      | 存放静态资源（如图片、CSS、JS），如果是前后端一体部署项目，可以将前端打包后的文件放这里。                   |
| `build/`       | 构建工具或 CI/CD 配置相关的文件，如 Dockerfile、Makefile、GitHub Actions 等。       |
| `cmd/`         | 每个子目录对应一个独立的可执行程序的入口点。主程序的 `main.go` 通常在这里。                       |
| `configs/`     | 存放配置文件，如 YAML、JSON 等，通常为运行时配置用。                                   |
| `deployments/` | 部署相关内容，如 Kubernetes YAML、Docker Compose 文件等。                      |
| `docs/`        | 项目的文档文件，包括设计文档、架构说明、使用说明等。                                        |
| `examples/`    | 提供项目使用方式的示例代码，方便开发者参考学习。                                          |
| `githooks/`    | Git 钩子脚本（如 pre-commit、pre-push），用于开发过程中的自动检查。                     |
| `init/`        | 初始化脚本或数据，比如数据库初始化脚本、迁移脚本等。                                        |
| `internal/`    | Go 的 internal 模块机制下的私有代码，只能在本模块中使用。通常用于实现细节封装。                    |
| `pkg/`         | 可被外部项目导入使用的公共库代码，是你希望暴露给其他开发者的部分。                                 |
| `scripts/`     | 辅助开发的脚本（shell、python 等），比如自动化部署、构建工具等。                            |
| `test/`        | 测试代码目录。可以包含集成测试、端到端测试、测试数据等。                                      |
| `third_party/` | 第三方库或依赖代码副本（通常不常见，但有些项目为了定制或依赖安全会这么做）。                            |
| `tools/`       | 命令行工具或内部工具相关代码，一般不是最终产品的一部分。                                      |
| `vendor/`      | Go module 的 vendor 依赖目录，包含了项目用到的所有第三方库的副本（可选）。                    |
| `web/`         | 若包含 Web 前端，这里是 Web 应用的代码（如 Vue、React 项目源码）。                       |
| `website/`     | 项目官网源码或宣传页面，不同于 `web/`，它更偏向项目的官方展示站点。                             |

---

###  Go 开发者的几个重点目录

- 开发者常改动的目录通常是：`cmd/`, `internal/`, `pkg/`, `api/`, `configs/`
    
- 架构设计者特别关注：`internal/`, `pkg/`, `deployments/`, `docs/`
    
- 运维或 DevOps 通常会用到：`build/`, `scripts/`, `deployments/`

