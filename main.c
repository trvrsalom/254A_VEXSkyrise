#pragma config(Sensor, in1,    autoPot,        sensorPotentiometer)
#pragma config(Sensor, in2,    posPot,         sensorPotentiometer)
#pragma config(Sensor, dgtl1,  rDriveEncoder,  sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  rLiftEncoder,   sensorQuadEncoder)
#pragma config(Sensor, dgtl5,  lDriveEncoder,  sensorQuadEncoder)
#pragma config(Sensor, dgtl7,  lLiftEncoder,   sensorQuadEncoder)
#pragma config(Sensor, dgtl9,  liftDetectLeft, sensorTouch)
#pragma config(Sensor, dgtl10, liftDetectRight, sensorTouch)
#pragma config(Motor,  port1,           driveLB,       tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           driveLF,       tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           liftLB,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           liftLT,        tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port5,           intakeR,       tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           intakeL,       tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           liftRT,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           liftRB,        tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port9,           driveRF,       tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port10,          driveRB,       tmotorVex393_HBridge, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX)

#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!

float ignoreDriveError = 40;
float driveKp = 1.5;
float driveKi = 0.0;
float driveKd = 0.0;

float ignoreArmError = 40;
float armKp = 10.0;
float armKi = 0.0;
float armKd = 0.0;

bool precise = false;
float precisionMode = 1;

bool toDriveStream = false;
float rPrevError = 0;
float rIntegral = 0;
float lPrevError = 0;
float lIntegral = 0;
float rError;
float lError;
float lDerivative;
float rDerivative;
float driveSetLPt = 0;
float driveSetRPt = 0;

float batLevel;

bool toArmStream = false;
float rAPrevError = 0;
float rAIntegral = 0;
float lAPrevError = 0;
float lAIntegral = 0;
float rAError;
float lAError;
float lADerivative;
float rADerivative;
float liftSetPt = 0;
int lLiftModifier = -1;
float lastLiftSetPt = 0;



void init() {
	SensorValue[rLiftEncoder] = 0;
	SensorValue[lLiftEncoder] = 0;
	SensorValue[rDriveEncoder] = 0;
	SensorValue[lDriveEncoder] = 0;
}

task armPID() {
	while(true) {
		rAError = liftSetPt + SensorValue[rLiftEncoder] + lLiftModifier;
		lAError = liftSetPt - SensorValue[lLiftEncoder];
		lAIntegral += lAError;
		rAIntegral += rAError;
		rADerivative = rAError - rAPrevError;
		lDerivative = lAError - lAPrevError;
		motor[liftLB] = ((armKp*lAError) + (armKi*lAIntegral) + (armKd*lADerivative))/precisionMode;
		motor[liftLT] = ((armKp*lAError) + (armKi*lAIntegral) + (armKd*lADerivative))/precisionMode;
		motor[liftRB] = ((armKp*RAError) + (armKi*RAIntegral) + (armKd*RADerivative))/precisionMode;
		motor[liftRT] = ((armKp*RAError) + (armKi*RAIntegral) + (armKd*RADerivative))/precisionMode;
		if(toArmStream) {
			writeDebugStreamLine("%f, %f,",lAError, rAError);
		}
	}
}

task drivePID() {
	while(true) {
		rError = driveSetRPt + SensorValue[rDriveEncoder];
		lError = driveSetLPt - SensorValue[lDriveEncoder];
		lIntegral += lError;
		rIntegral += rError;
		rDerivative = rError - rPrevError;
		lDerivative = lError - lPrevError;
		motor[driveRB] = (driveKp*rError) + (driveKi*rIntegral) + (driveKd*rDerivative);
		motor[driveRF] = (driveKp*rError) + (driveKi*rIntegral) + (driveKd*rDerivative);
		motor[driveLB] = (driveKp*lError) + (driveKi*lIntegral) + (driveKd*lDerivative);
		motor[driveLF] = (driveKp*lError) + (driveKi*lIntegral) + (driveKd*lDerivative);
		if(toDriveStream) {
			writeDebugStreamLine("%f, %f,", rError, lError);
		}
	}
}

void setDrive(int left, int right) {
	motor[driveLB] = motor[driveLF] = left;
	motor[driveRB] = motor[driveRF] = right;
}

void driveStream(bool set) {
	toDriveStream = set;
}

void armStream(bool set)
{
	toArmStream = set;
}

void driveTicks(float ticks) {
	driveSetRPt += ticks;
	driveSetLPt += ticks;
}

void turnTicks(float ticks) {
	driveSetRPt -= ticks;
	driveSetLPt += ticks;
}

