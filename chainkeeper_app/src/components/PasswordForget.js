import React, { Component } from 'react';
import { Link } from 'react-router-dom';

import { auth } from '../firebase';
import * as routes from "../constants/routes";
import Navigation from './Navigation';

const PasswordForgetPage = () =>
  <div>
    <Navigation/>
    <PasswordForgetForm />
  </div>

const byPropKey = (propertyName, value) => () => ({
  [propertyName]: value,
});

const INITIAL_STATE = {
  email: '',
  error: null,
};

class PasswordForgetForm extends Component {
  constructor(props) {
    super(props);

    this.state = { ...INITIAL_STATE };
  }

  onSubmit = (event) => {
    const { email } = this.state;

    auth.doPasswordReset(email)
      .then(() => {
        this.setState(() => ({ ...INITIAL_STATE }));
      })
      .catch(error => {
        this.setState(byPropKey('error', error));
      });

    event.preventDefault();
  }

  render() {
    const {
      email,
      error,
    } = this.state;

    const isInvalid = email === '';

    return (
        <div className="limiter">
                <div className="container-login100 back-login">
                    <div className="wrap-login100">
                        <form className="login100-form validate-form" onSubmit={this.onSubmit}>
                             <span className="login100-form-title p-b-1" style={{marginTop:"-40px", color:'#52595b', fontSize:'16px',fontFamily: 'Poppins-Regular'}}>
                                <b>ENTER YOUR EMAIL HERE</b>
                                <hr/>
                            </span>

                            <div className="wrap-input100 validate-input" data-validate="Valid email is: a@b.c">
                                <input
                                  value={email}
                                  onChange={event => this.setState(byPropKey('email', event.target.value))}
                                  type="text"
                                  className="input100"
                                />
                                <span className="focus-input100" data-placeholder="Email" />
                            </div>

                            <div className="container-login100-form-btn">
                                <div className="wrap-login100-form-btn">
                                    <div className="login100-form-bgbtn"/>
                                    <button className="login100-form-btn" disabled={isInvalid} type="submit"  style={{backgroundColor:"#00797B"}} >
                                     Reset My Password
                                    </button>

                                    { error && <p>{error.message}</p> }
                                </div>
                            </div>
                            <div className="text-center p-t-10">
                                <span className="txt1">
                                    <p>
                                     Have an account?
                                     {' '}
                                     <Link to={routes.SIGN_IN}><b>Sign In</b></Link>
                                    </p>
                                </span>
                            </div>
                        </form>
                    </div>
                </div>
            </div>
    );
  }
}

const PasswordForgetLink = () =>
  <p>
    <Link to="/pw-forget">Forgot Password?</Link>
  </p>

export default PasswordForgetPage;

export {
  PasswordForgetForm,
  PasswordForgetLink,
};