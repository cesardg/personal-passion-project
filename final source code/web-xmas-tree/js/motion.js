// based on code from The Coding Train / Daniel Shiffman

let video;
let poseNet;
let pose;
let skeleton;
let messageMode = "message"

const handleClickMode = (e) => {
    messageMode = e.target.value;
    setup();
}

function setup() {
    if (messageMode === "motion"){
        document.querySelector(`.p5Canvas`).style.display = "block";
        const myCanvas = createCanvas(600, 531);
        // 640 480
        canvas.width = 1200
        canvas.height = 960
        myCanvas.parent("canvasPlaceholder");
        video = createCapture(VIDEO);
        video.hide();
        poseNet = ml5.poseNet(video, modelLoaded);
        poseNet.on('pose', gotPoses);
    }
}

function gotPoses(poses) {
        if (messageMode === "motion"){
  //console.log(poses);
  if (poses.length > 0) {
    pose = poses[0].pose;
    skeleton = poses[0].skeleton;
  }
}
}

function modelLoaded() {
  console.log('poseNet ready');
}

function draw() {
        if (messageMode === "motion"){
  image(video, 0, 0);

  if (pose) {
    //let eyeR = pose.rightEye;
    //let eyeL = pose.leftEye;
    //let d = dist(eyeR.x, eyeR.y, eyeL.x, eyeL.y);
   // fill(255, 0, 0);
    //ellipse(pose.nose.x, pose.nose.y, d);
    fill(255, 0, 0);


    for (let i = 0; i < pose.keypoints.length; i++) {
      if (pose.keypoints[i].score > .6){
      let x = pose.keypoints[i].position.x;
      let y = pose.keypoints[i].position.y;
      fill(255, 0, 0);
      ellipse(x, y, 16, 16);
      }
    }
  }
}
}

const init = () => {
        // on change radio button menu
    document.querySelectorAll(`.message-modes`).forEach((mode)=> {
        mode.addEventListener("change", handleClickMode)
    })
}

init()
