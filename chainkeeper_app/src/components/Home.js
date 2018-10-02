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
      isLoading: false,
    };
  }

  componentDidMount() {
     this.setState({ isLoading: true });

    fetch("http://192.248.22.171:8080/blocksci/api/v5/latest_blocks")
      .then(response => response.json())
      .then(hits => this.setState({ elements: hits.data, isLoading: false }));

  }


  render() {
    const { elements, isLoading } = this.state;

    if (isLoading) {
      return <p style={{textAlign:"center", marginTop:"80px"}}>Loading ...</p>;
    }

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
                              <td><a style={{color:"#2268ad"}} href={'/explorer/block/'+ hit.height}>{hit.height}</a></td>
                            <td>{hit.timestamp}</td>
                            <td>{hit.numTxes}</td>
                            <td>{hit.output_value} BTC</td>
                            <td>{hit.size}</td>
                            <td><a style={{color:"#2268ad"}} href={'/explorer/block/'+ hit.height}>{hit.block_hash}</a></td>
			    <button className="btn btn-outline-success my-2 my-sm-0" type="button" ><a href={'/explorer/block/'+ hit.height}>View Details</a></button>
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
