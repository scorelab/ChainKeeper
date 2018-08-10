import React, { Component } from 'react';
import NavigationComp from './Navigation';
import { withRouter } from 'react-router-dom';

import '../public/css/main.css';
import '../public/fonts/font-awesome-4.7.0/css/font-awesome.css';
import './App.css';

// const BlockPage = () =>
//   <div>
//        <NavigationComp/>
//        <BlockData />
//   </div>

class BlockPage extends Component {
  componentDidMount() {
       console.log(this.props.match.params.id);
  }

  render() {
    return (
      <div>
        <NavigationComp/>
      <div className="container">
        <div className="row" style={{marginTop:"40px"}}>
            <div className="col-md-12">
                <h3>BLOCK #123</h3>

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
                            <td>2323</td>
                        </tr>
                        <tr>
                            <td>Output Total</td>
                            <td>2,577.40401907 BTC</td>
                        </tr>
                        <tr>
                            <td>Transaction Fees</td>
                            <td>0.06544274 BTC</td>
                        </tr>
                        <tr>
                            <td>Timestamp</td>
                            <td>2018-08-09 10:55:19</td>
                        </tr>
                        <tr>
                            <td>Nonce</td>
                            <td>3811265984</td>
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
                            <td>0000000000000000000bb1fabcfdcaa46c3d1163e2550f2397506b190187de60</td>
                        </tr>
                        <tr>
                            <td>Previous Block</td>
                            <td>000000000000000000172230089aed596ecf30eef1f1109b007c6c0d9dd746b7</td>
                        </tr>
                        <tr>
                            <td>Next Block(s)</td>
                            <td>00000000000000000010cb12be8e360d03867eaf1675f9ad8a1e8d9e280be0e1</td>
                        </tr>
                        <tr>
                            <td>Merkle Root</td>
                            <td>ebcfe2d23d22696052c797f6fc0dc06c32d3cfb52f817a473a5d97810066c105</td>
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
                            <th scope="col">Timestamp</th>
                        </tr>
                        </thead>
                        <tbody>
                        <tr>
                            <td>77f1c71f5ab2085fd7be0c78433563ad73cd3ce8a539d824acfca4bced41bb35</td>
                            <td>23</td>
                            <td>4</td>
                            <td>23.445 BTC</td>
                            <td>2018-08-09 10:53:28</td>
                        </tr>
                        <tr>
                            <td>77f1c71f5ab2085fd7be0c78433563ad73cd3ce8a539d824acfca4bced41bb35</td>
                            <td>23</td>
                            <td>4</td>
                            <td>23.445 BTC</td>
                            <td>2018-08-09 10:53:28</td>
                        </tr>
                        <tr>
                            <td>77f1c71f5ab2085fd7be0c78433563ad73cd3ce8a539d824acfca4bced41bb35</td>
                            <td>23</td>
                            <td>4</td>
                            <td>23.445 BTC</td>
                            <td>2018-08-09 10:53:28</td>
                        </tr>
                        <tr>
                            <td>77f1c71f5ab2085fd7be0c78433563ad73cd3ce8a539d824acfca4bced41bb35</td>
                            <td>23</td>
                            <td>4</td>
                            <td>23.445 BTC</td>
                            <td>2018-08-09 10:53:28</td>
                        </tr>
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