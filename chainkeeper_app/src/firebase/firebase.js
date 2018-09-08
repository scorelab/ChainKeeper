import * as firebase  from 'firebase';

const config = {
    apiKey: "AIzaSyC4xmlISjKu-GeyrdrX8XUvJtGAXuYWxG4",
    authDomain: "chain-keeper.firebaseapp.com",
    databaseURL: "https://chain-keeper.firebaseio.com",
    projectId: "chain-keeper",
    storageBucket: "chain-keeper.appspot.com",
    messagingSenderId: "1001241399639"
};

if (!firebase.apps.length) {
  firebase.initializeApp(config);
}

const auth = firebase.auth();
const googleProvider = new firebase.auth.GoogleAuthProvider();

export default firebase;
const db = firebase.database();
export {
  auth,
  googleProvider,
  db,
};