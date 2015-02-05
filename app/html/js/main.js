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

	$("#btnSubmit").click(function() {
		onSubmitClicked();
	});

	var onSubmitClicked = function() {
		var duration = parseFloat( dialDuration.val() );
		var left = parseInt( dialLeft.val() );
		var right = parseInt( dialRight.val() );
		var head = parseInt( dialHead.val() );

		socket.emit('action', {duration: duration, left: left, right: right, head: head});

		dialDuration.val(0).trigger('change');
		dialLeft.val(0).trigger('change');
		dialRight.val(0).trigger('change');
		dialHead.val(1500).trigger('change');
	};
});
