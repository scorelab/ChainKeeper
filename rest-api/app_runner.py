from flask import Flask, jsonify
import sys
sys.path.insert(0, 'services')

from blockchain import *
from tx import *

app = Flask(__name__)

@app.route('/blocksci/api/v5/block/<int:block_height>', methods=['GET'])
def get_block(block_height):
    return getBlockData(block_height)

@app.route('/blocksci/api/v5/tx_with_hash/<string:tx_hash>', methods=['GET'])
def get_tx_hash(tx_hash):
    return getTxDataWithHash(tx_hash)

@app.route('/blocksci/api/v5/tx_with_index/<int:tx_index>', methods=['GET'])
def get_tx_index(tx_index):
    return getTxDataWithIndex(tx_index)

@app.route('/blocksci/api/v5/tx_inputs/<string:tx_hash>', methods=['GET'])
def get_tx_inputs(tx_hash):
    return getTxInputs(tx_hash)

@app.route('/blocksci/api/v5/tx_inputs/<int:tx_index>', methods=['GET'])
def get_tx_inputs_index(tx_index):
    return getTxInputsIndex(tx_index)


if __name__ == '__main__':
   app.run(debug = True)