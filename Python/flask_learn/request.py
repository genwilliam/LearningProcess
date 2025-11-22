from flask import Flask, request

app = Flask(__name__)

@app.route('/hello')
def hello():
    if 'name' in request.args:
        return 'hello ' + request.args['name']
    else:
        return hello

app.run()