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

const $treeCode= document.querySelector(`.tree-code`);
const $message = document.querySelector(`.message`);
const $mode = document.querySelector(`.mode`);
const $ledContainers = document.querySelectorAll(`.led-container`);
const $sendButton = document.querySelector(`.send`);

let url = window.location.href;
let params = (new URL(url)).searchParams;

//mapping
const A = [242, 241, 224, 225, 226, 227, 228, 202, 203, 240, 243, 223, 221, 222, 207, 208, 209, 210, 211, 179, 180, 181, 165, 166, 167, 131, 132, 133, 134, 164, 163, 135, 136, 162, 161, 160, 159, 158, 157, 156, 190, 200, 201, 204, 188, 189, 141, 142, 140, 139, 138, 137, 106, 104, 105, 85, 86, 113, 114, 115, 75, 76, 77, 53, 54, 55, 84, 46, 45, 44];
const Acol = [[242,"e9692c"],[241,"e9692c"],[240,"e9692c"],[243,"e9692c"],[224,"e9692c"],[225,"e9692c"],[226,"e9692c"],[227,"e9692c"],[203,"e9692c"],[204,"e9692c"],[202,"e9692c"],[201,"e9692c"],[200,"e9692c"],[228,"e9692c"],[223,"e9692c"],[222,"e9692c"],[221,"e9692c"],[208,"e9692c"],[207,"e9692c"],[209,"e9692c"],[179,"e9692c"],[180,"e9692c"],[181,"e9692c"],[165,"e9692c"],[166,"e9692c"],[167,"e9692c"],[131,"e9692c"],[132,"e9692c"],[133,"e9692c"],[134,"e9692c"],[135,"e9692c"],[136,"e9692c"],[137,"e9692c"],[138,"e9692c"],[139,"e9692c"],[159,"e9692c"],[160,"e9692c"],[161,"e9692c"],[162,"e9692c"],[163,"e9692c"],[164,"e9692c"],[210,"e9692c"],[211,"e9692c"],[188,"e9692c"],[189,"e9692c"],[190,"e9692c"],[156,"e9692c"],[157,"e9692c"],[158,"e9692c"],[140,"e9692c"],[141,"e9692c"],[142,"e9692c"],[104,"e9692c"],[105,"e9692c"],[106,"e9692c"],[84,"e9692c"],[85,"e9692c"],[86,"e9692c"],[44,"e9692c"],[45,"e9692c"],[46,"e9692c"],[53,"e9692c"],[54,"e9692c"],[55,"e9692c"],[75,"e9692c"],[76,"e9692c"],[77,"e9692c"],[113,"e9692c"],[114,"e9692c"],[115,"e9692c"]]

