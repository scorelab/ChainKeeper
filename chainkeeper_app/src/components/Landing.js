import React, { Component } from 'react';
import NavigationComp from './Navigation';
import {db} from "../firebase/firebase";
import { withRouter } from 'react-router';
import { Redirect } from 'react-router'

const MainLandingPage = () =>
  <div>
       <NavigationComp/>
       <LandingPage />
  </div>

class LandingPage extends Component {

  constructor() {
        super();

        this.state = {
            redirect: ""
          };

    }

  renderRedirect = () => {
    if (this.state.redirect === "home") {
      return <Redirect to='/home' />
    }else if(this.state.redirect === "setup"){
      return <Redirect to='/setup' />
    }
  };

    componentDidMount() {
        this.mounted = true;

        let checkPath = db.ref();
        let valType = null;
        checkPath.once('value', (snapshot) => {
            if (snapshot.hasChild("path")) {
                valType = "home";
            } else {
                valType = "setup";
            }

          if(this.mounted) {
              this.setState({
                  redirect: valType
              });
          }
        });
    };

    componentWillUnmount(){
        this.mounted = false;
    }

  render() {
    return (
      <div className="container">
        {this.renderRedirect()}
        <div className="row" style={{marginTop:"30px"}}>
            <div className="col-md-12">
                <h3 style={{textAlign:"center"}}>LOADING ....</h3>
            </div>
        </div>
      </div>
    );
  }

}


export default withRouter(MainLandingPage);