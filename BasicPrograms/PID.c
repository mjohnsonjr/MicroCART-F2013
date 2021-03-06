/* Simple PID C function */
/*********************************************************
Title: PID
*
* Static Data:
*      float prev_err, float acc_err
*
* Description:  
*      PID controller. KP, KI, and KD are the PID constants.
*      Setpoint is the goal we want to achieve. Sensor
*      is the current state (e.g. current position).
*      Returns the correction to the control signal.
*
*  By: Michael Johnson
********************************************************/

/* TO COMPILE: gcc -o PID PID.cpp */

#include <stdio.h>
#include <stdlib.h>



typedef struct PID_t {
	float KP, KI, KD, setpoint, sensor;
	float prev_err; /* previous error */
	float acc_err;  /* accumulated error */	
} PID_t;


/* Prototypes */
void initializePIDConstants(PID_t *pids);
void getPIDCorrections(PID_t *pid, float* corrections);
float PID(float KP, float KI, float KD, float setpoint, float sensor, float* prev_err, float* acc_err);


int main(int argc, char** argv)
{
	

	/* Make PIDs */
	PID_t pids[6];

	/* Corrections for each of the 6 PIDs */	
	float corrections[6];

	/* Fill with the constants */
	initializePIDConstants(pids);

	/* Do stuff */
	while(1)
	{
		getPIDCorrections(pids, corrections); //TODO: , deltaTime


	}


}

/* TODO:
* Initializes each PIDs Coefficients.
*/
void initializePIDConstants(PID_t *pids)
{
	/*  Roll */
	pids[0].KP = 251;
	pids[0].KI = 0;
	pids[0].KD = 0;
	pids[0].setpoint = 0;
	pids[0].sensor = 0;
	pids[0].prev_err = 0;
	pids[0].acc_err = 0;
	
	/* Pitch */
	pids[1].KP = -251;
	pids[1].KI = 0;
	pids[1].KD = 0;
	pids[1].setpoint = 0;
	pids[1].sensor = 0;
	pids[1].prev_err = 0;
	pids[1].acc_err = 0;

	/* Yaw */
	pids[2].KP = 408;
	pids[2].KI = 0;
	pids[2].KD = 21;
	pids[2].setpoint = 0;
	pids[2].sensor = 0;
	pids[2].prev_err = 0;
	pids[2].acc_err = 0;

	/* Altitude */
	pids[3].KP = 44.076;
	pids[3].KI = 0.7777;
	pids[3].KD = 139.3324;
	pids[3].setpoint = 0;
	pids[3].sensor = 0;
	pids[3].prev_err = 0;
	pids[3].acc_err = 0;

	/* Longitude */
	pids[4].KP = 0.7;
	pids[4].KI = 0;
	pids[4].KD = 1.5;
	pids[4].setpoint = 0;
	pids[4].sensor = 0;
	pids[4].prev_err = 0;
	pids[4].acc_err = 0;

	/* Latitude */
	pids[5].KP = -0.7;
	pids[5].KI = 0;
	pids[5].KD = -1.5;
	pids[5].setpoint = 0;
	pids[5].sensor = 0;
	pids[5].prev_err = 0;
	pids[5].acc_err = 0;

}

/*
*	Copies the corrections of all 6 PIDs into the passed in corrections array.
*/
void getPIDCorrections(PID_t *pid, float* corrections) //, float deltaTime
 {
	unsigned i;
	for(i = 0; i < 6; i++)
	{
		corrections[i] = PID(pid[i].KP, pid[i].KI, pid[i].KD, pid[i].setpoint, pid[i].sensor, &pid[i].prev_err, &pid[i].acc_err); // TODO:, deltaTime
	}
}

/*
* Finds correction for a single PID.  Variables passed by reference are modified.
*/
float PID(float KP, float KI, float KD, float setpoint, float sensor, float* prev_err, float* acc_err) // TODO:, float deltaTime
{
 	float cur_err = 0;   /* Current state (e.g. position) */
	float err_diff = 0; /* Difference between current and previous error */
	float correction = 0; /* Amount to change control signal */
	double timeslice;

	/*Delta Time*/
	timespec now;
	delTime = ((double) (now.tv_sec - mark.tv_sec)) + ((double) (now.tv_nsec - mark.tv_nsec)/1000000000);
 
 
	/* Compute error, accumulated error, and change in error */
	cur_err = setpoint - sensor;
	*acc_err = *acc_err + cur_err;
	err_diff = cur_err - *prev_err;
 
 
	/* Compute correction */
	correction = (KP*cur_err) + (KI*(*acc_err)) + (KD*err_diff); // TODO: KI*deltaTime KD/deltaTime
	kiCor = KI*delTime;
	kdCor = KD/delTime;
  
 
	*prev_err = cur_err; /* Update prev_err */
 
	return correction;
}
