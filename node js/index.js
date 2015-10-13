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

var sp = new SerialPort("COM5", {
  parser: serialport.parsers.readline("\n")
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

//Handle socket io events
io.on('connection', function(socket){
  console.log('a user connected');
  socket.on('controll', function(c){
    console.log('controlls: ' + c);
  });
  socket.on('score', function(){
    console.log('Get highscore');
    socket.emit('score', [['ABM', 100], ['EAL', 50], ['TOM', 10]]);
  });
});

//Start http server
http.listen(3000, function(){
  console.log('listening on port 3000');
});

//Handle serial communication
sp.open(function (error) {
  if ( error ) {
    console.log('failed to open: '+ error);
  } 
  else {
    console.log('Serial port open');
    sp.on('data', function(data) {
      console.log('data received: ' + data);
    });
  }
});
