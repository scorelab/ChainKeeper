from flask import jsonify

def getAddressCount():
    count = {"addressCount":10}
    return jsonify(count)