# 注册登录

> 注册账户不能登录是因为没有添加到代码中，可以使用浏览器缓存，以下你可以看情况改

你遇到的这个问题是因为在当前的实现中，我们的注册功能并没有将注册的账户信息保存在某个地方（如本地存储或浏览器的 `localStorage`）以便后续登录时验证。这是导致登录验证失败的原因。

要解决这个问题，可以在用户注册时将用户名和密码存储在浏览器的 `localStorage` 中，然后在登录时从 `localStorage` 获取并验证这些信息。

### 解决方案

1. **注册时将用户名和密码存储到 `localStorage`**。
2. **登录时从 `localStorage` 获取存储的用户名和密码进行验证**。

### 1. **修改注册页面 (reg.html)**

我们在注册时将用户名和密码存储到 `localStorage`。

```html
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>注册页面</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            text-align: center;
            margin-top: 50px;
        }

        .register-box {
            width: 300px;
            margin: auto;
            padding: 20px;
            border: 1px solid #ccc;
        }

        input {
            width: 100%;
            padding: 10px;
            margin: 5px 0;
        }

        button {
            width: 100%;
            padding: 10px;
            background-color: #4CAF50;
            color: white;
            border: none;
        }

        .link {
            margin-top: 10px;
        }
    </style>
</head>

<body>
    <div class="register-box">
        <h2>注册</h2>
        <input type="text" id="regUsername" placeholder="用户名" required />
        <input type="password" id="regPassword" placeholder="密码" required />
        <input type="password" id="confirmPassword" placeholder="确认密码" required />
        <button onclick="register()">注册</button>
        <div class="link">
            <button onclick="window.location.href='login.html'">返回登录</button>
        </div>
    </div>

    <script>
        function register() {
            const username = document.getElementById("regUsername").value;
            const password = document.getElementById("regPassword").value;
            const confirmPassword = document.getElementById("confirmPassword").value;

            // 检查用户名和密码是否为空
            if (!username || !password || !confirmPassword) {
                alert("请填写所有字段");
                return;
            }

            // 检查密码是否一致
            if (password !== confirmPassword) {
                alert("密码和确认密码不一致");
                return;
            }

            // 检查用户名是否已存在
            if (localStorage.getItem(username)) {
                alert("用户名已存在，请选择其他用户名");
                return;
            }

            // 将用户名和密码存储到 localStorage
            localStorage.setItem(username, password);

            // 假设注册成功
            alert("注册成功！");
            window.location.href = "login.html";  // 注册成功后返回登录页面
        }
    </script>
</body>

</html>
```

### 2. **修改登录页面 (login.html)**

在登录时，我们从 `localStorage` 获取存储的用户名和密码并验证。

```html
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>管理员登录</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            text-align: center;
            margin-top: 50px;
        }

        .login-box {
            width: 300px;
            margin: auto;
            padding: 20px;
            border: 1px solid #ccc;
        }

        input {
            width: 100%;
            padding: 10px;
            margin: 5px 0;
        }

        button {
            width: 100%;
            padding: 10px;
            background-color: #4CAF50;
            color: white;
            border: none;
        }

        .link {
            margin-top: 10px;
        }
    </style>
</head>

<body>
    <div class="login-box">
        <h2>管理员登录</h2>
        <input type="text" id="username" placeholder="用户名" required />
        <input type="password" id="password" placeholder="密码" required />
        <button onclick="login()">登录</button>
        <div class="link">
            <button onclick="window.location.href='reg.html'">注册</button>
        </div>
    </div>

    <script>
        function login() {
            const username = document.getElementById("username").value;
            const password = document.getElementById("password").value;

            // 从 localStorage 获取用户名和密码
            const storedPassword = localStorage.getItem(username);

            // 检查用户名和密码是否正确
            if (storedPassword && storedPassword === password) {
                alert("登录成功！");
                window.location.href = "exam.html";  // 登录成功跳转到考试页面
            } else {
                alert("用户名或密码错误");
            }
        }
    </script>
</body>

</html>
```

### 3. **功能改进说明**

- **注册页面：** 在注册时，我们将用户名和密码存储到 `localStorage` 中。这样即使页面刷新，数据仍然能保留。
  - 通过 `localStorage.setItem(username, password)` 存储用户信息。
  - 增加了用户名重复检查，如果已有相同用户名的账户，系统会提示用户。
- **登录页面：** 在登录时，使用 `localStorage.getItem(username)` 获取保存的密码进行比对。
  - 如果用户名和密码匹配，跳转到考试页面。
  - 如果不匹配，弹出“用户名或密码错误”提示。

### 4. **总结**

- 通过使用 `localStorage` 来存储注册的账户信息，我们确保了用户可以在登录时验证注册的账户。
- 这种方式是前端存储的简单实现，不涉及后端数据库，适用于简单的静态网站或原型开发。



