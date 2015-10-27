//Start socket io connection to node
var socket = io();


//Controller mode
var mode = 0;
var modeSelect = function(m){
  mode = m;
  tiltX = 50;
  key = 50;
}



//Handle key presses
var key = 50;
var KeyShoot = 0; 
var increment = 0;

var shoot = function(s){
  KeyShoot = s;
}

var arrow = function(k){
  if (key + k <= 100 && key + k >= 0){
    key += k;
  }
}

var setIncrement = function(i){
  increment = i;
}

//increment key every 20 ms
window.setInterval(function(){
  arrow(increment);
}, 20);


//function to check when key is pressed: 
//Handel keyboard presses
document.onkeydown = checkKey;
function checkKey(e) {

    e = e || window.event;

    if (e.keyCode == '38') {
      // up arrow
      shoot(1);
    }
    else if (e.keyCode == '40') {
      // down arrow
      shoot(1);
    }
    else if (e.keyCode == '37') {
      // left arrow
      arrow(-1);
    }
    else if (e.keyCode == '39') {
      // right arrow
      arrow(1);
    }
}

document.onkeyup = unCheckKey;
function unCheckKey() {
  shoot(0);
}




//Handle arrow presses on screen
window.addEventListener('load', function(){
 
    var upArrow = document.getElementById('upArrow')
    var leftArrow = document.getElementById('leftArrow')
    var rightArrow = document.getElementById('rightArrow')

    //Handle touch 
    upArrow.addEventListener('touchstart', function(e){
      shoot(1);
      e.preventDefault(); // Prevent long press (left mouse butten press) box
    }, false)

    leftArrow.addEventListener('touchstart', function(e){
      increment = -1;
      e.preventDefault();
    }, false)

    rightArrow.addEventListener('touchstart', function(e){
      increment = 1;
      e.preventDefault();
    }, false)

    //Handle touch release
    upArrow.addEventListener('touchend', function(e){
      shoot(0);
      e.preventDefault();
    }, false)

    leftArrow.addEventListener('touchend', function(e){
      increment = 0;
      e.preventDefault();
    }, false)

    rightArrow.addEventListener('touchend', function(e){
      increment = 0;
      e.preventDefault();
    }, false)
 
}, false)




//Handle device orientation
var tiltX = 0;
var tiltY = 0;
function tilt(a){
  tiltX = Math.round(a[0]) + 50;
  if(tiltX > 100){
    tiltX = 100;
  }
  if (tiltX < 0){
    tiltX = 0;
  }
  tiltY = (Math.abs(Math.round(a[1])) < 30)? 1 : 0;
  //tiltY = Math.round(a[1]);
}


if (window.DeviceOrientationEvent) {
    window.addEventListener("deviceorientation", function () {
        tilt([event.beta, event.gamma]);
    }, true);
} else if (window.DeviceMotionEvent) {
    window.addEventListener('devicemotion', function () {
        tilt([event.acceleration.x * 2, event.acceleration.y * 2]);
    }, true);
} else {
    window.addEventListener("MozOrientation", function () {
        tilt([orientation.x * 50, orientation.y * 50]);
    }, true);
}


//Send controll input to node.js
var sendControlls = function(){
  switch(mode){
    case 0:
      socket.emit('controll', [key, KeyShoot]);
      break;
    case 1:
      socket.emit('controll', [tiltX, tiltY]);
      break;
  }
}


//call sendControll function at set time intervalls

window.setInterval(function(){
  sendControlls();
}, 100);
