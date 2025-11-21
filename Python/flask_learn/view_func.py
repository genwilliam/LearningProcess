from flask import Flask, request
# 视图函数
# 处理请求并返回响应
# 通常接收请求对象作为参数，并返回响应对象，或者直接返回字符串、HTML 等
app = Flask(__name__)

@app.route('/greet/<name>')
def greet(name):
    return f'Hello, {name}!'

if __name__ == '__main__':
    app.run()