# admin.html

要在添加试题后将新的题目直接保存到代码中，或者在试题管理页面中动态添加试题并更新页面展示，可以按以下几个步骤进行操作。

### 思路

- **动态添加试题**：可以通过 `prompt` 获取用户输入的试题内容（包括问题、选项和答案），然后将新题目添加到现有的 `questions` 数组中。
- **展示更新后的试题**：在添加题目后，调用 `displayQuestions()` 函数重新渲染页面，展示新添加的题目。
- **持久化存储**：如果你希望在页面刷新后依然保留新添加的题目，可以使用 `localStorage` 来存储题目数据。

### 具体实现步骤：

1. **通过 `prompt` 添加试题**：已经在现有代码中使用 `prompt` 让管理员输入新的题目，接下来只需要处理数据并显示到页面上。
2. **在试题中动态添加题目**：
   - 添加新题目时，将其插入到 `questions` 数组中。
   - 调用 `displayQuestions()` 来重新渲染页面。
3. **存储新题目**：为了让新题目在页面刷新后依然存在，可以使用 `localStorage` 来存储题目数据。`localStorage` 可以保存数据，即使页面刷新或者浏览器关闭后，数据仍然存在。

### 修改后的代码：

#### 1. `admin.html` 页面：

```html
<!DOCTYPE html>
<html lang="en">

<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>试题管理</title>
  <style>
    body {
      font-family: Arial, sans-serif;
      text-align: center;
      margin-top: 50px;
    }

    .question-list {
      margin-bottom: 20px;
      text-align: left;
    }

    button {
      padding: 10px 20px;
      background-color: #4CAF50;
      color: white;
      border: none;
    }
  </style>
</head>

<body>
  <h2>试题管理</h2>
  <div class="question-list" id="questionList"></div>
  <button onclick="addQuestion()">添加试题</button>

  <script>
    // 从 localStorage 获取试题列表，若没有则使用默认题目
    let questions = JSON.parse(localStorage.getItem("questions")) || [
      { question: "1+1等于多少？", options: ["1", "2", "3", "4"], answer: "2" },
      { question: "2+2等于多少？", options: ["2", "3", "4", "5"], answer: "4" }
    ];

    function displayQuestions() {
      const questionList = document.getElementById("questionList");
      questionList.innerHTML = ''; // 清空列表
      questions.forEach((q, index) => {
        let questionHTML = `<div>
                              <p>${q.question}</p>
                              <ul>`;
        q.options.forEach(opt => {
          questionHTML += `<li>${opt}</li>`;
        });
        questionHTML += `</ul>
                          <p>正确答案: ${q.answer}</p>
                          <button onclick="deleteQuestion(${index})">删除</button>
                          <hr></div>`;
        questionList.innerHTML += questionHTML;
      });

      // 将题目保存到 localStorage 中
      localStorage.setItem("questions", JSON.stringify(questions));
    }

    function addQuestion() {
      // 通过弹窗获取管理员输入的新题目
      const question = prompt("请输入新题目:");
      const answer = prompt("请输入正确答案:");
      const options = prompt("请输入选项，用逗号分隔:").split(",");

      // 将新题目添加到 questions 数组
      questions.push({ question, options, answer });

      // 重新显示更新后的试题
      displayQuestions();
    }

    function deleteQuestion(index) {
      // 从数组中删除指定的题目
      questions.splice(index, 1);

      // 重新显示更新后的试题
      displayQuestions();
    }

    // 初始化页面时显示所有试题
    displayQuestions();
  </script>
</body>

</html>
```

### 主要修改点：

1. **使用 `localStorage` 保存题目数据**：
   - `localStorage.setItem("questions", JSON.stringify(questions))`：将题目数据保存到 `localStorage` 中，以便页面刷新后能保留数据。
   - `JSON.parse(localStorage.getItem("questions"))`：从 `localStorage` 中读取数据，如果没有数据则使用默认的题目。
2. **添加试题后更新显示**：
   - 每次添加试题时，会将新的题目加入 `questions` 数组，并调用 `displayQuestions()` 来更新页面内容。
   - 删除试题时，同样更新 `questions` 数组并重新显示。
3. **确保数据持久化**：
   - 数据存储在 `localStorage` 中，即使页面刷新或重新打开，数据依然存在。

### 运行效果：

- 页面会显示所有的题目（从 `localStorage` 获取）。
- 当添加新题目时，弹窗会提示输入题目、正确答案和选项。
- 每次添加或删除题目时，页面内容会自动更新，并且数据会持久化存储在浏览器的 `localStorage` 中。

通过这种方式，管理员可以方便地管理试题，且所有更改都会被保存，即使页面刷新或重新打开。