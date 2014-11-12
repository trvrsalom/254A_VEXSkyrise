void encoderClear () {
	nMotorEncoder[lF] = 0;
	nMotorEncoder[lB] = 0;
	nMotorEncoder[rB] = 0;
	nMotorEncoder[rF] = 0;
}

void redSkyrise () {
	motor[in] = 127;
	wait1Msec(500);
	motor[in] = 0;
	int threshold = 200;
	bool hasReached = false;
	while (/*!hasReached*/ true) {
		if(SensorValue[lineFollowBack] > threshold && SensorValue[lineFollowFWD] > threshold) {
			motor[RB] = +50;
			motor[LB] = -50;
			motor[RF] = -50;
			motor[LF] = +50;
		}
		else if(SensorValue[lineFollowBack] < threshold) {
			motor[RB] = +40;
			motor[LB] = -40;
			motor[RF] = -60;
			motor[LF] = +60;
		}
		else if(SensorValue[lineFollowFWD] < threshold) {
			motor[RB] = +60;
			motor[LB] = -60;
			motor[RF] = -40;
			motor[LF] = +40;
		}
		if(SensorValue[lineFollowEND] > threshold) {
			hasReached = true;
		}
	}
}