const B = [246, 220, 221, 245, 244, 243, 223, 222, 224, 242, 241, 225, 226, 227, 240, 239, 238, 237, 228, 229, 230, 231, 199, 200, 201, 189, 190, 156, 157, 158, 159, 160, 161, 162, 163, 164, 165, 181, 209, 210, 180, 182, 208, 183, 184, 185, 186, 187, 188, 143, 142, 141, 105, 104, 103, 87, 86, 85, 45, 84, 46, 83, 47, 48, 82, 166, 132, 133, 134, 112, 113, 114, 76, 77, 78, 79, 80, 81, 49, 50, 51, 52, 53, 54]
const Bcol = [[246, "e9692c"],[220, "e9692c"],[221, "e9692c"],[245, "e9692c"],[244, "e9692c"],[243, "e9692c"],[223, "e9692c"],[222, "e9692c"],[224, "e9692c"],[242, "e9692c"],[241, "e9692c"],[225, "e9692c"],[226, "e9692c"],[227, "e9692c"],[240, "e9692c"],[239, "e9692c"],[238, "e9692c"],[237, "e9692c"],[228, "e9692c"],[229, "e9692c"],[230, "e9692c"],[231, "e9692c"],[199, "e9692c"],[200, "e9692c"],[201, "e9692c"],[189, "e9692c"],[190, "e9692c"],[191, "e9692c"],[155, "e9692c"],[156, "e9692c"],[157, "e9692c"],[158, "e9692c"],[159, "e9692c"],[160, "e9692c"],[161, "e9692c"],[162, "e9692c"],[163, "e9692c"],[164, "e9692c"],[165, "e9692c"],[181, "e9692c"],[209, "e9692c"],[210, "e9692c"],[180, "e9692c"],[182, "e9692c"],[208, "e9692c"],[183, "e9692c"],[184, "e9692c"],[185, "e9692c"],[186, "e9692c"],[187, "e9692c"],[188, "e9692c"],[143, "e9692c"],[142, "e9692c"],[141, "e9692c"],[105, "e9692c"],[104, "e9692c"],[103, "e9692c"],[87, "e9692c"],[86, "e9692c"],[85, "e9692c"],[45, "e9692c"],[84, "e9692c"],[46, "e9692c"],[83, "e9692c"],[47, "e9692c"],[48, "e9692c"],[82, "e9692c"],[166, "e9692c"],[132, "e9692c"],[133, "e9692c"],[134, "e9692c"],[112, "e9692c"],[113, "e9692c"],[114, "e9692c"],[76, "e9692c"],[77, "e9692c"],[78, "e9692c"],[79, "e9692c"],[80, "e9692c"],[81, "e9692c"],[49, "e9692c"],[50, "e9692c"],[51, "e9692c"],[52, "e9692c"],[53, "e9692c"],[54, "e9692c"]]

const C = [[238, 239, 227, 228, 229, 230, 200, 201, 202, 240, 241, 242, 243, 244, 222, 223, 224, 225, 226, 221, 220, 219, 211, 210, 209, 181, 180, 179, 167, 166, 165, 133, 132, 131, 115, 114, 113, 77, 76, 75, 78, 79, 80, 81, 82, 83, 84, 85, 86, 104, 105, 106, 46, 47, 48, 49, 50, 51, 52, 53]]
const Ccol = [[238, "e9692c"],[239, "e9692c"],[227, "e9692c"],[228, "e9692c"],[229, "e9692c"],[230, "e9692c"],[200, "e9692c"],[201, "e9692c"],[202, "e9692c"],[240, "e9692c"],[241, "e9692c"],[242, "e9692c"],[243, "e9692c"],[244, "e9692c"],[222, "e9692c"],[223, "e9692c"],[224, "e9692c"],[225, "e9692c"],[226, "e9692c"],[221, "e9692c"],[220, "e9692c"],[219, "e9692c"],[211, "e9692c"],[210, "e9692c"],[209, "e9692c"],[181, "e9692c"],[180, "e9692c"],[179, "e9692c"],[167, "e9692c"],[166, "e9692c"],[165, "e9692c"],[133, "e9692c"],[132, "e9692c"],[131, "e9692c"],[115, "e9692c"],[114, "e9692c"],[113, "e9692c"],[77, "e9692c"],[76, "e9692c"],[75, "e9692c"],[78, "e9692c"],[79, "e9692c"],[80, "e9692c"],[81, "e9692c"],[82, "e9692c"],[83, "e9692c"],[84, "e9692c"],[85, "e9692c"],[86, "e9692c"],[104, "e9692c"],[105, "e9692c"],[106, "e9692c"],[46, "e9692c"],[47, "e9692c"],[48, "e9692c"],[49, "e9692c"],[50, "e9692c"],[51, "e9692c"],[52, "e9692c"],[53, "e9692c"]]

