from flask import jsonify
import blocksci
import sys

chain = blocksci.Blockchain("/root/bitcoin-data/blocksci-514496-v5")

#get block data function with block height
def getBlockData(block_height):
    response = {
        "data": {},
        "status": "success"
    }

    if(len(chain.blocks) < block_height):
        response["status"] = "failed: Maximum block height is "+str(len(chain.blocks))
        return jsonify(response)
    else:
        blockData = chain.blocks[block_height]

        blockData = {
            "height": blockData.height,
            "block_hash": str(blockData.hash),
            "output_value": (blockData.output_value/100000000),
            "numTxes": blockData.tx_count,
            "timestamp": blockData.timestamp,
            "size": blockData.size_bytes,
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

        if(len(chain.blocks) > block_height2):
            element = []
            for x in range(rangeVal + 1):
                blockData = chain.blocks[block_height1 + x]

                blockData = {
                    "height": blockData.height,
                    "block_hash": str(blockData.hash),
                    "output_value": (blockData.output_value/100000000),
                    "numTxes": blockData.tx_count,
                    "timestamp": blockData.timestamp,
                    "size": blockData.size_bytes,
                    "nonce": blockData.nonce
                }

                element.append(blockData)
            response["data"] = element

            return jsonify(response)
        else:
            response["status"] = "failed: Maximum block height is "+str(len(chain.blocks))
            return jsonify(response)


#get tx data function with hash
def getTxDataWithHash(tx_hash):
    response = {
        "data": {},
        "status": "success"
    }

    try:
        txData = chain.tx_with_hash(tx_hash)

        txData = {
            "block_height": txData.block_height,
            "tx_index": txData.index,
            "tx_hash": str(txData.hash),
            "numIns": len(txData.inputs),
            "numOuts": len(txData.outputs),
            "size_bytes": txData.size_bytes,
            "weight": txData.weight,
            "output_value": (txData.output_value / 100000000)
        }

        response["data"] = txData
        return jsonify(response)


    except:  # catch *all* exceptions
        e = sys.exc_info()[0]
        response["status"] = str(e)
        return jsonify(response)


#get tx data function with tx_index
def getTxDataWithIndex(tx_index):
    response = {
        "data": {},
        "status": "success"
    }

    try:
        txData = chain.tx_with_index(int(tx_index))

        txData = {
            "block_height": txData.block_height,
            "tx_index": txData.index,
            "tx_hash": str(txData.hash),
            "numIns": len(txData.inputs),
            "numOuts": len(txData.outputs),
            "size_bytes": txData.size_bytes,
            "weight": txData.weight,
            "output_value": (txData.output_value / 100000000)
        }

        response["data"] = txData
        return jsonify(response)
    except:  # catch *all* exceptions
        e = sys.exc_info()[0]
        response["status"] = str(e)
        return jsonify(response)


