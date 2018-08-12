import React, { Component } from 'react';
import NavigationComp from './Navigation';

const MainPage = () =>
  <div>
       <NavigationComp/>
       <HomePage />
  </div>

class HomePage extends Component {
  constructor(props) {
    super(props);

    this.state = {
      elements: [],
    };
  }

  componentDidMount() {
  let headers = new Headers();

  headers.append('Content-Type', 'application/json');
  headers.append('Accept', 'application/json');

  headers.append('Access-Control-Allow-Origin', '*');

  headers.append('GET', 'POST', 'OPTIONS');

    let options = {
      method: 'GET',
      mode: 'cors',
      header: headers
    };

    fetch("http://192.248.22.171:8080/blocksci/api/v5/latest_blocks", options)
      .then(response => response.json())
      .then(hits => this.setState({ elements: hits.data }));
  }


  render() {
    const { elements } = this.state;

    return (
      <div className="container">
        <div className="row" style={{marginTop:"30px"}}>
            <div className="col-md-12">
                <h3>LATEST BLOCKS</h3>

                <div>
                    <table id="latestBlocks" className="table table-striped" style={{marginTop:"20px"}}>
                        <thead>
                        <tr>
                            <th scope="col">Height</th>
                            <th scope="col">Timestamp</th>
                            <th scope="col">Transactions</th>
                            <th scope="col">Total Sent</th>
                            <th scope="col">Size (kB)</th>
                            <th scope="col">Hash</th>
                        </tr>
                        </thead>
                        <tbody>

                        {elements.map(hit =>
                          <tr key={hit.height}>
                            <td>{hit.height}</td>
                            <td>{hit.timestamp}</td>
                            <td>{hit.numTxes}</td>
                            <td>{hit.output_value} BTC</td>
                            <td>{hit.size}</td>
                            <td>{hit.block_hash}</td>
                          </tr>
                        )}
                        </tbody>
                    </table>
                </div>
            </div>
        </div>
      </div>
    );
  }
}


export default MainPage;