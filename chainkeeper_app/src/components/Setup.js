import React, {Component} from 'react';
import logo from '../public/images/logo.png';
import './App.css';
import { withRouter } from 'react-router';
import {db} from "../firebase/firebase";

const FORM_STATE = {
  path:'',
};

const byPropKey = (propertyName, value) => () => ({
  [propertyName]: value,
});



class Setup extends Component {
    constructor(){
        super();
        this.state = { ...FORM_STATE };


        this.setupPath = db.ref("path");
        this.handleSubmit = this.handleSubmit.bind(this);

        // setupPath.once('value', function(snapshot) {
        //   if (snapshot.hasChild("mempool")) {
        //     this.props.history.push('/home')
        //   }
        // });
    }

    handleSubmit(event) {
        event.preventDefault();
        const {
                path
            } = this.state;

        this.setupPath.push({
                    setupPath: path,
                });

        alert("Submitted Successfully!");
        this.setState({...FORM_STATE});
        this.props.history.push('/home')
    }

    render() {
        const {
            path
        } = this.state;

        const isInvalid =
              path === '';

        return (
            <div className="App">
                <header className="App-header">
                    <h3 style={{marginTop:"10px"}}>Welcome to ChainKeeper</h3>
                    <h5>Web Platform to Analyse Crypto Blockchain</h5>
                </header>
                <img src={logo} className="App-logo-main" style={{marginTop: "90px", height: "60px"}} alt="logo"/>
                <p className="App-intro">
                    To get started, enter the blockchain path and submit it!
                </p>
                <div className="container">
                    <div className="row" style={{marginTop:"30px"}}>
                        <div className="col-md-8 offset-md-2">
                            <form onSubmit={this.handleSubmit}>
                                <input className="form-control mr-sm-2"
                                       type="search"
                                       placeholder="Enter blockchain path"
                                       style={{width:"100%",marginBottom:"10px"}}
                                       aria-label="Search"
                                       value={path}
                                       onChange={event => this.setState(byPropKey('path', event.target.value))}

                                />
                                <button className="btn" type="submit" disabled={isInvalid} style={{width:"20%" , backgroundColor:"#e6e6e6", color:"#000000", border:"2px solid #074a84"}}>Submit</button>

                                {error && <p style={{color: '#aa1d1d'}}>{error.message}</p>}
                            </form>
                        </div>
                    </div>
                </div>
            </div>
        );
    }
}

export default withRouter(Setup);
