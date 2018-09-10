from flask import jsonify
import blocksci
import sys

chain = blocksci.Blockchain("/root/bitcoin-data/blocksci-514496-v5")

def getTxInputs(tx_hash):
    response = {
        "data": [],
        "status": "success"
    }

    try:
        txData = chain.tx_with_hash(tx_hash)
        txInputs = txData.ins

        element = []
        for x in range(len(txInputs)):
            inputData = {
                "spent_tx_index": txInputs[x].spent_tx_index,
                "address": str(txInputs[x].address),
                "value": (txInputs[x].value/100000000),
                "age": txInputs[x].age,
                "block_height": txInputs[x].block.height,
                "sequence_num": txInputs[x].sequence_num
            }

            element.append(inputData)

        response["data"] = element
        return jsonify(response)

    except:  # catch *all* exceptions
        e = sys.exc_info()[0]
        response["status"] = str(e)

        return jsonify(response)

def getTxInputsIndex(tx_index):
    response = {
        "data": [],
        "status": "success"
    }

    try:
        txData = chain.tx_with_index(int(tx_index))
        txInputs = txData.ins

        element = []
        for x in range(len(txInputs)):
            inputData = {
                "spent_tx_index": txInputs[x].spent_tx_index,
                "address": str(txInputs[x].address),
                "value": (txInputs[x].value/100000000),
                "age": txInputs[x].age,
                "block_height": txInputs[x].block.height,
                "sequence_num": txInputs[x].sequence_num
            }
            element.append(inputData)

        response["data"] = element
        return jsonify(response)

    except:  # catch *all* exceptions
        e = sys.exc_info()[0]
        response["status"] = str(e)

        return jsonify(response)

def getTxOutputs(tx_hash):
    response = {
        "data": [],
        "status": "success"
    }

    try:
        txData = chain.tx_with_hash(tx_hash)
        txOutputs = txData.outs

        element = []
        for x in range(len(txOutputs)):
            outputData = {
                "is_spent": txOutputs[x].is_spent,
                "spending_tx_index": txOutputs[x].spending_tx_index,
                "address": str(txOutputs[x].address),
                "value": (txOutputs[x].value/100000000),
                "block_height": txOutputs[x].block.height
            }

            element.append(outputData)

        response["data"] = element
        return jsonify(response)

    except:  # catch *all* exceptions
        e = sys.exc_info()[0]
        response["status"] = str(e)

        return jsonify(response)

def getTxOutputsIndex(tx_index):
    response = {
        "data": [],
        "status": "success"
    }

    try:
        txData = chain.tx_with_index(int(tx_index))
        txOutputs = txData.outs

        element = []
        for x in range(len(txOutputs)):
            outputData = {
                "is_spent": txOutputs[x].is_spent,
                "spending_tx_index": txOutputs[x].spending_tx_index,
                "address": str(txOutputs[x].address),
                "value": (txOutputs[x].value/100000000),
                "block_height": txOutputs[x].block.height
            }

            element.append(outputData)

        response["data"] = element
        return jsonify(response)

    except:  # catch *all* exceptions
        e = sys.exc_info()[0]
        response["status"] = str(e)

        return jsonify(response)

def getSpentTx(tx_index, input_index):
    response = {
        "data": [],
        "status": "success"
    }

    try:
        txData = chain.tx_with_index(tx_index)
        tx_inputs = txData.inputs
        input_selected = tx_inputs[input_index]
        spent_tx = input_selected.spent_tx

        txData = {
            "block_height": spent_tx.block_height,
            "tx_index": spent_tx.index,
            "tx_hash": str(spent_tx.hash),
            "numIns": len(spent_tx.inputs),
            "numOuts": len(spent_tx.outputs),
            "size_bytes": spent_tx.size_bytes,
            "weight": spent_tx.weight,
            "output_value": (spent_tx.output_value / 100000000)
        }

        response["data"] = txData
        return jsonify(response)

    except:  # catch *all* exceptions
        e = sys.exc_info()[0]
        response["status"] = str(e)

        return jsonify(response)

def getSpendingTx(tx_index, input_index):
    response = {
        "data": [],
        "status": "success"
    }

    try:
        txData = chain.tx_with_index(tx_index)
        tx_outputs = txData.outputs
        output_selected = tx_outputs[input_index]
        isSpent = output_selected.is_spent

        if isSpent:
            spending_tx = output_selected.spending_tx

            txData = {
                "block_height": spending_tx.block_height,
                "tx_index": spending_tx.index,
                "tx_hash": str(spending_tx.hash),
                "numIns": len(spending_tx.inputs),
                "numOuts": len(spending_tx.outputs),
                "size_bytes": spending_tx.size_bytes,
                "weight": spending_tx.weight,
                "output_value": (spending_tx.output_value / 100000000)
            }

            response["data"] = txData
            return jsonify(response)
        else:
            response["data"] = "output not spend yet"
            return jsonify(response)

    except:  # catch *all* exceptions
        e = sys.exc_info()[0]
        response["status"] = str(e)

        return jsonify(response)
