from flask import Flask, request
app = Flask(__name__)

@app.route('/methods',methods = ['GET','POST', 'PUT'])
def methods():
    if request.method == 'GET':
        return 'method is GET'
    elif request.method == 'POST':
        return 'method is POST'
    elif request.method == 'PUT':
        return 'method is PUT'
    else:
        return 'method'

app.run()