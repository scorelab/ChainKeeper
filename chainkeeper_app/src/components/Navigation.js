import React from 'react';
import { Link } from 'react-router-dom';
import { LinkContainer } from "react-router-bootstrap";

import AuthUserContext from './AuthUserContext';
import * as routes from '../constants/routes';

const Navigation = () =>
  <AuthUserContext.Consumer>
    {authUser => authUser
      ? <NavigationNonAuth />
      : <NavigationNonAuth />
    }
  </AuthUserContext.Consumer>

const NavigationNonAuth = () =>
    <nav className="navbar navbar-expand-lg" style={{backgroundColor:"#10767A", borderColor:"none", height:"80px"}}>
        <a className="navbar-brand" href="#" style={{color:"#ffffff"}}><b>CHAIN_KEEPER</b></a>
        <button className="navbar-toggler" type="button" data-toggle="collapse" data-target="#navbarText"
                aria-controls="navbarText" aria-expanded="false" aria-label="Toggle navigation">
            <span className="navbar-toggler-icon"/>
        </button>
        <div className="collapse navbar-collapse" id="navbarText">
            <ul className="navbar-nav mr-auto">
                <li className="nav-item item-hover active" style={{margin: "0 20px 0 20px"}}>
                    <a className="nav-link" href="/" style={{color:"#ffffff"}}>HOME <span className="sr-only">(current)</span></a>
                </li>
                <li className="nav-item item-hover" style={{margin: "0 10px 0 10px"}}>
                    <a className="nav-link" href="/explorer" style={{color:"#ffffff"}}>DATA</a>
                </li>
                <li className="nav-item item-hover" style={{margin: "0 20px 0 10px"}}>
                    <a className="nav-link" href="/signin" style={{color:"#ffffff"}}>SIGN IN</a>
                </li>
            </ul>
             <form className="form-inline my-2 my-lg-1">
              <input className="form-control mr-sm-2" type="search" style={{marginLeft:"-40px !important", width:"270px"}} placeholder="BLOCK, HASH, TRANSACTION ..." />
              <button className="btn btn-outline-success my-2 my-sm-0" type="submit">Search</button>
            </form>
        </div>
    </nav>;


export default Navigation;