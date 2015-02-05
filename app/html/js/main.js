$(function() {
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
		var right parseInt( dialRight.val() );
		var head = parseInt( dialHead.val() );
	};
});
