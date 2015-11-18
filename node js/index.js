//Set up express server
var express = require("express");
var app = express();
var http = require('http').Server(app);
//Allow path to static scripts, styles and images
app.use("/styles", express.static(__dirname +'/www/styles'));
app.use("/scripts", express.static(__dirname + '/www/scripts'));
app.use("/images", express.static(__dirname + '/www/images'));

//Set up socket.io
var io = require('socket.io')(http);

//Set up serial communication
var serialport = require("serialport");
var SerialPort = serialport.SerialPort; // localize object constructor

var sp = new SerialPort("COM13", {
  parser: serialport.parsers.readline("\n"),
  baudrate: 9600
}, false);

//Handle website calls
app.get('/', function(req, res){
  res.sendFile('www/index.html', { root: __dirname });
});
app.get('/index', function(req, res){
  res.sendFile('www/index.html', { root: __dirname });
});
app.get('/game', function(req, res){
  res.sendFile('www/game.html', { root: __dirname });
});
app.get('/score', function(req, res){
  res.sendFile('www/score.html', { root: __dirname });
});

var leaderboard = [[]];//[['ABM', 100], ['EAL', 50], ['TOM', 10]]

//Handle socket io events
io.on('connection', function(socket){
  console.log('a user connected');
  socket.on('controll', function(c){
    console.log('controlls: ' + c);
    sp.write("1," + c + "\n");
  });
  socket.on('score', function(){
    console.log('Get highscore');
    for (var i =  0; i < 16; i++) {
      sp.write("2, " + i + "\n");
      sleep(50);
    };
    socket.emit('score', leaderboard);
  });
});

//Start http server
http.listen(80, function(){
  console.log('listening on port 80');
});

//Handle serial communication
sp.open(function (error) {
  if ( error ) {
    console.log('failed to open: '+error);
  } else {
    console.log('open');
    sp.on('data', function(data) {
      console.log('data received: ' + data);
      var arr = data.split(",");
      if (Number(arr[0]) == 2 ){ //if highscore recieved
        leaderboard[Number(arr[1])-1] = [arr[2], Number(arr[3])]; //Add highscore to leaaderboard
      }
    });
    sp.write("ls\n", function(err, results) {
      console.log('err ' + err);
      console.log('results ' + results);
    });
  }
});


function sleep(milliseconds) {
  var start = new Date().getTime();
  for (var i = 0; i < 1e7; i++) {
    if ((new Date().getTime() - start) > milliseconds){
      break;
    }
  }
}