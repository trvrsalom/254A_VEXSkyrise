void encoderClear () {
	nMotorEncoder[lF] = 0;
	nMotorEncoder[lB] = 0;
	nMotorEncoder[rB] = 0;
	nMotorEncoder[rF] = 0;
}

void redSkyrise () {
	int threshold = 505;
	bool hasReached = false;
	while (!hasReached) {
		if(SensorValue[lineFollowCENTER] > threshold) {
			motor[lB] = -64;
			motor[rB] = 64;
			motor[lF] = 64;
			motor[rF] = -64;
		}
		else if(SensorValue[lineFollowFWD] > threshold) {
			motor[lB] = -50;
			motor[rB] = 50;
			motor[lF] = 78;
			motor[rF] = -78;
		}
		else if(SensorValue[lineFollowBACK] > threshold) {
			motor[lB] = -78;
			motor[rB] = 78;
			motor[lF] = 50;
			motor[rF] = -50;
		}
		if(SensorValue[lineFollowEND] > threshold) {
			hasReached = true;
		}
	}
}
