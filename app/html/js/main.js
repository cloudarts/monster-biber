$(function() {
	var socket = io();
	
	var dialDuration = $("#dialDuration");
	var dialLeft = $("#dialMotorLeft");
	var dialRight = $("#dialMotorRight");
	var dialHead = $("#dialHeadPosition");

	dialDuration.knob();
	dialLeft.knob();
	dialRight.knob();
	dialHead.knob();

	$("#btnSubmitAction").click(function() {
		onSubmitActionClicked();
	});
	$("#btnSubmitHead").click(function() {
		onSubmitHeadClicked();
	});
	$("#btnSubmitSonar").click(function() {
		onSubmitSonarClicked();
	});

	var onSubmitActionClicked = function() {
		var duration = parseFloat( dialDuration.val() );
		var left = parseInt( dialLeft.val() );
		var right = parseInt( dialRight.val() );

		socket.emit('action', {duration: duration, left: left, right: right});

		dialDuration.val(0).trigger('change');
		dialLeft.val(0).trigger('change');
		dialRight.val(0).trigger('change');
	};

	var onSubmitHeadClicked = function() {
		var head = parseInt( dialHead.val() );
		socket.emit('head', {head: head});	
	};

	var onSubmitSonarClicked = function() {
		socket.emit('sonar', null);
	}
});
