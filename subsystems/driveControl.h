//Drive Control Modifiers
float lx () {
	int i = vexRT[Ch4]/127;
	i = 127*(i^3);
	return i;
}

float ly () {
	int i = vexRT[Ch3]/127;
	i = 127*(i^3);
	return i;
}

float rx () {
	int i = vexRT[Ch1]/127;
	i = 127*(i^3);
	return i;
}

float ry () {
	int i = vexRT[Ch2]/127;
	i = 127*(i^3);
	return i;
}

//Drive Sensor Getters
int getFwdLeft () {
	int i = nMotorEncoder[lF];
	return i;
}

int getRearLeft () {
	int i = nMotorEncoder[lB];
	return i;
}

int getRearRight () {
	int i = nMotorEncoder[rB];
	return i;
}

int getFwdRight () {
	int i = nMotorEncoder[rF];
	return i;
}

int getGyro () {
		int i = SensorValue[gyro];
		return i;
}

//Basic Control w/o PID
void basicDrive (float forward, float right, float clockwise) {
	float k = 0;
	clockwise = k*clockwise;

	motor[lF] = forward + clockwise + right;
	motor[rF] = forward - clockwise - right;
	motor[lB] = forward + clockwise - right;
	motor[rB] = forward - clockwise + right;
}

//Field Centric Control w/o PID
void bCentricDrive (float forward, float right, float clockwise, int theta) {
	float k = 0;
	clockwise = k*clockwise;

	float ftheta = (float)theta;
	float temp = forward*cos(ftheta) + right*sin(ftheta);
	right = -forward*cos(ftheta) + right*sin(ftheta);
	forward = temp;

	motor[lF] = forward + clockwise + right;
	motor[rF] = forward - clockwise - right;
	motor[lB] = forward + clockwise - right;
	motor[rB] = forward - clockwise + right;
}
