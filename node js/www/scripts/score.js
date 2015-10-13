//Start socket io connection to node
var socket = io();

socket.emit('score', 'req');

socket.on('score', function(score){
	for (var i = 0; i < score.length; i++) {
		$('#score').append($('<tr>').append($('<th>').text(i+1), $('<th>').text(score[i][0]), $('<th>').text(score[i][1]) ));
	};
});