//Start socket io connection to node
var socket = io();


//Controller mode
var mode = 0;
var modeSelect = function(m){
  mode = m;
}



//Handle key presses
//function to check when key is pressed: 
var key = 'NONE';
document.onkeydown = checkKey;
function checkKey(e) {

    e = e || window.event;

    if (e.keyCode == '38') {
      // up arrow
      key = 'UP';
    }
    else if (e.keyCode == '40') {
      // down arrow
      key = 'DOWN';
    }
    else if (e.keyCode == '37') {
      // left arrow
      key = 'LEFT';
    }
    else if (e.keyCode == '39') {
      // right arrow
      key = 'RIGHT';
    }
}

document.onkeyup = unCheckKey;
function unCheckKey() {
  key = 'NONE'
}


//Handle arrow presses on screen
window.addEventListener('load', function(){
 
    var upArrow = document.getElementById('upArrow')
    var leftArrow = document.getElementById('leftArrow')
    var rightArrow = document.getElementById('rightArrow')

    //Handle touch 
    upArrow.addEventListener('touchstart', function(e){
      arrow('UP'); //Register command
      e.preventDefault(); // Prevent long press (left mouse butten press) box
    }, false)

    leftArrow.addEventListener('touchstart', function(e){
      arrow('LEFT');
      e.preventDefault();
    }, false)

    rightArrow.addEventListener('touchstart', function(e){
      arrow('RIGHT');
      e.preventDefault();
    }, false)

    //Handle touch release
    upArrow.addEventListener('touchend', function(e){
      arrow('NONE');
      e.preventDefault();
    }, false)

    leftArrow.addEventListener('touchend', function(e){
      arrow('NONE');
      e.preventDefault();
    }, false)

    rightArrow.addEventListener('touchend', function(e){
      arrow('NONE');
      e.preventDefault();
    }, false)
 
}, false)

var arrow = function(k){
  key = k;
}



//Handle device orientation
var orX = 0;
var orY = 0;
function tilt(a){
  orX = Math.round(a[0]);
  orY = Math.round(a[1]);
  //socket.emit('controll', a);
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
  socket.emit('controll', [mode, key, orX, orY]);
}


//call sendControll function at set time intervalls

window.setInterval(function(){
  sendControlls();
}, 100);