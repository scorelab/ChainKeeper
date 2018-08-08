import React, {Component} from 'react';
import logo from '../public/logo.png';
import './App.css';

class Setup extends Component {
    render() {
        return (
            <div className="App">
                <header className="App-header">
                    <h3 style={{marginTop:"10px"}}>Welcome to ChainKeeper</h3>
                    <h5>Web Platform to Analyze Crypto Blockchain</h5>
                </header>
                <img src={logo} className="App-logo-main" style={{marginTop: "90px", height: "60px"}} alt="logo"/>
                <p className="App-intro">
                    To get started, enter the blockchain path and submit it!
                </p>
                <div className="container">
                    <div className="row" style={{marginTop:"30px"}}>
                        <div className="col-md-8 offset-md-2">
                            <form >
                                <input className="form-control mr-sm-2" type="search" placeholder="Enter blockchain path" style={{width:"100%",marginBottom:"10px"}} aria-label="Search"/>
                                <button className="btn" type="submit" style={{width:"20%" , backgroundColor:"#e6e6e6", color:"#000000", border:"2px solid #00797B"}}>Submit</button>
                            </form>
                        </div>
                    </div>
                </div>
            </div>
        );
    }
}

export default Setup;
