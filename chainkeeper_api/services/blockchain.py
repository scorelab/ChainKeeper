from flask import jsonify
import blocksci

chain = blocksci.Blockchain("/root/bitcoin-data/blocksci-514496-v5")

#get block data function with block height
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
        "numTxes": blockData.tx_count,
        "timestamp": blockData.timestamp,
        "bits": blockData.bits,
        "nonce": blockData.nonce
    }

    response["data"] = blockData
    return jsonify(response)

#get block data function for block data range
def getBlockRangeData(block_height1,block_height2):
    rangeVal = block_height2 - block_height1

    response = {
        "data": [],
        "status": "success"
    }

    if(rangeVal < 0):
        response["status"] = "failed: Invalid block range"
        return jsonify(response)
    else:
        for x in range(rangeVal):
            blockData = chain.blocks[block_height1 + x]

            blockData = {
                "height": blockData.height,
                "block_hash": blockData.hash,
                "version": blockData.version,
                "numTxes": blockData.tx_count,
                "timestamp": blockData.timestamp,
                "bits": blockData.bits,
                "nonce": blockData.nonce
            }

            response["data"][x] = blockData

    return jsonify(response)


#get tx data function with hash
def getTxDataWithHash(tx_hash):
    txData = chain.tx_with_hash(tx_hash)
    response = {
        "data": {},
        "status": "success"
    }

    txData = {
        "block_height": txData.block_height,
        "tx_index": txData.tx_index,
        "tx_hash": txData.tx_hash,
        "numIns": len(txData.txins),
        "numOuts": len(txData.txouts),
        "size_bytes": txData.size_bytes
    }

    response["data"] = txData
    return jsonify(response)


#get tx data function with tx_index
def getTxDataWithIndex(tx_index):
    txData = chain.tx_with_hash(tx_index)
    response = {
        "data": {},
        "status": "success"
    }

    txData = {
        "block_height": txData.block_height,
        "tx_index": txData.tx_index,
        "tx_hash": txData.tx_hash,
        "numIns": len(txData.txins),
        "numOuts": len(txData.txouts),
        "size_bytes": txData.size_bytes
    }

    response["data"] = txData
    return jsonify(response)


