from flask import jsonify
import blocksci

chain = blocksci.Blockchain("/root/bitcoin-data/blocksci-514496-v5")

def getBlockData(block_height):
    blockData = chain.blocks[block_height]
    response = {
        "data": {},
        "status": "success"
    }

    blockData = {
        "height": blockData.height,
        "block_hash": blockData.hash,
        "version": blockData.version,
        "numTxes": blockData.numTxes,
        "timestamp": blockData.timestamp,
        "bits": blockData.bits,
        "nonce": blockData.nonce
    }

    response["data"] = blockData
    return jsonify(response)

def getTxDataWithHash(tx_hash):
    txData = chain.tx_with_hash(tx_hash)
    response = {
        "data": {},
        "status": "success"
    }

    txData = {
        "block_height": txData.block_height,
        "tx_index": txData.tx_index,
        "tx_hash": tx_hash,
        "numIns": len(txData.txins),
        "numOuts": len(txData.txouts),
        "size_bytes": txData.size_bytes
    }

    response["data"] = txData
    return jsonify(response)

def getTxDataWithIndex(tx_index):
    txData = chain.tx_with_hash(tx_index)
    response = {
        "data": {},
        "status": "success"
    }

    txData = {
        "block_height": txData.block_height,
        "tx_index": txData.tx_index,
        "tx_hash": tx_hash,
        "numIns": len(txData.txins),
        "numOuts": len(txData.txouts),
        "size_bytes": txData.size_bytes
    }

    response["data"] = txData
    return jsonify(response)