const D = [[246, 245, 244, 243, 242, 241, 240, 239, 238, 228, 229, 227, 226, 225, 224, 223, 222, 221, 220, 210, 209, 208, 182, 181, 180, 166, 165, 164, 134, 133, 132, 114, 113, 112, 78, 77, 76, 54, 53, 52, 51, 79, 80, 81, 82, 49, 50, 48, 47, 83, 46, 84, 85, 86, 230, 231, 199, 200, 201, 189, 190, 191, 155, 156, 157, 141, 142, 143, 103, 104, 105]]
const Dcol = [[246, "e9692c"],[245, "e9692c"],[244, "e9692c"],[243, "e9692c"],[242, "e9692c"],[241, "e9692c"],[240, "e9692c"],[239, "e9692c"],[238, "e9692c"],[228, "e9692c"],[229, "e9692c"],[227, "e9692c"],[226, "e9692c"],[225, "e9692c"],[224, "e9692c"],[223, "e9692c"],[222, "e9692c"],[221, "e9692c"],[220, "e9692c"],[210, "e9692c"],[209, "e9692c"],[208, "e9692c"],[182, "e9692c"],[181, "e9692c"],[180, "e9692c"],[166, "e9692c"],[165, "e9692c"],[164, "e9692c"],[134, "e9692c"],[133, "e9692c"],[132, "e9692c"],[114, "e9692c"],[113, "e9692c"],[112, "e9692c"],[78, "e9692c"],[77, "e9692c"],[76, "e9692c"],[54, "e9692c"],[53, "e9692c"],[52, "e9692c"],[51, "e9692c"],[79, "e9692c"],[80, "e9692c"],[81, "e9692c"],[82, "e9692c"],[49, "e9692c"],[50, "e9692c"],[48, "e9692c"],[47, "e9692c"],[83, "e9692c"],[46, "e9692c"],[84, "e9692c"],[85, "e9692c"],[86, "e9692c"],[230, "e9692c"],[231, "e9692c"],[199, "e9692c"],[200, "e9692c"],[201, "e9692c"],[189, "e9692c"],[190, "e9692c"],[191, "e9692c"],[155, "e9692c"],[156, "e9692c"],[157, "e9692c"],[141, "e9692c"],[142, "e9692c"],[143, "e9692c"],[103, "e9692c"],[104, "e9692c"],[105, "e9692c"]]

const E = [236, 237, 238, 239, 240, 241, 242, 243, 244, 245, 246, 247, 219, 220, 221, 222, 223, 224, 225, 226, 227, 228, 229, 230, 211, 210, 209, 179, 180, 181, 167, 166, 165, 164, 163, 162, 161, 160, 159, 131, 132, 133, 115, 114, 113, 75, 76, 77, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44, 78, 79, 80, 81, 82, 83, 84, 85, 86, 182, 183, 184, 185, 186, 187, 188, 158]
const Ecol = [[236, "e9692c"],[237, "e9692c"],[238, "e9692c"],[239, "e9692c"],[240, "e9692c"],[241, "e9692c"],[242, "e9692c"],[243, "e9692c"],[244, "e9692c"],[245, "e9692c"],[246, "e9692c"],[247, "e9692c"],[219, "e9692c"],[220, "e9692c"],[221, "e9692c"],[222, "e9692c"],[223, "e9692c"],[224, "e9692c"],[225, "e9692c"],[226, "e9692c"],[227, "e9692c"],[228, "e9692c"],[229, "e9692c"],[230, "e9692c"],[211, "e9692c"],[210, "e9692c"],[209, "e9692c"],[179, "e9692c"],[180, "e9692c"],[181, "e9692c"],[167, "e9692c"],[166, "e9692c"],[165, "e9692c"],[164, "e9692c"],[163, "e9692c"],[162, "e9692c"],[161, "e9692c"],[160, "e9692c"],[159, "e9692c"],[131, "e9692c"],[132, "e9692c"],[133, "e9692c"],[134, "e9692c"],[135, "e9692c"],[136, "e9692c"],[115, "e9692c"],[114, "e9692c"],[113, "e9692c"],[75, "e9692c"],[76, "e9692c"],[77, "e9692c"],[55, "e9692c"],[54, "e9692c"],[53, "e9692c"],[52, "e9692c"],[51, "e9692c"],[50, "e9692c"],[49, "e9692c"],[48, "e9692c"],[47, "e9692c"],[46, "e9692c"],[45, "e9692c"],[44, "e9692c"],[78, "e9692c"],[79, "e9692c"],[80, "e9692c"],[81, "e9692c"],[82, "e9692c"],[83, "e9692c"],[84, "e9692c"],[85, "e9692c"],[86, "e9692c"],[182, "e9692c"],[183, "e9692c"],[184, "e9692c"],[185, "e9692c"],[186, "e9692c"],[187, "e9692c"],[188, "e9692c"],[158, "e9692c"]];

