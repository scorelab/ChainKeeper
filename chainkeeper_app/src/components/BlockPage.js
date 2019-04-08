import React, { Component } from 'react';
import NavigationComp from './Navigation';

import '../public/css/main.css';
import '../public/fonts/font-awesome-4.7.0/css/font-awesome.css';
import './App.css';


class BlockPage extends Component {
  constructor(props) {
    super(props);

    this.state = {
      elements: [],
      isLoading: false,
      next:0,
      prev:0,
      txes:[],
    };
  }

  componentDidMount() {
       this.setState({ isLoading: true });
       let openVal = parseInt(this.props.match.params.id, 10);

        fetch("http://192.248.22.171:8080/blocksci/api/v5/block/"+openVal)
              .then(response => response.json())
              .then(hits => this.setState({ elements: hits.data, txes:hits.data.tx, next:(openVal+1),prev:(openVal-1), isLoading: false }));
  };

  render() {
    const { txes, isLoading } = this.state;

    if (isLoading) {
      return <p style={{textAlign:"center", marginTop:"80px"}}>Loading ...</p>;
    }

    return (
      <div>
        <NavigationComp/>
      <div className="container">
        <div className="row" style={{marginTop:"40px"}}>
            <div className="col-md-12">
                <h3>BLOCK #{this.state.elements.height}</h3>

                <div className="row">
                    <div className="col-md-5">
                            <table id="blockSummary" className="table table-striped" style={{marginTop:"20px"}}>
                                <thead>
                                <tr>
                                    <th scope="col">Summary</th>
                                    <th scope="col"/>

                                </tr>
                                </thead>
                                <tbody>
                                <tr>
                                    <td>Number Of Transactions</td>
                                    <td>{this.state.elements.numTxes}</td>
                                </tr>
                                <tr>
                                    <td>Output Total</td>
                                    <td>{this.state.elements.output_value} BTC</td>
                                </tr>
                                <tr>
                                    <td>Size</td>
                                    <td>{this.state.elements.size}</td>
                                </tr>
                                <tr>
                                    <td>Timestamp</td>
                                    <td>{this.state.elements.timestamp}</td>
                                </tr>
                                <tr>
                                    <td>Nonce</td>
                                    <td>{this.state.elements.nonce}</td>
                                </tr>

                                </tbody>
                            </table>
                    </div>

                    <div className="col-md-7">
                        <table id="hashesTable" className="table table-striped" style={{marginTop:"20px"}}>
                        <thead>
                        <tr>
                            <th scope="col">Hashes</th>
                            <th scope="col"/>

                        </tr>
                        </thead>
                        <tbody>
                        <tr>
                            <td>Hash</td>
                            <td><a style={{color:"#2268ad"}}  href={'/explorer/block/'+this.state.elements.height}>{this.state.elements.block_hash}</a></td>
                        </tr>
                        <tr>
                            <td>Previous Block</td>
                            <td><a style={{color:"#2268ad"}}  href={'/explorer/block/'+this.state.prev}>{this.state.elements.prev_block}</a></td>
                        </tr>
                        <tr>
                            <td>Next Block(s)</td>
                            <td><a style={{color:"#2268ad"}}  href={'/explorer/block/'+this.state.next}>{this.state.elements.next_block}</a></td>
                        </tr>
                        </tbody>
                    </table>
                    </div>
                </div>

            </div>
        </div>

        <div className="row" style={{marginTop:"30px"}}>
            <div className="col-md-12">
                <h4>Transactions</h4>

                <div style={{marginTop:"30px"}}>
                    <table id="transactionTable" className="table table-striped" style={{marginTop:"20px"}}>
                        <thead>
                        <tr>
                            <th scope="col">Hash</th>
                            <th scope="col">Inputs</th>
                            <th scope="col">Outputs</th>
                            <th scope="col">Amount</th>
                            <th scope="col">Size (bytes)</th>
                        </tr>
                        </thead>
                        <tbody>

                        {txes.map(hit =>
                        <tr key={hit.block_height}>
                            <td><a style={{color:"#2268ad"}}  href={'/explorer/tx/'+hit.tx_hash}>{hit.tx_hash}</a></td>
                            <td>{hit.numIns}</td>
                            <td>{hit.numOuts}</td>
                            <td>{hit.output_value} BTC</td>
                            <td>{hit.size_bytes}</td>
                        </tr>
                        )}
                        </tbody>
                    </table>
                </div>
            </div>
        </div>
      </div>
      </div>
    );
  }
}


export default BlockPage;
