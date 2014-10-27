#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, I2C_1,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_2,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_3,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_4,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Motor,  port1,           rB,            tmotorVex393_HBridge, openLoop, reversed, encoderPort, I2C_2)
#pragma config(Motor,  port2,           rF,            tmotorVex393_MC29, openLoop, reversed, encoderPort, I2C_1)
#pragma config(Motor,  port3,           lF,            tmotorVex393_MC29, openLoop, encoderPort, I2C_4)
#pragma config(Motor,  port4,           lru,           tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port5,           lrd,           tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port6,           llu,           tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port7,           lld,           tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port10,          lB,            tmotorVex393_HBridge, openLoop, encoderPort, I2C_3)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!

int encoderTicks = 392;

float driveKp = 1.2;
float driveKi = 0.0;
float driveKd = 0.0;

int fwd;
int strafe;
int clockwise;

int ignoreDriveError = 1;
int driveErrorMax = 40;

float integralLF = 0;
float integralLB = 0;
float integralRF = 0;
float integralRB = 0;

int prevErrorLF = 0;
int prevErrorLB = 0;
int prevErrorRF = 0;
int prevErrorRB = 0;

//Reset All Encoders
void clearEncoders () {
	nMotorEncoder[rB] = 0;
	nMotorEncoder[rF] = 0;
	nMotorEncoder[lF] = 0;
	nMotorEncoder[lB] = 0;
}

//Set Arm Power
void armPo(int power) {
	motor[lru] = motor[lrd] = motor[llu] = motor[lld] = power;
}

//Set target value in ticks
void driveTicks(int fwdDrive, int rDrive, int rotateDrive)
{
	fwd = fwdDrive*sqrt(2);
	strafe = rDrive*sqrt(2);
	clockwise = rotateDrive*sqrt(2);
}

//Set drive target in inches
void driveIn(int fwdDrive, int rDrive, int rotateDrive)
{
	float fakefwd = (fwdDrive*sqrt(2)*4*PI)/encoderTicks;
	float fakeright = (rDrive*sqrt(2)*4*PI)/encoderTicks;
	fwd = fakefwd;
	strafe = fakeright;
	clockwise = rotateDrive;
}

//PID for arm
task armPID() {

}

//PID for drive
task drivePID() {
	while(true) {
		int ticksRF = nMotorEncoder[rF];
		int ticksLB = nMotorEncoder[lB];
		int ticksLF = nMotorEncoder[lF];
		int ticksRB = nMotorEncoder[rB];

		int targetRB = fwd - clockwise + strafe;
		int targetLB = fwd + clockwise - strafe;
		int targetRF = fwd - clockwise - strafe;
		int targetLF = fwd + clockwise + strafe;

		int errorRB = targetRB - ticksRB;
		int errorLB = targetLB - ticksLB;
		int errorRF = targetRF - ticksRF;
		int errorLF = targetLF - ticksLF;

		integralRB = errorRB;
		integralLB = errorLB;
		integralRF = errorRF;
		integralLF = errorLF;

		if(abs(integralRB) < ignoreDriveError) {
			integralRB = 0;
		}
		if(abs(integralRB) > driveErrorMax) {
			integralRB = 0;
		}


		if(abs(integralRF) < ignoreDriveError) {
			integralRF = 0;
		}
		if(abs(integralRF) > driveErrorMax) {
			integralRF = 0;
		}


		if(abs(integralLB) < ignoreDriveError) {
			integralLB = 0;
		}
		if(abs(integralLB) > driveErrorMax) {
			integralLB = 0;
		}


		if(abs(integralLF) < ignoreDriveError) {
			integralLF = 0;
		}
		if(abs(integralLF) > driveErrorMax) {
			integralLF = 0;
		}

		int derivativeRF = errorRF - prevErrorRF;
		int derivativeRB = errorRB - prevErrorRB;
		int derivativeLF = errorLF - prevErrorLF;
		int derivativeLB = errorLB - prevErrorLB;

		prevErrorRF = errorRF;
		prevErrorRB = errorRB;
		prevErrorLB = errorLB;
		prevErrorLF = errorLF;

		motor[rF] = driveKp * errorRF + driveKi * integralRF + driveKd * derivativeRF;
		motor[rB] = driveKp * errorRB + driveKi * integralRB + driveKd * derivativeRB;
		motor[lF] = driveKp * errorLF + driveKi * integralLF + driveKd * derivativeLF;
		motor[lB] = driveKp * errorLB + driveKi * integralLB + driveKd * derivativeLB;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                          Pre-Autonomous Functions
//
// You may want to perform some actions before the competition starts. Do them in the
// following function.
//
/////////////////////////////////////////////////////////////////////////////////////////

void pre_auton()
{
	// Set bStopTasksBetweenModes to false if you want to keep user created tasks running between
	// Autonomous and Tele-Op modes. You will need to manage all user created tasks if set to false.
	bStopTasksBetweenModes = true;

	// All activities that occur before the competition starts
	// Example: clearing encoders, setting servo positions, ...
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 Autonomous Task
//
// This task is used to control your robot during the autonomous phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////

task autonomous()
{
	// .....................................................................................
	// Insert user code here.
	// .....................................................................................

	AutonomousCodePlaceholderForTesting();  // Remove this function call once you have "real" code.
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 User Control Task
//
// This task is used to control your robot during the user control phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////
int battVoltage;

task usercontrol()
{
	// User control code here, inside the loop
	clearEncoders();
	startTask(drivePID);

	while (true)
	{
		battVoltage = nImmediateBatteryLevel/1000.0;
		fwd = vexRT[Ch4];
		strafe = vexRT[Ch3];
		clockwise = vexRT[Ch1];

		if(vexRT[Btn6U] == 1) {
			armPo(127);
		}
		else if(vexRT[Btn6D] == 1) {
			armPo(-127);
		}
		else {
			armPo(0);
		}

		//Simple PID free drive for testing
		/*
		motor[rB] = fwd - clockwise + right;
		motor[lB] = fwd + clockwise - right;
		motor[rF] = fwd - clockwise - right;
		motor[lF] = fwd + clockwise + right;
		/**/
	}
}
