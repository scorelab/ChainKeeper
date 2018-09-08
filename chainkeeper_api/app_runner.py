from flask import Flask, jsonify
import sys
from flask_cors import CORS

sys.path.insert(0, 'services')

from blockchain import *
from tx import *

app = Flask(__name__)
CORS(app)

@app.route('/blocksci/api/v5/block/<int:block_height>', methods=['GET'])
def get_block(block_height):
    return getBlockData(block_height)

@app.route('/blocksci/api/v5/block/range/<int:block_height1>/<int:block_height2>', methods=['GET'])
def get_block_range(block_height1,block_height2):
    return getBlockRangeData(block_height1,block_height2)

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

@app.route('/blocksci/api/v5/tx_outputs/<string:tx_hash>', methods=['GET'])
def get_tx_outputs(tx_hash):
    return getTxOutputs(tx_hash)

@app.route('/blocksci/api/v5/tx_outputs/<int:tx_index>', methods=['GET'])
def get_tx_outputs_index(tx_index):
    return getTxOutputsIndex(tx_index)

@app.route('/blocksci/api/v5/latest_blocks', methods=['GET'])
def get_latest_blocks():
    return getLatestBlocks()

# @app.route('/blocksci/api/v5/spent_tx/', methods=['GET'])
# def get_latest_blocks():
#     return getLatestBlocks()


if __name__ == '__main__':
   app.run(host='0.0.0.0',port=8888)