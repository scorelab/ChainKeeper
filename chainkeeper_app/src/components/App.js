import React, { Component } from 'react';
import { BrowserRouter as Router,Route, } from 'react-router-dom';
import './App.css';

import * as routes from '../constants/routes';
import Setup from './Setup';

const App = () =>
  <Router>
    <div>
      <Route
        exact path={routes.LANDING}
        component={() => <Setup />}
      />
    </div>
  </Router>

export default App;
