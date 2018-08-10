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
  state = {
    redirect: ""
  };

  renderRedirect = () => {
    if (this.state.redirect === "home") {
      return <Redirect to='/home' />
    }else if(this.state.redirect === "setup"){
      return <Redirect to='/setup' />
    }
  };

    componentDidMount() {
        let checkPath = db.ref();
        let valType = null;
        checkPath.once('value', (snapshot) => {
            if (snapshot.hasChild("path")) {
                valType = "home";
            } else {
                valType = "setup";
            }

          this.setState({
            redirect: valType
          });
        });

        console.log(valType);
        console.log(this.state);
    };

  render() {
    return (
      <div className="container">
        <div className="row" style={{marginTop:"30px"}}>
            <div className="col-md-12">
                {this.renderRedirect()}
                <h3 style={{textAlign:"center"}}>LOADING ....</h3>
            </div>
        </div>
      </div>
    );
  }

}


export default withRouter(MainLandingPage);