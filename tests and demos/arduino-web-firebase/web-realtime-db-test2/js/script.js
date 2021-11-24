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

let $name= document.querySelector(`.name`);
let $roll = document.querySelector(`.roll`);
let $sec = document.querySelector(`.sec`);
let $gen = document.querySelector(`.gen`);
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

const selectData = (e) => {
    e.preventDefault();
    const dbRef = ref(db);
    get(child(dbRef, "TheStudents/" + $roll.value)).then((snapshot)=>{
        if (snapshot.exists()){
            $name.value = snapshot.val().Name;
            $sec.value = snapshot.val().Section;
            $gen.value = snapshot.val().Gender;
        } else{
            console.log("no data found")
        }
    })
    .catch((error)=>{
        console.log(error)
    })
}

const updateData = (e) => {
    e.preventDefault();
    update(ref(db, "TheStudents/"+ $roll.value),{
        Name: $name.value,
        Section: $sec.value,
        Gender: $gen.value

    })
    .then(()=>{
        console.log("update done")
    })
    .catch((error)=>{
        console.log(error)
    })
}

const deleteData = (e) => {
    e.preventDefault();
    remove(ref(db, "TheStudents/"+ $roll.value))
    .then(()=>{
        console.log("remove done")
    })
    .catch((error)=>{
        console.log(error)
    })
}



const init = () =>{
    $insBtn.addEventListener('click', insertData);
    $selBtn.addEventListener('click', selectData);
    $updBtn.addEventListener('click', updateData);
    $delBtn.addEventListener('click', deleteData);
}

init()