const F = [247, 246, 245, 244, 243, 242, 241, 240, 239, 238, 237, 236, 219, 220, 221, 222, 223, 224, 225, 226, 227, 228, 229, 230, 211, 210, 209, 179, 180, 181, 182, 183, 184, 185, 186, 187, 167, 166, 165, 164, 163, 162, 161, 160, 159, 131, 132, 133, 115, 114, 113, 75, 76, 77, 55, 54, 53]
const Fcol = [[247, "e9692c"],[246, "e9692c"],[245, "e9692c"],[244, "e9692c"],[243, "e9692c"],[242, "e9692c"],[241, "e9692c"],[240, "e9692c"],[239, "e9692c"],[238, "e9692c"],[237, "e9692c"],[236, "e9692c"],[219, "e9692c"],[220, "e9692c"],[221, "e9692c"],[222, "e9692c"],[223, "e9692c"],[224, "e9692c"],[225, "e9692c"],[226, "e9692c"],[227, "e9692c"],[228, "e9692c"],[229, "e9692c"],[230, "e9692c"],[211, "e9692c"],[210, "e9692c"],[209, "e9692c"],[179, "e9692c"],[180, "e9692c"],[181, "e9692c"],[182, "e9692c"],[183, "e9692c"],[184, "e9692c"],[185, "e9692c"],[186, "e9692c"],[187, "e9692c"],[167, "e9692c"],[166, "e9692c"],[165, "e9692c"],[164, "e9692c"],[163, "e9692c"],[162, "e9692c"],[161, "e9692c"],[160, "e9692c"],[159, "e9692c"],[131, "e9692c"],[132, "e9692c"],[133, "e9692c"],[115, "e9692c"],[114, "e9692c"],[113, "e9692c"],[75, "e9692c"],[76, "e9692c"],[77, "e9692c"],[55, "e9692c"],[54, "e9692c"],[53, "e9692c"]]

const G = [245, 244, 243, 242, 241, 240, 239, 219, 220, 221, 222, 223, 224, 225, 226, 227, 228, 229, 211, 210, 209, 203, 202, 201, 179, 180, 181, 167, 166, 165, 162, 161, 160, 159, 158, 157, 131, 132, 133, 136, 137, 138, 139, 140, 141, 115, 114, 113, 107, 106, 105, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 53, 52, 51, 50, 49, 48, 47]
const Gcol = [[245, "e9692c"],[244, "e9692c"],[243, "e9692c"],[242, "e9692c"],[241, "e9692c"],[240, "e9692c"],[239, "e9692c"],[219, "e9692c"],[220, "e9692c"],[221, "e9692c"],[222, "e9692c"],[223, "e9692c"],[224, "e9692c"],[225, "e9692c"],[226, "e9692c"],[227, "e9692c"],[228, "e9692c"],[229, "e9692c"],[211, "e9692c"],[210, "e9692c"],[209, "e9692c"],[203, "e9692c"],[202, "e9692c"],[201, "e9692c"],[179, "e9692c"],[180, "e9692c"],[181, "e9692c"],[167, "e9692c"],[166, "e9692c"],[165, "e9692c"],[162, "e9692c"],[161, "e9692c"],[160, "e9692c"],[159, "e9692c"],[158, "e9692c"],[157, "e9692c"],[131, "e9692c"],[132, "e9692c"],[133, "e9692c"],[136, "e9692c"],[137, "e9692c"],[138, "e9692c"],[139, "e9692c"],[140, "e9692c"],[141, "e9692c"],[115, "e9692c"],[114, "e9692c"],[113, "e9692c"],[107, "e9692c"],[106, "e9692c"],[105, "e9692c"],[75, "e9692c"],[76, "e9692c"],[77, "e9692c"],[78, "e9692c"],[79, "e9692c"],[80, "e9692c"],[81, "e9692c"],[82, "e9692c"],[83, "e9692c"],[84, "e9692c"],[85, "e9692c"],[53, "e9692c"],[52, "e9692c"],[51, "e9692c"],[50, "e9692c"],[49, "e9692c"],[48, "e9692c"],[47, "e9692c"]]

