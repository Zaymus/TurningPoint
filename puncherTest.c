#pragma config(Motor,  port2,           puncher,       tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           puncher2,      tmotorVex393_MC29, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task main()
{
	while(true)
	{
		if (vexRT(Btn6U) == true)
		{
			motor[puncher] = 127;
			motor[puncher2] = 127;
	  }//end of if
	  else
	  {
	  	motor[puncher] = 0;
	  	motor[puncher2] = 0;
	  }//end of else
	}//end of while
}//end of main