void intake(int po) {
	motor[intakeR] = -po;
	motor[intakeL] = po;
}

void armControl() {
	if(vexRT[Btn8D] && precisionMode == 1)
		precisionMode = 8;
  else if(!vexRT[Btn8D] && precisionMode == 8)
  	precisionMode = 1;
	if(vexRT[Btn6D]) {
		liftSetPt = SensorValue[rLiftEncoder] + (40);
	}
	else if(vexRT[Btn6U]) {
		liftSetPt = SensorValue[rLiftEncoder] - (40);
	}
	else if(vexRT[Btn7D]) {
		liftSetPt = SensorValue[rLiftEncoder] + (2);
	}
	else {
		liftSetPt = SensorValue[rLiftEncoder] - 1;
	}
	if(liftDetectLeft)
		SensorValue[lLiftEncoder] = 0;
  if(liftDetectRight)
  	SensorValue[rLiftEncoder] = 0;
}

void driveControl(float leftPo, float rightPo) {
	motor[driveRB] = rightPo;
	motor[driveRF] = rightPo;
	motor[driveLB] = leftPo;
	motor[driveLF] = leftPo;
}

void intakePo(float po) {
	motor[intakeL] = -po;
	motor[intakeR] = po;
}

void deploy() {
	liftSetPt = -30;
	wait1Msec(1000);
	intakePo(-127);
	wait1Msec(500);
	liftSetpt = -5;
	wait1Msec(1000);
}


void blueSmallAuto() {
 driveTicks(-395);
 wait1Msec(1500);
 deploy();
 turnTicks(-125);
 wait1Msec(1000);
 liftSetPt = -60;
 wait1Msec(1000);
 intakePo(127);
 wait1Msec(1000);
 driveTicks(-200);
}

void redSmallAuto() {
 driveTicks(-395);
 wait1Msec(1500);
 deploy();
 turnTicks(125);
 wait1Msec(1000);
 liftSetPt = -60;
 wait1Msec(1000);
 intakePo(127);
 wait1Msec(1000);
 driveTicks(-200);
}

void blueTallAuto() {
	deploy();
	intakePo(-127);
	wait1Msec(500);
	driveTicks(750);
	wait1Msec(3000);
	turnTicks(410);
	wait1Msec(1000);
	driveTicks(900);
	wait1Msec(1500);
	turnTicks(370);
	wait1Msec(2000);
	driveTicks(-70);
	wait1Msec(500);
	liftSetPt = -100;
	wait1Msec(1500);
	turnTicks(-70);
	wait1Msec(1000);
	driveTicks(85);
	wait1Msec(1000);
	intakePo(127);
}

void redTallAuto() {
	deploy();
	intakePo(-127);
	wait1Msec(500);
	driveTicks(750);
	wait1Msec(3000);
	turnTicks(-390);
	wait1Msec(1000);
	driveTicks(880);
	wait1Msec(1500);
	turnTicks(-385);
	wait1Msec(2000);
	driveTicks(-65);
	wait1Msec(500);
	liftSetPt = -100;
	wait1Msec(1500);
	driveTicks(120);
	wait1Msec(1000);
	intakePo(127);
	wait1Msec(1000);
	driveTicks(-30);
	wait1Msec(1000);
}

void intakeControl() {
	if(vexRT[Btn5U])
		intakePo(127);
	else if(vexRT[Btn5D])
		intakePo(-127);
	else
		intakePo(-32);
}


void autonSelector() {
	if(SensorValue[posPot] <=2000) {
		if(SensorValue[autoPot] <= 1500) {
			blueSmallAuto();
		}
		else if(SensorValue[autoPot] >= 2500) {
			redSmallAuto();
		}
		else {}
	}
	else if(SensorValue[posPot] >= 2000) {
		if(SensorValue[autoPot] <= 1500) {
			blueTallAuto();
		}
		else if(SensorValue[autoPot] >= 2500) {
			redTallAuto();
		}
		else {}
	}
}

void pre_auton()
{
  bStopTasksBetweenModes = true;
}


task autonomous()
{
	init();
	startTask(drivePID);
	startTask(armPID);
	redTallAuto();
  //blueSmallAuto();
	//stopTask(drivePID);
	//stopTask(armPID);
}

task usercontrol()
{
	init();
	while (true)
	{
		startTask(armPID);
		batLevel = nImmediateBatteryLevel/1000.0;
		armStream(true);
		driveControl(vexRT[Ch3] + vexRT[Ch1], vexRT[Ch3] - vexRT[Ch1]);
		armControl();
		intakeControl();
	}
}