const H = [[247, 246, 245, 238, 237, 236, 219, 220, 221, 228, 229, 230, 211, 210, 209, 202, 201, 200, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 167, 166, 165, 164, 163, 162, 161, 160, 159, 158, 157, 156, 140, 141, 142, 106, 105, 104, 84, 85, 86, 46, 45, 44, 131, 132, 133, 115, 114, 113, 75, 76, 77, 55, 54, 53]]
const Hcol = [[247, "e9692c"],[246, "e9692c"],[245, "e9692c"],[238, "e9692c"],[237, "e9692c"],[236, "e9692c"],[219, "e9692c"],[220, "e9692c"],[221, "e9692c"],[228, "e9692c"],[229, "e9692c"],[230, "e9692c"],[211, "e9692c"],[210, "e9692c"],[209, "e9692c"],[202, "e9692c"],[201, "e9692c"],[200, "e9692c"],[179, "e9692c"],[180, "e9692c"],[181, "e9692c"],[182, "e9692c"],[183, "e9692c"],[184, "e9692c"],[185, "e9692c"],[186, "e9692c"],[187, "e9692c"],[188, "e9692c"],[189, "e9692c"],[190, "e9692c"],[167, "e9692c"],[166, "e9692c"],[165, "e9692c"],[164, "e9692c"],[163, "e9692c"],[162, "e9692c"],[161, "e9692c"],[160, "e9692c"],[159, "e9692c"],[158, "e9692c"],[157, "e9692c"],[156, "e9692c"],[140, "e9692c"],[141, "e9692c"],[142, "e9692c"],[106, "e9692c"],[105, "e9692c"],[104, "e9692c"],[84, "e9692c"],[85, "e9692c"],[86, "e9692c"],[46, "e9692c"],[45, "e9692c"],[44, "e9692c"],[131, "e9692c"],[132, "e9692c"],[133, "e9692c"],[115, "e9692c"],[114, "e9692c"],[113, "e9692c"],[75, "e9692c"],[76, "e9692c"],[77, "e9692c"],[55, "e9692c"],[54, "e9692c"],[53, "e9692c"]] 

const I = [247, 246, 245, 244, 243, 242, 241, 240, 239, 238, 237, 236, 219, 220, 221, 222, 223, 224, 225, 226, 227, 228, 229, 230, 206, 205, 204, 184, 185, 186, 162, 161, 160, 136, 137, 138, 110, 109, 108, 80, 81, 82, 54, 53, 52, 75, 55, 76, 77, 78, 79, 51, 50, 49, 48, 83, 84, 85, 86, 47, 46, 45, 44]
const Icol = [[247, "e9692c"],[246, "e9692c"],[245, "e9692c"],[244, "e9692c"],[243, "e9692c"],[242, "e9692c"],[241, "e9692c"],[240, "e9692c"],[239, "e9692c"],[238, "e9692c"],[237, "e9692c"],[236, "e9692c"],[219, "e9692c"],[220, "e9692c"],[221, "e9692c"],[222, "e9692c"],[223, "e9692c"],[224, "e9692c"],[225, "e9692c"],[226, "e9692c"],[227, "e9692c"],[228, "e9692c"],[229, "e9692c"],[230, "e9692c"],[206, "e9692c"],[205, "e9692c"],[204, "e9692c"],[184, "e9692c"],[185, "e9692c"],[186, "e9692c"],[162, "e9692c"],[161, "e9692c"],[160, "e9692c"],[136, "e9692c"],[137, "e9692c"],[138, "e9692c"],[110, "e9692c"],[109, "e9692c"],[108, "e9692c"],[80, "e9692c"],[81, "e9692c"],[82, "e9692c"],[54, "e9692c"],[53, "e9692c"],[52, "e9692c"],[75, "e9692c"],[55, "e9692c"],[76, "e9692c"],[77, "e9692c"],[78, "e9692c"],[79, "e9692c"],[51, "e9692c"],[50, "e9692c"],[49, "e9692c"],[48, "e9692c"],[83, "e9692c"],[84, "e9692c"],[85, "e9692c"],[86, "e9692c"],[47, "e9692c"],[46, "e9692c"],[45, "e9692c"],[44, "e9692c"]]

