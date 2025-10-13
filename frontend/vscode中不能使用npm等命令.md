# vscode中不能使用npm等命令

这个问题与 PowerShell 脚本的执行策略有关。Windows 系统的 PowerShell 默认会限制某些脚本的运行，尤其是当你尝试运行 npm 命令时，可能会出现此错误。这是因为 PowerShell 的执行策略（Execution Policy）阻止了脚本的执行。

### 解决方法：

1. **查看当前执行策略**：
你可以在 PowerShell 中运行以下命令查看当前的执行策略：
    
    ```powershell
    Get-ExecutionPolicy
    
    ```
    
    如果返回的是 `Restricted`，那就意味着禁止了脚本的执行。
    
2. **修改执行策略**：
你可以临时修改执行策略来允许脚本的运行。使用以下命令（管理员权限）修改执行策略为 `RemoteSigned` 或 `Unrestricted`：
    
    ```powershell
    Set-ExecutionPolicy RemoteSigned -Scope CurrentUser
    
    ```
    
    这将允许你运行本地脚本，同时仍然要求从互联网下载的脚本需要签名。
    
    或者，你可以使用 `Unrestricted` 策略：
    
    ```powershell
    Set-ExecutionPolicy Unrestricted -Scope CurrentUser
    
    ```
    
    如果你希望恢复默认的执行策略，可以使用：
    
    ```powershell
    Set-ExecutionPolicy Restricted -Scope CurrentUser
    
    ```
    
3. **尝试重新运行命令**：
修改执行策略后，重新启动 VSCode，试着运行 `npm build serve` 看是否能够成功。

### 为什么 WebStorm 可以运行？

WebStorm 可能以不同的方式启动或配置了环境，使得它绕过了这个执行策略的限制。例如，它可能通过某些内置的设置或者不同的终端程序执行 npm 命令，而没有遇到 PowerShell 执行策略的问题。

### 注意：

- 这个解决方法是针对 PowerShell 的限制，而非 npm 或 VSCode 的问题。
- 如果你的机器上有其他的安全限制或组织策略，也可能需要联系管理员来调整相关设置。

如果你不想修改 PowerShell 的执行策略，还有其他几种方法可以绕过这个问题：

### 1. **使用 `cmd`（命令提示符）**:

你可以直接使用 Windows 自带的命令提示符（`cmd`）来运行 `npm` 命令，而不是在 PowerShell 中运行。`cmd` 通常不受 PowerShell 执行策略的影响。

步骤：

- 打开 VSCode 终端，并切换到 `cmd`（点击终端右上角的下拉菜单，选择 `Select Default Profile`，然后选择 `Command Prompt`）。
- 然后你可以在 `cmd` 中运行 `npm build serve`。

### 2. **使用 Git Bash**:

如果你安装了 Git，你可以使用 Git Bash 来运行 npm 命令。Git Bash 是一个模拟类 Unix 环境的终端，不会受 PowerShell 执行策略的限制。

步骤：

- 在 VSCode 中打开 Git Bash 终端（点击终端右上角的下拉菜单，选择 `Git Bash`）。
- 然后运行 `npm build serve`。

### 3. **直接运行 `npm` 文件**:

你可以在文件资源管理器中手动找到 `npm.ps1` 文件，然后直接运行它，或者通过 `node` 直接运行相关的 JavaScript 脚本。

步骤：

- 找到 `npm` 可执行文件所在的路径，通常在 `E:\\ProgramFiles(x86)\\Node\\` 下。
- 直接使用 `node` 运行相关的 `.js` 文件。例如：
    
    ```bash
    node E:\\ProgramFiles(x86)\\Node\\npm-cli.js build server
    
    ```
    

### 4. **修改 VSCode 设置**:

你还可以在 VSCode 中调整终端的启动设置，确保其不会使用 PowerShell。你可以通过以下步骤来配置 VSCode 使用 `cmd` 或 Git Bash：

- 打开 VSCode 设置（快捷键 `Ctrl + ,`）。
- 搜索 `terminal.integrated.shell.windows`，然后设置为 `cmd.exe` 或 Git Bash 的路径。
    - 如果选择 `cmd.exe`，路径通常是 `C:\\Windows\\System32\\cmd.exe`。
    - 如果选择 Git Bash，路径通常是 `C:\\Program Files\\Git\\bin\\bash.exe`（根据你的安装路径可能会有所不同）。

### 5. **临时绕过 PowerShell 执行策略**:

你可以使用 `powershell -ExecutionPolicy Bypass -File npm.ps1` 命令临时绕过执行策略限制。这样可以在不永久修改执行策略的情况下运行 npm 命令：

```bash
powershell -ExecutionPolicy Bypass -File E:\\ProgramFiles(x86)\\Node\\npm.ps1 build server

```

### 总结：

最简单的解决方法是使用 `cmd` 或 Git Bash 来运行命令，这样你就不会碰到 PowerShell 的执行策略限制。如果你确实希望继续使用 PowerShell，可以通过修改终端的默认设置或通过绕过执行策略来实现。

如果你有其他偏好或需求，欢迎告诉我！