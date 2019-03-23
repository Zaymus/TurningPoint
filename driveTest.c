#pragma config(Sensor, in1,    ballDetector,   sensorLineFollower)
#pragma config(Sensor, dgtl1,  transmission,   sensorDigitalOut)
#pragma config(Sensor, dgtl2,  intakeAngler,   sensorDigitalOut)
#pragma config(Motor,  port1,           Rfront,         tmotorVex393_HBridge, openLoop, reversed)
#pragma config(Motor,  port2,           puncherMotor,  tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port8,           intake,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           Rback,          tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port10,          Rmid,           tmotorVex393_HBridge, openLoop)



typedef enum {strength, speed} type;
type gearType = strength;


const int joystickThresh = 30;

int Rdrive;
int Ldrive;

int mapJoystick(int channel){
	if (abs(channel) < joystickThresh) return 0;
	  // check if magnitude is less than threshold on joystick in case driver accidentally shoved stick
	
	else // if driver has pushed the joystick definitively, map the joystick range to motor range
	{	
		float slope = 1.31;
		float b = 39.3;
		return (slope * channel -b);
	}//end of else
}//end of mapJoystick




task main()
{
	while(true)
	{
		if (abs(mapJoystick(vexRT(Ch4))) )
		{
		Rdrive = abs(mapJoystick(vexRT(Ch3)));
		Ldrive = abs(mapJoystick(vexRT(Ch3)));
		}
		else
		{
			Rdrive = abs(mapJoystick(vexRT(Ch3))) + abs(mapJoystick(vexRT(Ch4)));
		}
		motor[Rfront] = Rdrive;
		motor[Rback] = Rdrive;
		motor[Rmid] = Rdrive;

		SensorValue[transmission] = gearType;

		if (vexRT(Btn7U) == true)
		{
			gearType = speed;
		}//end of if

		if (vexRT(Btn7D) == true)
		{
			gearType = strength;
		}//end of if

		if (vexRT(Btn8U) == true)
		{
			motor[intake] = -127;
		}//end of if

		if (vexRT(Btn8R) == true)
		{
			motor[intake] = 0;
		}//end of if

		if (vexRT(Btn8D) == true)
		{
			motor[intake] = 127;
		}//end of if

		if (vexRT(Btn5U) == true)
		{
			SensorValue[intakeAngler] = 1;
		}//end of if

		if (vexRT(Btn5D) == true)
		{
			SensorValue[intakeAngler] = 0;
		}//end of if

		if (vexRT(Btn6U) == true)
		{
			motor[puncherMotor] = 127;
	  }//end of if
	  else
	  {
	  	motor[puncherMotor] = 0;
	  }//end of else
	}//end of while
}//end of main