const J = [239, 238, 237, 227, 228, 229, 203, 202, 201, 187, 188, 189, 159, 158, 157, 139, 140, 141, 107, 106, 105, 83, 130, 131, 132, 116, 115, 114, 74, 75, 76, 77, 78, 79, 80, 81, 82, 84, 85, 53, 52, 51, 50, 49, 48]
const Jcol = [[239, "e9692c"],[238, "e9692c"],[237, "e9692c"],[227, "e9692c"],[228, "e9692c"],[229, "e9692c"],[203, "e9692c"],[202, "e9692c"],[201, "e9692c"],[187, "e9692c"],[188, "e9692c"],[189, "e9692c"],[159, "e9692c"],[158, "e9692c"],[157, "e9692c"],[139, "e9692c"],[140, "e9692c"],[141, "e9692c"],[107, "e9692c"],[106, "e9692c"],[105, "e9692c"],[83, "e9692c"],[130, "e9692c"],[131, "e9692c"],[132, "e9692c"],[116, "e9692c"],[115, "e9692c"],[114, "e9692c"],[74, "e9692c"],[75, "e9692c"],[76, "e9692c"],[77, "e9692c"],[78, "e9692c"],[79, "e9692c"],[80, "e9692c"],[81, "e9692c"],[82, "e9692c"],[84, "e9692c"],[85, "e9692c"],[53, "e9692c"],[52, "e9692c"],[51, "e9692c"],[50, "e9692c"],[49, "e9692c"],[48, "e9692c"]];
//end mapping

let litLights = [];
let litLightsOnlyIndex = [];



const handleClickSend = (e) => {
    e.preventDefault();
    update(ref(db, params.get('tree-id') ),{
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
        document.querySelector(`.led-container-${light[0]}`).style.background = `#${light[1]}`;
    })
}

const handleHoverOverLed = (e) => {

    const ledNumber = Number(e.currentTarget.innerHTML);
  
    if (litLightsOnlyIndex.includes(ledNumber)){


        if (litLightsOnlyIndex.indexOf(ledNumber) > -1) {
        litLightsOnlyIndex.splice(litLightsOnlyIndex.indexOf(ledNumber), 1);
        }

          if (litLights.indexOf(ledNumber) > -1) {
        litLights.splice(litLights.indexOf(ledNumber), 1);
        }

         document.querySelector(`.led-container-${ledNumber}`).style.background = `#ffffff`;

    } else {
        litLights.push([ledNumber, "e9692c"])
        document.querySelector(`.led-container-${ledNumber}`).style.background = `#e9692c`;
        litLightsOnlyIndex.push(ledNumber);
    }
      

      console.log(litLightsOnlyIndex);
      console.log(litLights);

    let copyString;

    litLights.forEach((e) => {
        if (e){
        copyString += `[${e[0]}, "${e[1]}"],`
        }
    })
      document.querySelector(`.copy-array`).innerHTML = `[${copyString}]`
}



const init = () =>{
    $sendButton.addEventListener('click', handleClickSend);
    //addHTMLandCSS();
    lightUpPreview();
    if ($ledContainers){
        $ledContainers.forEach((ledContainer)=>{
            ledContainer.addEventListener('mousedown', handleHoverOverLed)
        })
    }
}

init()
