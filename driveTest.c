#pragma config(Sensor, in1,    ballDetector,   sensorLineFollower)
#pragma config(Sensor, dgtl1,  transmission,   sensorDigitalOut)
#pragma config(Sensor, dgtl2,  intakeAngler,   sensorDigitalOut)
#pragma config(Sensor, dgtl3,  puncherAngler,  sensorDigitalOut)
#pragma config(Motor,  port1,           rightBack,     tmotorVex393_HBridge, openLoop, reversed)
#pragma config(Motor,  port2,           rightMid,      tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           rightFront,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           intake,        tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port5,           arm,           tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           leftFront,     tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port7,           leftMid,       tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           leftBack,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           puncherMotor1, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port10,          puncherMotor2, tmotorVex393_HBridge, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

typedef enum {strength, speed} type;
type gearType = speed;

void queueShot()
{
	motor[puncherMotor1] = 127;
	motor[puncherMotor2] = 127;
	if (time1[T1] >= 400)
	{
		motor[puncherMotor1] = 50;
		motor[puncherMotor2] = 50;
	}//end of if
}//end of queueShot

task driveControl()
{
	int rightSpeed;
	int leftSpeed;

	const int joystickThresh = 30;

	while(true)
	{
		if (vexRT(Ch3) + vexRT(Ch4) >= joystickThresh || vexRT(Ch3) - vexRT(Ch4) <= -joystickThresh)
		{
			if (vexRT(Ch3) >= 30 || vexRT(Ch3) <= -joystickThresh)
			{
				if (vexRT(Ch4) >= 30 || vexRT(Ch4) <= -joystickThresh)
				{
					leftSpeed = vexRT(Ch3) + vexRT(Ch4);
					rightSpeed = vexRT(Ch3) - vexRT(Ch4);
				}//end of if
				else
				{
					leftSpeed = vexRT(Ch3);
					rightSpeed = vexRT(Ch3);
				}//end of else
			}//end of if
			else if (vexRT(Ch4) >= joystickThresh || vexRT(Ch4) <= -joystickThresh)
			{
				if (vexRT(Ch4) >= joystickThresh)
				{
					leftSpeed = vexRT(Ch4) / 3;
					rightSpeed = -vexRT(Ch4) / 3;
				}//end of if
				else
				{
					leftSpeed = -vexRT(Ch4) / 3;
					rightSpeed = vexRT(Ch4) / 3;
				}//end of else
			}//end of else if
		}//end of if
		else
		{
			leftSpeed = 0;
			rightSpeed = 0;
		}//end of else

		motor[rightFront] = rightSpeed;
		motor[rightMid] = rightSpeed;
		motor[rightBack] = rightSpeed;
		motor[leftFront] = leftSpeed;
		motor[leftMid] = leftSpeed;
		motor[leftBack] = leftSpeed;

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

task puncher()
{
	int stage = 0;
	clearTimer(T1);
	while(true)
	{
		switch(stage)
		{
		case 0:
			queueShot();
			break;
		case 1:
			if (ballLoaded())
			{
				clearTimer(T1);
				stage = 2;
			}//end of if
			else
			{
				stage = 3;
			}
			break;

		case 2:
			motor[puncherMotor1] = 127;
			motor[puncherMotor2] = 127;
			delay(50);
			motor[puncherMotor1] = 0;
			motor[puncherMotor2] = 0;
			stage = 3;
			break;

		case 3:
			stopTask(puncher);
			break;
		}
	}
}

task main()
{
	while(true)
	{
		startTask(driveControl);


		SensorValue[transmission] = gearType;

		if (vexRT(Btn5U) == true)
		{
			motor[intake] = 127;
		}//end of if
		else
		{
			motor[intake] = 0;
		}//end of else

		if (vexRT(Btn5D) == true)
		{
			motor[intake] = -127;
		}//end of if
		else
		{
			motor[intake] = 0;
		}//end of else

		if (vexRT(Btn8R) == true)
		{
			SensorValue[puncherAngler] = !SensorValue[puncherAngler];
		}//end of if

		if (vexRT(Btn8D) == true)
		{
			if(gearType == speed)
			{
				gearType = strength;
			}//end of if
			else
			{
				gearType = speed;
			}//end of else
		}//end of if

		if(vexRT(Btn6U) == true)
		{
			startTask(puncher);
		}//end of if

		if (vexRT(Btn8U) == true)
		{
			SensorValue[puncherAngler] = !SensorValue[puncherAngler];
		}//end of if
	}//end of while
}//end of main
