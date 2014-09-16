//Setup
void gyroClear () {
	SensorType[gyro] = sensorNone;
	wait1Msec(1000);
	SensorType[gyro] = sensorGyro;
	wait1Msec(1000);
}

void encoderClear () {
	nMotorEncoder[lF] = 0;
	nMotorEncoder[lB] = 0;
	nMotorEncoder[rB] = 0;
	nMotorEncoder[rF] = 0;
}
