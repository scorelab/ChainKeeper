# Blockchain Data API

API calls are available with CORS headers. More APIs will be added in soon. 

##### Install Requirements

  - pip install -r requirements.txt

##### Single Block Data

  - End Point - <b>http://domain.com/blocksci/api/v5/block/$block_height</b>
  - Example - <b>http://domain.com/blocksci/api/v5/block/514494</b>
  - Result - 

```sh
{
    "data": {
        "block_hash": "00000000000000000011ee21567ee5a168e5800531c2cf59530b03d31e3fea0d",
        "height": 514494,
        "next_block": "0000000000000000002f0e36273d1026648403461520ce9ae32b342e05b70941",
        "nonce": 579496330,
        "numTxes": 701,
        "output_value": 3139.92189929,
        "prev_block": "000000000000000000172fbc2dc756519a20815f8bbff5a0b8fb19a3a368e2dd",
        "size": 376859,
        "timestamp": 1521615810,
        "tx": [Tx array with data],
    "status": "success"
}
```

##### Block Range Data

  - End Point - <b>http://domain.com/blocksci/api/v5/block/range/$block_height_From/$block_height_To</b>
  - Example - <b>http://domain.com/blocksci/api/v5/block/range/123/200</b>
  - Result - 

```sh
{
    "data": [
        {
            "block_hash": "00000000a3bbe4fd1da16a29dbdaba01cc35d6fc74ee17f794cf3aab94f7aaa0",
            "height": 123,
            "nonce": 4094077204,
            "numTxes": 1,
            "output_value": 50,
            "size": 216,
            "timestamp": 1231677823
        },
        {
            "block_hash": "00000000ceae2b1cb578f066bd08c672fe87814880671c205febb2d624184f21",
            "height": 124,
            "nonce": 1878174981,
            "numTxes": 1,
            "output_value": 50,
            "size": 216,
            "timestamp": 1231678278
        }
	.....................
    ],
    "status": "success"
}
```

##### Tx Data with Hash

  - End Point - <b>http://domain.com/blocksci/api/v5/tx_with_hash/$tx_hash</b>
  - Example - <b>http://domain.com/blocksci/api/v5/tx_with_hash/53fa4435a2c5d6a66fd88d94bcb078c737b25cf676d7256ffded44f50ca41831</b>
  - Result - 

```sh
{
    "data": {
        "block_height": 143234,
        "numIns": 1,
        "numOuts": 2,
        "output_value": 500,
        "size_bytes": 258,
        "tx_hash": "53fa4435a2c5d6a66fd88d94bcb078c737b25cf676d7256ffded44f50ca41831",
        "tx_index": 1406392,
        "weight": 1032
    },
    "status": "success"
}
```

##### Tx Data with Index

  - End Point - <b>http://domain.com/blocksci/api/v5/tx_with_index/$tx_index</b>
  - Example - <b>http://domain.com/blocksci/api/v5/tx_with_index/1406392</b>
  - Result - 

```sh
{
    "data": {
        "block_height": 143234,
        "numIns": 1,
        "numOuts": 2,
        "output_value": 500,
        "size_bytes": 258,
        "tx_hash": "53fa4435a2c5d6a66fd88d94bcb078c737b25cf676d7256ffded44f50ca41831",
        "tx_index": 1406392,
        "weight": 1032
    },
    "status": "success"
}
```

##### Tx Input Data with Tx Hash

  - End Point - <b>http://domain.com/blocksci/api/v5/tx_inputs/$tx_hash</b>
  - Example - <b>http://domain.com/blocksci/api/v5/tx_inputs/53fa4435a2c5d6a66fd88d94bcb078c737b25cf676d7256ffded44f50ca41831</b>
  - Result - 

```sh
{
    "data": [
        {
            "address": "PubkeyHashAddress(1D14wY9HUivwQZv2JWXtxCx6QyzsrTsX6E)",
            "age": 11296,
            "block_height": 143234,
            "sequence_num": 4294967295,
            "spent_tx_index": 795970,
            "value": 500
        }
    ],
    "status": "success"
}
```

##### Tx Input Data with Tx Index

  - End Point - <b>http://domain.com/blocksci/api/v5/tx_inputs/$tx_index</b>
  - Example - <b>http://domain.com/blocksci/api/v5/tx_inputs/1406392</b>
  - Result - 

```sh
{
    "data": [
        {
            "address": "PubkeyHashAddress(1D14wY9HUivwQZv2JWXtxCx6QyzsrTsX6E)",
            "age": 11296,
            "block_height": 143234,
            "sequence_num": 4294967295,
            "spent_tx_index": 795970,
            "value": 500
        }
    ],
    "status": "success"
}
```

##### Tx Output Data with Tx Hash

  - End Point - <b>http://domain.com/blocksci/api/v5/tx_outputs/$tx_hash</b>
  - Example - <b>http://domain.com/blocksci/api/v5/tx_outputs/53fa4435a2c5d6a66fd88d94bcb078c737b25cf676d7256ffded44f50ca41831</b>
  - Result - 

```sh
{
    "data": [
        {
            "address": "PubkeyHashAddress(125vg4Nksznp8oSMyxUV9U9VaZKZYAs2cH)",
            "block_height": 143234,
            "is_spent": true,
            "spending_tx_index": 1412617,
            "value": 268
        },
        {
            "address": "PubkeyHashAddress(153SRAtbLJxUQvqcxLnmXnc6YSPQq4YanU)",
            "block_height": 143234,
            "is_spent": true,
            "spending_tx_index": 1476316,
            "value": 232
        }
    ],
    "status": "success"
}
```

##### Tx Output Data with Tx Index

  - End Point - <b>http://domain.com/blocksci/api/v5/tx_outputs/$tx_index</b>
  - Example - <b>http://domain.com/blocksci/api/v5/tx_outputs/1406392</b>
  - Result - 

```sh
{
    "data": [
        {
            "address": "PubkeyHashAddress(125vg4Nksznp8oSMyxUV9U9VaZKZYAs2cH)",
            "block_height": 143234,
            "is_spent": true,
            "spending_tx_index": 1412617,
            "value": 268
        },
        {
            "address": "PubkeyHashAddress(153SRAtbLJxUQvqcxLnmXnc6YSPQq4YanU)",
            "block_height": 143234,
            "is_spent": true,
            "spending_tx_index": 1476316,
            "value": 232
        }
    ],
    "status": "success"
}
```


