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

    for x in range(len(txInputs)):
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

    for x in range(len(txInputs)):
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

def getTxOutputs(tx_hash):
    txData = chain.tx_with_hash(tx_hash)
    txOutputs = txData.outs

    response = {
        "data": [],
        "status": "success"
    }

    for x in range(len(txOutputs)):
        outputData = {
            "is_spent": txOutputs[x].is_spent,
            "spending_tx_index": txOutputs[x].spending_tx_index,
            "address": txOutputs[x].address,
            "value": txOutputs[x].value,
            "block_height": txOutputs[x].block.height
        }

        response["data"][x] = outputData


    return jsonify(response)

def getTxOutputsIndex(tx_index):
    txData = chain.tx_with_hash(tx_index)
    txOutputs = txData.outs

    response = {
        "data": [],
        "status": "success"
    }

    for x in range(len(txOutputs)):
        outputData = {
            "is_spent": txOutputs[x].is_spent,
            "spending_tx_index": txOutputs[x].spending_tx_index,
            "address": txOutputs[x].address,
            "value": txOutputs[x].value,
            "block_height": txOutputs[x].block.height
        }

        response["data"][x] = outputData


    return jsonify(response)


