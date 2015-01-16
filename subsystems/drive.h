bool driveStream = false;

task drivePID() {
	if(driveStream)
		//stream
}

function drivePIDStream(bool set) {
	driveStream = set;
}
