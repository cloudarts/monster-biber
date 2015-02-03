var express = require('express');
var app = express();
var http = require('http').Server(app);

app.use(express.static(__dirname + '/html'));

http.listen(3000, function() {
	console.log('http server listening on *.3000');
});
