`event.preventDefault();` 是 JavaScript 中用于阻止事件的默认行为的方法。

### 作用：

在事件触发时，`event.preventDefault()` 会阻止浏览器执行该事件的默认行为。例如：

- 对于 `submit` 事件，默认行为是提交表单并刷新页面。
- 对于 `click` 事件，默认行为可能是打开链接或触发某个按钮的点击效果。

通过调用 `event.preventDefault()`，您可以阻止这些默认行为，并自定义事件处理逻辑。

### 解释：

假设您的代码如下：

```javascript
document.getElementById('dnslog-form').addEventListener('submit', function(event) {
    event.preventDefault();
    // 自定义代码逻辑
});
```

1. **`submit` 事件的默认行为**：当您点击“提交”按钮时，浏览器默认会提交表单并重新加载页面。调用 `event.preventDefault()` 会阻止这一行为，确保页面不会重新加载。
    
2. **自定义行为**：使用 `event.preventDefault()` 后，您可以在 `submit` 事件发生时添加自己的行为，例如用 JavaScript 发送 AJAX 请求，而不是刷新页面。
    

### 示例：

假设您有一个表单，点击“提交”按钮后，浏览器默认会刷新页面并发送表单数据到服务器。如果您希望在提交表单时避免页面刷新，可以使用 `event.preventDefault()`，并通过 JavaScript 处理表单数据。

```html
<form id="myForm">
    <input type="text" id="name">
    <button type="submit">提交</button>
</form>

<script>
document.getElementById('myForm').addEventListener('submit', function(event) {
    event.preventDefault(); // 阻止表单的默认提交行为
    console.log('表单已提交，但没有刷新页面');
});
</script>
```

### 总结：

`event.preventDefault()` 用于阻止浏览器执行与事件相关的默认行为，使得开发者可以控制事件的处理方式。