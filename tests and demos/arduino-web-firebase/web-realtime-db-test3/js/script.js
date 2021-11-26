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
const $mode = document.querySelector(`.mode`);
const $ledContainers = document.querySelectorAll(`.led-container`);

const $sendButton = document.querySelector(`.send`);

let litLights = [[1, "6a0dad"], [23, "e9692c"], [80, "e9692c"] ]

const handleClickSend = (e) => {
    e.preventDefault();
    update(ref(db, $treeId.value ),{
        message: $message.value, 
        mode: $mode.value,
        lights: litLights
    })
    .then(()=>{
        console.log("update done")
    })
    .catch((error)=>{
        console.log(error)
    })
    
}

const addHTMLandCSS = () => {

//tree preview

    for (let i = 0; i < 15; i++) {
        const row =  `<div class="preview-row preview-row-${i}"></div>`
        document.querySelector(`.preview`).innerHTML += row;

        switch (i) {
            case 14:
                for (let f = 0; f < 34; f++) {
                    const col =  `<div class="led-container led-container-${f}">${f}</div>`
                    document.querySelector(`.preview-row-${i}`).innerHTML += col ;
                    }
                break;
            case 13:
                for (let f = 34; f < 66; f++) {
                        const col =  `<div class="led-container led-container-${f}">${f}</div>`
                        document.querySelector(`.preview-row-${i}`).innerHTML += col ;
                        document.querySelector(`.preview-row-${i}`).classList.add(`reversed`);
                        }
                break;
            case 12:
                   for (let f = 66; f < 96; f++) {
                        const col =  `<div class="led-container led-container-${f}">${f}</div>`
                        document.querySelector(`.preview-row-${i}`).innerHTML += col ;
                        }
                break;
            case 11:
                    for (let f = 96; f < 124; f++) {
                        const col =  `<div class="led-container led-container-${f}">${f}</div>`
                        document.querySelector(`.preview-row-${i}`).innerHTML += col ;
                        document.querySelector(`.preview-row-${i}`).classList.add(`reversed`);
                        }
                break;
            case 10:
                    for (let f = 124; f < 150; f++) {
                        const col =  `<div class="led-container led-container-${f}">${f}</div>`
                        document.querySelector(`.preview-row-${i}`).innerHTML += col ;
                        }
                break;
            case 9:
                   for (let f = 150; f < 174; f++) {
                        const col =  `<div class="led-container led-container-${f}">${f}</div>`
                        document.querySelector(`.preview-row-${i}`).innerHTML += col ;
                        document.querySelector(`.preview-row-${i}`).classList.add(`reversed`);
                        }
                break;
            case 8:
                   for (let f = 174; f < 196; f++) {
                        const col =  `<div class="led-container led-container-${f}">${f}</div>`
                        document.querySelector(`.preview-row-${i}`).innerHTML += col ;
                        }
                break;
             case 7:
                   for (let f = 196; f < 216; f++) {
                        const col =  `<div class="led-container led-container-${f}">${f}</div>`
                        document.querySelector(`.preview-row-${i}`).innerHTML += col ;
                        document.querySelector(`.preview-row-${i}`).classList.add(`reversed`);
                        }
                break;
            case 6:
                   for (let f = 216; f < 234; f++) {
                        const col =  `<div class="led-container led-container-${f}">${f}</div>`
                        document.querySelector(`.preview-row-${i}`).innerHTML += col ;
                        }
                break;
            case 5:
                   for (let f = 234; f < 250; f++) {
                        const col =  `<div class="led-container led-container-${f}">${f}</div>`
                        document.querySelector(`.preview-row-${i}`).innerHTML += col ;
                        document.querySelector(`.preview-row-${i}`).classList.add(`reversed`);
                        }
                break;
            case 4:
                   for (let f = 250; f < 264; f++) {
                        const col =  `<div class="led-container led-container-${f}">${f}</div>`
                        document.querySelector(`.preview-row-${i}`).innerHTML += col ;
                        }
                break;
            case 3:
                   for (let f = 264; f < 276; f++) {
                        const col =  `<div class="led-container led-container-${f}">${f}</div>`
                        document.querySelector(`.preview-row-${i}`).innerHTML += col ;
                        document.querySelector(`.preview-row-${i}`).classList.add(`reversed`);
                        }
                break;
            case 2:
                   for (let f = 276; f < 286; f++) {
                        const col =  `<div class="led-container led-container-${f}">${f}</div>`
                        document.querySelector(`.preview-row-${i}`).innerHTML += col ;
                        }
                break;
            case 1:
                   for (let f = 286; f < 294; f++) {
                        const col =  `<div class="led-container led-container-${f}">${f}</div>`
                        document.querySelector(`.preview-row-${i}`).innerHTML += col ;
                        document.querySelector(`.preview-row-${i}`).classList.add(`reversed`);
                        }
                break;
            case 0:
                for (let f = 294; f < 300; f++) {
                        const col =  `<div class="led-container led-container-${f}">${f}</div>`
                        document.querySelector(`.preview-row-${i}`).innerHTML += col ;
                        }
            }
            
    }


}

const lightUpPreview = () => {
        litLights.forEach((light)=>{
    console.log(light);
    document.querySelector(`.led-container-${light[0]}`).style.background = `#${light[1]}`;
        })
}

const handleHoverOverLed = (e) => {
    console.log(e.target.innerHTML);
}


const init = () =>{
    $sendButton.addEventListener('click', handleClickSend);
    //addHTMLandCSS();
    lightUpPreview();
    if ($ledContainers){
        $ledContainers.forEach((ledContainer)=>{
            ledContainer.addEventListener('mouseover', handleHoverOverLed)
        })
    }
}

init()
