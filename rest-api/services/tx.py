from flask import jsonify
import blocksci

chain = blocksci.Blockchain("/root/bitcoin-data/blocksci-514496-v5")

def getTxInputs(tx_hash):
    txData = chain.tx_with_hash(tx_hash)
    txInputs = txData.ins

    response = {
        "data": [],
        "status": "success"
    }

    for x in range len(txInputs):
        inputData = {
            "spent_tx_index": txInputs[x].spent_tx_index,
            "address": txInputs[x].address,
            "value": txInputs[x].value,
            "age": txInputs[x].age,
            "block_height": txInputs[x].block.height,
            "sequence_num": txInputs[x].sequence_num
        }

        response["data"][x] = inputData


    return jsonify(response)

def getTxInputsIndex(tx_index):
    txData = chain.tx_with_hash(tx_index)
    txInputs = txData.ins

    response = {
        "data": [],
        "status": "success"
    }

    for x in range len(txInputs):
        inputData = {
            "spent_tx_index": txInputs[x].spent_tx_index,
            "address": txInputs[x].address,
            "value": txInputs[x].value,
            "age": txInputs[x].age,
            "block_height": txInputs[x].block.height,
            "sequence_num": txInputs[x].sequence_num
        }

        response["data"][x] = inputData


    return jsonify(response)

