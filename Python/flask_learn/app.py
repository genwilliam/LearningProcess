from flask import Flask
app = Flask(__name__)

@app.route("/hello") # 默认get方法
def hello():
    return "Hello World!"

@app.route("/home", methods=["POST"])
def home():
    return "welcome to home page"


if __name__ == '__main__':
    app.run()