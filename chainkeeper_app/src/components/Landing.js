import React, { Component } from 'react';
import NavigationComp from './Navigation';
import {db} from "../firebase/firebase";

const MainLandingPage = () =>
  <div>
       <NavigationComp/>
       <LandingPage />
  </div>

class LandingPage extends Component {
  constructor(props){
      super(props);
      this.componentDidMount = this.componentDidMount.bind(this);
  }

  componentDidMount = () =>{
        let checkPath = db.ref();
        checkPath.once('value', function(snapshot) {
          if (snapshot.hasChild("path")) {
            this.props.history.push('/home');
          }else{
              
          }
        });
    };

  render() {
    return (
      <div className="container">
        <div className="row" style={{marginTop:"30px"}}>
            <div className="col-md-12">
                <h3 style={{textAlign:"center"}}>LOADING ....</h3>
            </div>
        </div>
      </div>
    );
  }

}


export default MainLandingPage;