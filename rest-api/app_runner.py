from flask import Flask, jsonify
import sys
sys.path.insert(0, 'services')

from blockchain import *

app = Flask(__name__)

@app.route('/blocksci/api/v5/tasks', methods=['GET'])
def get_tasks():
    return getAddressCount()


if __name__ == '__main__':
   app.run(debug = True)