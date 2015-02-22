var express = require('express');
var app = express();
var http = require('http').Server(app);
var io = require('socket.io')(http);
var argv = require('minimist')(process.argv.slice(2));

if( !argv.s || !argv.p ) {
	console.log("\n\nusage: node app -p [PORT] -s [SERIAL DEVICE]\n\n");
	process.exit(1);
}

var SerialPort = require('serialport').SerialPort;
var serialPort = new SerialPort(argv.s, { baudrate:115200 });

serialPort.on("open", function() {
	console.log("\n\nserial port open...");

	serialPort.on('data', function(data) {
		console.log("received data from serial: " + data);
	});
});

app.use(express.static(__dirname + '/html'));

http.listen(argv.p, function() {
	console.log('http server listening on *.' + argv.p);
});

io.on('connection', function(socket) {
	socket.on('action', function(data) {
		onNewAction(data);
	});

	socket.on('head', function(data) {
		serialPort.write("1:" + data.head);
	});

	socket.on('sonar', function() {
		serialPort.write("2");
	});
});

var onNewAction = function(data) {
	console.log("received new action: " + JSON.stringify(data));	

	serialPort.write("0:" + data.left + ":" + data.right, function(err, result) {
		setTimeout(function() {
			stop();
		}, data.duration * 1000);
	});
};

var stop = function() {
	serialPort.write("0:0:0");
};
