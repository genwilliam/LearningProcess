import json
from flask import Flask, request

app = Flask(__name__)

@app.route('/message', methods=['POST'])
def api_message():
    content_type = request.headers.get('Content-Type', '')

    # text/plain
    if content_type == 'text/plain':
        return "text message: " + request.data.decode('utf-8')

    # application/json
    elif content_type == 'application/json':
        data = request.get_json()          # 正确的获取 JSON
        return "json message: " + json.dumps(data)

    # application/octet-stream
    elif content_type == 'application/octet-stream':
        with open('./binary', 'wb') as f:
            f.write(request.data)
        return "Binary message written!"

    else:
        return "415 Unsupported Media Type ;)"

if __name__ == '__main__':
    app.run()