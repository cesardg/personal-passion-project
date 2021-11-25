import { initializeApp } from "https://www.gstatic.com/firebasejs/9.1.0/firebase-app.js";
import {getDatabase, ref, get, set, child, update, remove} from "https://www.gstatic.com/firebasejs/9.1.0/firebase-database.js";

const firebaseConfig = {
    apiKey: "AIzaSyAdfE9rKt59I0J-qVrvDnOsJAx0-xp1dMI",
    authDomain: "arduino-wi-fi-xmas-tree-db.firebaseapp.com",
    databaseURL: "https://arduino-wi-fi-xmas-tree-db-default-rtdb.europe-west1.firebasedatabase.app",
    projectId: "arduino-wi-fi-xmas-tree-db",
    storageBucket: "arduino-wi-fi-xmas-tree-db.appspot.com",
    messagingSenderId: "838895049591",
    appId: "1:838895049591:web:6e11c76081c8d1d9f05f72"
};

const app = initializeApp(firebaseConfig);
const db = getDatabase();

const $treeId= document.querySelector(`.tree-id`);
const $message = document.querySelector(`.message`);

const $sendButton = document.querySelector(`.send`);

const handleClickSend = (e) => {
    e.preventDefault();
    update(ref(db, $treeId.value + "/messages"),{
        message: $message.value  
    })
    .then(()=>{
        console.log("update done")
        $message.value = "";
        document.querySelector(`.container`).innerHTML = `<h1 class="title">Your message has been successfully sent!</h1>`
    })
    .catch((error)=>{
        console.log(error)
    })
}


const init = () =>{
    $sendButton.addEventListener('click', handleClickSend);
}

init()
