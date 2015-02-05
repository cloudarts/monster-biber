var express = require('express');
var app = express();
var http = require('http').Server(app);
var io = require('socket.io')(http);

app.use(express.static(__dirname + '/html'));

http.listen(3000, function() {
	console.log('http server listening on *.3000');
});

io.on('connection', function(socket) {
	socket.on('action', function(data) {
		onNewAction(data);
	});
});

var onNewAction = function(data) {
	console.log("received new action: " + JSON.stringify(data));	
};
