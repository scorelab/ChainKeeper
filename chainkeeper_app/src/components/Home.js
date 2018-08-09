import React, { Component } from 'react';
import Navigation from './Navigation';

const MainPage = () =>
  <div>
       <Navigation/>
       <HomePage />
  </div>

class HomePage extends Component {

  render() {
    return (
      <div className="container">
        <div className="row" style={{marginTop:"30px"}}>
            <div className="col-md-12">
                <h3>LATEST BLOCKS</h3>

                <div>
                    <table class="table table-striped" style={{marginTop:"20px"}}>
                        <thead>
                        <tr>
                            <th scope="col">Height</th>
                            <th scope="col">Age</th>
                            <th scope="col">Transactions</th>
                            <th scope="col">Total Sent</th>
                            <th scope="col">Size (kB)</th>
                            <th scope="col">Hash</th>
                        </tr>
                        </thead>
                        <tbody>
                        <tr>
                            <td>535894</td>
                            <td>7 minutes</td>
                            <td>638</td>
                            <td>2,092.29 BTC</td>
                            <td>277.29</td>
                            <td>77f1c71f5ab2085fd7be0c78433563ad73cd3ce8a539d824acfca4bced41bb35</td>
                        </tr>
                        <tr>
                            <td>535894</td>
                            <td>7 minutes</td>
                            <td>638</td>
                            <td>2,092.29 BTC</td>
                            <td>277.29</td>
                            <td>77f1c71f5ab2085fd7be0c78433563ad73cd3ce8a539d824acfca4bced41bb35</td>
                        </tr>
                        <tr>
                            <td>535894</td>
                            <td>7 minutes</td>
                            <td>638</td>
                            <td>2,092.29 BTC</td>
                            <td>277.29</td>
                            <td>77f1c71f5ab2085fd7be0c78433563ad73cd3ce8a539d824acfca4bced41bb35</td>
                        </tr>
                        <tr>
                            <td>535894</td>
                            <td>7 minutes</td>
                            <td>638</td>
                            <td>2,092.29 BTC</td>
                            <td>277.29</td>
                            <td>77f1c71f5ab2085fd7be0c78433563ad73cd3ce8a539d824acfca4bced41bb35</td>
                        </tr>
                        <tr>
                            <td>535894</td>
                            <td>7 minutes</td>
                            <td>638</td>
                            <td>2,092.29 BTC</td>
                            <td>277.29</td>
                            <td>77f1c71f5ab2085fd7be0c78433563ad73cd3ce8a539d824acfca4bced41bb35</td>
                        </tr>
                        <tr>
                            <td>535894</td>
                            <td>7 minutes</td>
                            <td>638</td>
                            <td>2,092.29 BTC</td>
                            <td>277.29</td>
                            <td>77f1c71f5ab2085fd7be0c78433563ad73cd3ce8a539d824acfca4bced41bb35</td>
                        </tr>
                        <tr>
                            <td>535894</td>
                            <td>7 minutes</td>
                            <td>638</td>
                            <td>2,092.29 BTC</td>
                            <td>277.29</td>
                            <td>77f1c71f5ab2085fd7be0c78433563ad73cd3ce8a539d824acfca4bced41bb35</td>
                        </tr>
                        <tr>
                            <td>535894</td>
                            <td>7 minutes</td>
                            <td>638</td>
                            <td>2,092.29 BTC</td>
                            <td>277.29</td>
                            <td>77f1c71f5ab2085fd7be0c78433563ad73cd3ce8a539d824acfca4bced41bb35</td>
                        </tr>
                        <tr>
                            <td>535894</td>
                            <td>7 minutes</td>
                            <td>638</td>
                            <td>2,092.29 BTC</td>
                            <td>277.29</td>
                            <td>77f1c71f5ab2085fd7be0c78433563ad73cd3ce8a539d824acfca4bced41bb35</td>
                        </tr>

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