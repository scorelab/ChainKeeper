import React from 'react';

import { auth } from '../firebase';

const SignOutButton = () =>
  <button
    type="button"
    onClick={auth.doSignOut}
    style={{backgroundColor:'transparent'}}
  >
    Sign Out
  </button>

export default SignOutButton;