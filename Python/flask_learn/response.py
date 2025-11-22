import json

from flask import Response, Flask

app = Flask(__name__)

@app.route('/hello', methods=['GET'])
def api_hello():
    data = {
        "hello": "world",
        "age": 18
    }
    data_json = json.dumps(data)
    res = Response(data_json, status=200, mimetype='application/json')
    res.headers['Link'] = 'http://luisrei.com'
    return res

app.run()