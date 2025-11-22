from flask import Flask, jsonify, request

app = Flask(__name__)

@app.errorhandler(404)
def api_not_found(e):
    return jsonify({
        "status": 404,
        "message": "Not Found: " + request.url
    }), 404


@app.route('/user/<id>', methods=['GET'])
def api_user(user_id):
    user = {
        '1': 'william',
        '2': 'peter',
        '3': 'nil'
    }
    if user_id in user:
        return jsonify({
            "id": user_id,
            "name": user[user_id]
        })
    else:
        return api_not_found(None)


app.run(debug=True)