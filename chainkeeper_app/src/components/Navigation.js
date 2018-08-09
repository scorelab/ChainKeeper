import React from 'react';
import AuthUserContext from './AuthUserContext';
import {auth} from "../firebase";

const Navigation = () =>
  <AuthUserContext.Consumer>
    {authUser => authUser
      ? <NavigationAuth />
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
                    <a className="nav-link" href="/home" style={{color:"#ffffff"}}>HOME <span className="sr-only">(current)</span></a>
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

const NavigationAuth = () =>
    <nav className="navbar navbar-expand-lg" style={{backgroundColor:"#10767A", borderColor:"none", height:"80px"}}>
        <a className="navbar-brand" href="#" style={{color:"#ffffff"}}><b>CHAIN_KEEPER</b></a>
        <button className="navbar-toggler" type="button" data-toggle="collapse" data-target="#navbarText"
                aria-controls="navbarText" aria-expanded="false" aria-label="Toggle navigation">
            <span className="navbar-toggler-icon"/>
        </button>
        <div className="collapse navbar-collapse" id="navbarText">
            <ul className="navbar-nav mr-auto">
                <li className="nav-item item-hover active" style={{margin: "0 20px 0 20px"}}>
                    <a className="nav-link" href="/home " style={{color:"#ffffff"}}>HOME <span className="sr-only">(current)</span></a>
                </li>
                <li className="nav-item item-hover" style={{margin: "0 10px 0 10px"}}>
                    <a className="nav-link" href="/explorer" style={{color:"#ffffff"}}>DATA</a>
                </li>
                <li className="nav-item item-hover" style={{margin: "0 20px 0 10px"}}>
                    <a className="nav-link" href="/signin" style={{color:"#ffffff"}}>ADD TAGS</a>
                </li>
            </ul>
             <form className="form-inline my-2 my-lg-1">
              <input className="form-control mr-sm-2" type="search" style={{marginLeft:"-40px !important", width:"270px"}} placeholder="BLOCK, HASH, TRANSACTION ..." />
              <button className="btn btn-outline-success my-2 my-sm-0" type="submit">Search</button>
            </form>
            <li className="nav-item dropdown">
                <AuthUserContext.Consumer>
                    {authUser =>
                        <a style={{color: "#ffffff"}} className="nav-link dropdown-toggle" href="#"
                           id="navbarDropdownMenuLink" data-toggle="dropdown" aria-haspopup="true"
                           aria-expanded="false">
                            <i className="fa fa-user" aria-hidden="true"/> {authUser.email}
                        </a>
                    }
                </AuthUserContext.Consumer>
                <div className="dropdown-menu" aria-labelledby="navbarDropdownMenuLink">
                    <a className="dropdown-item signOutBtn" onClick={auth.doSignOut}>Sign Out</a>
                </div>
            </li>
        </div>
    </nav>;


export default Navigation;  