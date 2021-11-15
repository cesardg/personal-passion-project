let mouseX = 0, mouseY = 0;
let xp = 0, yp = 0;

const init = () => {
    window.addEventListener('mousemove', handleMouseMove)
}

const handleMouseMove = (e) => {
    //document.querySelectorAll(`.icon`).forEach(element => element.style.backgroundColor = "red");
    mouseX = e.pageX - 30;
    mouseY = e.pageY - 30; 
    //console.log(mouseX, mouseY, window.innerHeight, window.innerWidth)
    let y = (window.innerHeight/2) - mouseY
    let x = mouseX - (window.innerWidth/2)
    console.log(x,y )
    let angle =  Math.atan2(y, x) * 180 / Math.PI;
    console.log(angle)
    document.querySelector(".arrow").style.transform = `rotate(${-angle}deg)`; 
    /*
    if (mouseX > (window.innerWidth/2) + 100){
        console.log('rechts')
        document.querySelectorAll(`.mid-right`).forEach(element => element.style.backgroundColor = "green");
    } else if (mouseX < (window.innerWidth/2) - 100){
        console.log('links')
        document.querySelectorAll(`.mid-left`).forEach(element => element.style.backgroundColor = "green");
    } else {
        document.querySelectorAll(`.mid-mid`).forEach(element => element.style.backgroundColor = "green");
        console.log('hor midden')
    }

    if (mouseY > (window.innerHeight/2) + 100){
        console.log('onder')
        document.querySelectorAll(`.back-mid`).forEach(element => element.style.backgroundColor = "green");
    } else if (mouseY < (window.innerHeight/2) - 100){
        console.log('boven')
          document.querySelectorAll(`.front-mid`).forEach(element => element.style.backgroundColor = "green");
    } else {
        console.log('ver midden')
          document.querySelectorAll(`.mid-mid`).forEach(element => element.style.backgroundColor = "green");
    }
    */
}


window.setInterval(function(){    
    xp += ((mouseX - xp)/6);
    yp += ((mouseY - yp)/6);
    document.querySelector(".circle").style.top = `${yp}px`
    document.querySelector(".circle").style.left = `${xp}px`
}, 20);

init ()