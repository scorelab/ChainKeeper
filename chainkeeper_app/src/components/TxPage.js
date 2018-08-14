import React, { Component } from 'react';
import NavigationComp from './Navigation';
import '../public/css/main.css';
import '../public/fonts/font-awesome-4.7.0/css/font-awesome.css';
import './App.css';

// const TxPage = () =>
  {/*<div>*/}
       {/*<NavigationComp/>*/}
       {/*<TxData />*/}
  {/*</div>*/}

class TxPage extends Component {
  constructor(props) {
    super(props);

    this.state = {
      elements: [],
      isLoading: false,
      ins:[],
      outs:[],
    };
  }

  componentDidMount() {
       this.setState({ isLoading: true });
       let openVal = this.props.match.params.id;

        fetch("http://192.248.22.171:8080/blocksci/api/v5/tx_with_hash/"+openVal)
              .then(response => response.json())
              .then(hits => this.setState({ elements: hits.data}));

        fetch("http://192.248.22.171:8080/blocksci/api/v5/tx_inputs/"+openVal)
              .then(response => response.json())
              .then(hits => this.setState({ ins: hits.data }));

        fetch("http://192.248.22.171:8080/blocksci/api/v5/tx_outputs/"+openVal)
              .then(response => response.json())
              .then(hits => this.setState({ outs: hits.data, isLoading: false }));
  }

  render() {
    const { elements, ins, outs, isLoading } = this.state;

    if (isLoading) {
      return <p style={{textAlign:"center", marginTop:"80px"}}>Loading ...</p>;
    }

    return (
      <div>
        <NavigationComp/>
      <div className="container">
        <div className="row" style={{marginTop:"40px"}}>
            <div className="col-md-12">
                <h3>Transaction <small>View information about a bitcoin transaction</small></h3>
            </div>
        </div>
        <div className="row" style={{marginTop:"30px"}}>
            <div className="col-md-5">
                <div style={{marginTop:"30px"}}>
                    <table id="transactionTable" className="table table-striped" style={{marginTop:"20px"}}>
                        <thead>
                        <tr>
                            <th scope="col">Inputs</th>
                        </tr>
                        </thead>
                        <tbody>
                        {ins.length > 0
                            ? ins.map(hit =>
                                <tr>
                                    <td>{hit.address.split("(")[1].slice(0, -1)} </td>
                                </tr>
                            ):
                            <tr>
                                <td>No any inputs</td>
                            </tr>
                        }
                        </tbody>
                    </table>
                </div>
            </div>
            <div className="col-md-2">
               <center>
                <i class="fa fa-arrow-right" aria-hidden="true" style={{color:"#26BB5A", fontSize:"28px", textAlign:"center",marginTop:"40px"}}/>
                </center>
            </div>
            <div className="col-md-5">
                <div style={{marginTop:"30px"}}>
                    <table id="transactionTable" className="table table-striped" style={{marginTop:"20px"}}>
                        <thead>
                        <tr>
                            <th scope="col">Outputs</th>
                            <th scope="col">Amount</th>
                        </tr>
                        </thead>
                        <tbody>
                        {outs.length > 0
                            ? outs.map(hit =>
                                <tr>
                                    <td>{hit.address.split("(")[1].slice(0, -1)} </td>
                                    <td>{hit.value} BTC</td>
                                </tr>
                            ):
                            <tr>
                                <td>No any outputs</td>
                                <td>-</td>
                            </tr>
                        }
                        </tbody>
                    </table>
                </div>
            </div>
        </div>

        <div className="row" style={{marginTop:"-10px"}}>
            <div className="col-md-12">
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
                            <td>Hash</td>
                            <td>a1537589f42c9f9251e3b0d8bfa59a94d2aaf961bbe5163b2b4ea20687fda000</td>
                        </tr>
                        <tr>
                            <td>Size</td>
                            <td>290 (bytes)</td>
                        </tr>
                        <tr>
                            <td>Weight</td>
                            <td>1052</td>
                        </tr>
                        <tr>
                            <td>Confirmations</td>
                            <td>14</td>
                        </tr>
                        <tr>
                            <td>Total Amount</td>
                            <td>234.4 BTC</td>
                        </tr>

                        </tbody>
                    </table>
                    </div>

                    <div className="col-md-7">
                    </div>
                </div>

            </div>
        </div>
      </div>
      </div>
    );
  }
}


export default TxPage;