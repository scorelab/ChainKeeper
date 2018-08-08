import React, { Component } from 'react';
import Navigation from './Navigation';

const MainPage = () =>
  <div>
       <Navigation/>
       <HomePage />
  </div>

class HomePage extends Component {

  render() {
    return (
      <div>
        <h1>Home</h1>
        <p>The Home Page is accessible by every signed in user.</p>
      </div>
    );
  }
}


export default MainPage;