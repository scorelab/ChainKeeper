import React, { Component } from 'react';
import { withRouter } from 'react-router-dom';
import { auth } from '../firebase';
import * as routes from "../constants/routes";

const GoogleSignInPage = ({ history }) =>
  <div>
    <LoginwithGoogle history={history} />
  </div>

const byPropKey = (propertyName, value) => () => ({
  [propertyName]: value,
});


const INITIAL_STATE = {
  email: '',
  error: null,
};

class LoginwithGoogle extends Component {
    constructor(props) {
        super(props);
        this.state = { ...INITIAL_STATE };
    }

    render () {
        const {
            history,
         } = this.props;

        const imageClick = () => {
           auth.loginWithGoogle()
              .then((result) => {
                  const user = result.user;
                  this.setState({
                    user
                  });
                  console.log(user.email);
                  history.push(routes.HOME);
              })
              .catch(error => {
                this.setState(byPropKey('error', error));
              });
        };
        return (
           <div>
              <img className="google_login" src={require('../public/gmail_login.png')} style={{width:"200px"}} onClick={() => imageClick()} />
           </div>
        );
     }

}


export default withRouter(GoogleSignInPage);
