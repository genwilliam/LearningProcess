document.getElementById("loginForm").addEventListener("submit", function (e) {
    e.preventDefault();
    
    const username = document.getElementById("username").value;
    const password = document.getElementById("password").value;
  
    if (username === "admin" && password === "123456") {
      window.location.href = "exam.html";  // 登录成功，跳转到考试页面
    } else {
      alert("用户名或密码错误！");
    }
  });
  