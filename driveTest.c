#pragma config(Sensor, in1,    ballDetector,   sensorLineFollower)
#pragma config(Sensor, dgtl1,  transmission,   sensorDigitalOut)
#pragma config(Sensor, dgtl2,  intakeAngler,   sensorDigitalOut)
#pragma config(Sensor, dgtl3,  puncherAngler,  sensorDigitalOut)
#pragma config(Sensor, dgtl6,  armEnc,         sensorQuadEncoder)
#pragma config(Motor,  port1,           rightBack,     tmotorVex393_HBridge, openLoop, reversed)
#pragma config(Motor,  port2,           rightMid,      tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           rightFront,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           arm,           tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           intake,        tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port6,           leftFront,     tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port7,           leftMid,       tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           leftBack,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           puncherMotor1, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port10,          puncherMotor2, tmotorVex393_HBridge, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

int armTar = 10;
int enc;
bool pressed = false;

typedef enum {strength, speed} type;
	type gearType = speed;

task driveControl()
{

	int rightSpeed;
	int leftSpeed;

	const int joystickThresh = 30;

	while(true)
	{
		SensorValue[transmission] = gearType;

		motor[rightFront] = rightSpeed;
		motor[rightMid] = rightSpeed;
		motor[rightBack] = rightSpeed;
		motor[leftFront] = leftSpeed;
		motor[leftMid] = leftSpeed;
		motor[leftBack] = leftSpeed;
		SensorValue[transmission] = gearType;

		if (vexRT(Ch3) >= joystickThresh || vexRT(Ch3) <= -joystickThresh || vexRT(Ch4) >= joystickThresh || vexRT(Ch4) <= -joystickThresh)
		{
			leftSpeed = vexRT(Ch3) + vexRT(Ch4);
			rightSpeed = vexRT(Ch3) - vexRT(Ch4);
		}//end of if
		else
		{
			leftSpeed = 0;
			rightSpeed = 0;
		}//end of else

		if (vexRT(Btn5U) == true)
		{
			motor[intake] = 127;
		}
		else if (vexRT(Btn5D) == true)
		{
			motor[intake] = -127;
		}
		else
		{
			motor[intake] = 0;
		}
		if (vexRT(Btn8D) == true)
		{
			pressed = true;
		}//end of if

		if (vexRT(Btn8D) == false && pressed)
		{
			if(gearType == speed)
			{
				gearType = strength;
			}//end of if
			else
			{
				gearType = speed;
			}//end of else
			pressed = false;
		}

		if(vexRT(Btn6U) == true)
		{
			motor[puncherMotor1] = 127;
			motor[puncherMotor2] = 127;
		}//end of if
		else
		{
			motor[puncherMotor1] = 0;
			motor[puncherMotor2] = 0;
		}


		if (vexRT(Btn8U) == true)
		{
			SensorValue[puncherAngler] = 0;
		}//end of if

		if (vexRT(Btn8L) == true)
		{
			SensorValue[puncherAngler] = 1;
		}//end of if

		if (vexRT(Btn8R) == true)
		{
			pressed = true;
		}//end of if

		if (vexRT(Btn8R) == false && pressed)
		{
			SensorValue[intakeAngler] = !SensorValue[intakeAngler];
			pressed = false;
		}
		wait1Msec(20);
	}//end of while
}//end of driveControl task

bool ballLoaded()
{
	const int ballThresh = 200;
	if (SensorValue[ballDetector] <= ballThresh)
	{
		return true;
	}//end of if
	else
	{
		return false;
	}//end of else
}//end of ballLoadded

task main()
{
	/*SensorValue[armEnc] = 0;
	while(SensorValue[armEnc] < armTar)
	{
		enc = SensorValue[armEnc];
		motor[arm] = 30;
	}
	SensorValue[armEnc] = 0;
	armTar = 0;
	enc = SensorValue[armEnc];
	motor[arm] = 15;*/
	while(true)
	{
		/*if(SensorValue[armEnc] < armTar + 5 && SensorValue[armEnc] > armTar - 5)
		{
			motor[arm] = 20;
		}
		else
		{
			if (SensorValue[armEnc] > armTar)
			{
				motor[arm] = -80;
			}
			else if (SensorValue[armEnc] < armTar)
			{
				motor[arm] = 80;
			}
		}*/
		startTask(driveControl);

	}//end of while
}//end of main