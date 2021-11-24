    // Import the functions you need from the SDKs you need
    import { initializeApp } from "https://www.gstatic.com/firebasejs/9.1.0/firebase-app.js";
    // TODO: Add SDKs for Firebase products that you want to use
    // https://firebase.google.com/docs/web/setup#available-libraries

    // Your web app's Firebase configuration
    const firebaseConfig = {
        apiKey: "AIzaSyAdfE9rKt59I0J-qVrvDnOsJAx0-xp1dMI",
        authDomain: "arduino-wi-fi-xmas-tree-db.firebaseapp.com",
        databaseURL: "https://arduino-wi-fi-xmas-tree-db-default-rtdb.europe-west1.firebasedatabase.app",
        projectId: "arduino-wi-fi-xmas-tree-db",
        storageBucket: "arduino-wi-fi-xmas-tree-db.appspot.com",
        messagingSenderId: "838895049591",
        appId: "1:838895049591:web:6e11c76081c8d1d9f05f72"
    };

    // Initialize Firebase
    const app = initializeApp(firebaseConfig);

    import {getDatabase, ref, set, child, update, remove} from "https://www.gstatic.com/firebasejs/9.1.0/firebase-database.js";

    const db = getDatabase();

    const $name= document.querySelector(`.name`);
    const $roll = document.querySelector(`.roll`);
    const $sec = document.querySelector(`.sec`);
    const $gen = document.querySelector(`.gen`);

    const $insBtn = document.querySelector(`.insert`);
    const $selBtn = document.querySelector(`.select`);
    const $updBtn = document.querySelector(`.update`);
    const $delBtn = document.querySelector(`.delete`);

    // insert data
    const insertData = (e) => {
        e.preventDefault();
        set(ref(db, "TheStudents/"+ $roll.value),{
            Name: $name.value,
            Roll: $roll.value,
            Section: $sec.value,
            Gender: $gen.value

        })
        .then(()=>{
            console.log("set done")
        })
        .catch((error)=>{
            console.log(error)
        })
    }

    $insBtn.addEventListener('click', insertData);
