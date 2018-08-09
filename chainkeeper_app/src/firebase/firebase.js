import * as firebase  from 'firebase';

const config = {
    apiKey: "AIzaSyANEGBNvsMQuCXp7eWZYVcqD_JTFyx8IpY",
    authDomain: "chain-kleaner.firebaseapp.com",
    databaseURL: "https://chain-kleaner.firebaseio.com",
    projectId: "chain-kleaner",
    storageBucket: "chain-kleaner.appspot.com",
    messagingSenderId: "967778545944"
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