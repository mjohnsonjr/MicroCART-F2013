///*---------------------------------------------------------
// File: labet_main_kalman.c
//
// Procedures:
// - main
// - PredictAccG_pitch
// - PredictAccG_roll
// --------------------------------------------------------*/
//
///*---------------------------------------------------------
// INCLUDES
// ---------------------------------------------------------*/
//#include <system.h>
//#include <stdarg.h>
//#include <stdlib.h>
//#include <unistd.h>
//#include <stddef.h>
//#include <fcntl.h>
//#include <stdio.h>
//#include <math.h>
//#include <sys/alt_timestamp.h>
//#include <alt_types.h>
//#include <sys/time.h>
//#include "hello_world.h"
//#include "labet.h"
//#include "imu.h"
//#include "ars.h"
//#include "ping.h"
//#include "controls.h"
//#define SIZE_OF_DATA_PACKET 56
////#include "kalmanfilter.h"
///*---------------------------------------------------------
// DEFINITIONS
// ---------------------------------------------------------*/
//
///*---------------------------------------------------------
// TYPES
// ---------------------------------------------------------*/
///*---------------------------------------------------------
// GLOBAL VARIABLES
// ---------------------------------------------------------*/
//struct MCTPIDERR errLat;
//struct MCTPIDERR errLong;
//struct MCTPIDERR errAlt;
//struct MCTPIDERR errPitch;
//struct MCTPIDERR errRoll;
//struct MCTPIDERR errYaw;
//struct MCTPID UAVLat;
//struct MCTPID UAVLon;
//struct MCTPID UAVAlt;
//struct MCTPID UAVPitch;
//struct MCTPID UAVRoll;
//struct MCTPID UAVYaw;
//int count = 0;
//int print = 0;
//
////This is to fix the problem of the timestamp getting to high and rolling over to 0
//alt_timestamp_type timestampFix;
///*---------------------------------------------------------
// MACROS
// ---------------------------------------------------------*/
///*---------------------------------------------------------
// PROCEDURES
// ---------------------------------------------------------*/
////Sets everything in the struct to zero
//void setZero(struct MCTPIDERR *pid) {
//    pid->preverr=0;
//    pid->err = 0;
//    pid->prevD = 0;
//    pid->prevI = 0;
//    pid->mark = alt_timestamp_start();
//    //If the timestamp is not available print this out
//    if (pid->mark < 0) {
//    	printf("No timestamp device available\n");
//    }
//}
//
////Initializes all structs by setting them to zero
//void initializeToZero(){
//	//Set all the errors to 0
//	setZero(&errAlt);
//	setZero(&errLat);
//	setZero(&errLong);
//	setZero(&errPitch);
//	setZero(&errYaw);
//	setZero(&errRoll);
//}
//
////The PID from the basestation
//int getCorrections(float *sigCor, float curAlt, float curLon, float curLat, float curPitch, float curRoll, float curDir, float targetDir, float targetAlt, float targetLat, float targetLon, float targetPitch, float targetRoll)
//{
//	count++;
//	float front = cos(curDir)*(targetLat-curLat) + sin(curDir)*(targetLon - curLon);
//	float side = -sin(curDir)*(targetLat-curLat) + cos(curDir)*(targetLon - curLon);
//	targetPitch = get_PID_correction( 0.0, front, &errLat, UAVLat);
//	print = 0;
//	targetRoll = get_PID_correction(0.0, side, &errLong, UAVLon);
//
//	sigCor[0] = get_PID_correction(curAlt, targetAlt , &errAlt, UAVAlt);
//    sigCor[1] = get_PID_correction(curPitch, targetPitch , &errPitch, UAVPitch);
//    sigCor[2] = get_PID_correction(curRoll, targetRoll , &errRoll, UAVRoll);
//    sigCor[3] = get_PID_correction(curDir, targetDir , &errYaw, UAVYaw);
//    return 1;
//}
//
////The PID stuff that was copied from the base station
//float get_PID_correction(float current, float target, struct MCTPIDERR *err, struct MCTPID pid)
//{
//    // check if there is new data
//    if( (target - current) == err->err) {
//        return err->correction;
//    } else {
//        float timeslice;
//        alt_timestamp_type now;
//        float p,i,d;
//        now = alt_timestamp();
//        //calculate timeslice in seconds
//        timeslice = (((float) (now + timestampFix - err->mark + 1) * 20)/ 1000000000);
//
//       //move all current to previous
//        err->mark = now;
//        err->preverr = err->err;
//        //caluclate new error and filtered error
//        err->err = target - current;
//
//        //calculate p term
//        p = pid.Kp * err->err;
//        //calculate i term
//        i = ( pid.Ki * timeslice * err->err ) + err->prevI;
//        err->prevI = i;
//        //calculate d term
//        d = ( ( pid.Kd * ( err->err - err->preverr ) ) + (pid.Kf * err->prevD) ) / (pid.Kf + timeslice);
//        err->prevD = d;
//        err->correction = ( p + i + d);
//        return err->correction;
//
//    }
//}
//
///*********************************************************
// * Title:               main
// *
// * Description:
// *      The entry point to the program
// *
// ********************************************************/
//int main()
//{
//	printf("Hello from jones III Control TEST Nios II");
//	//This is the data that we will read in
//	float data[18] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
//	//This is the pointer to the data that we read in
//	float *readInto = data;
//	//Lets us read in the data
//	char *byte_ptr = (char *) data;
//	/**
//	 * The current values of the quad
//	 * Are sent over from the camera system now, will eventually be GPS and Kalman filter
//	 */
//	//current altitude of the quad
//	float curPosAlt = 0;
//	//current latitude of the quad
//	float curPosLat = 0;
//	//current longitude of the quad
//	float curPosLon = 0;
//	//current pitch of the quad
//	float curPosPitch = 0;
//	//current roll of the quad
//	float curPosRoll = 0;
//	//current yaw of the quad
//	float curPosYaw = 0;
//	/**
//	 * The target values for the quad
//	 * Will be sent over from the base station
//	 */
//	//current direction of the quad
//	float targetDir = 0;
//	//target altitude for the quad
//	float targetPosAlt = 0;
//	//target latitude for the quad
//	float targetPosLat = 0;
//	//target longitude for the quad
//	float targetPosLon = 0;
//	//target pitch for the quad
//	float targetPitch = 0;
//	//target roll for the quad
//	float targetRoll = 0;
//	//If we are manually throttling what that value is
//	float manualThrottle = 0;
//	//whether we are manually throttling or automatically doing it
//	float autoThrottle = 1;
//
//	//0 is altitude error
//	//1 is pitch error
//	//2 is roll error
//	//3 is yaw error
//	//The error values that the PID finds
//	float sigCorArr[4] = {0, 0, 0 ,0};
//	//Pointer to the sigCorArr that we pass to functions
//	float *sigCorPtr = sigCorArr;
//	//The values that we are sending to the RC controller
//	int RCValuesArr[4] = {0, 0, 0, 0};
//	//Pointer to the RCValuesArr so we can pass to functions
//	int *RCValuesPtr = RCValuesArr;
//	//The throttle value
//	int thrtVal = 0;
//	//The pitch value
//	int pitchVal = 50;
//	//The roll value
//	int rollVal = 50;
//	//The yaw value
//	int yawVal = 50;
//	/**
//	 * The trim values may need to be set eventually
//	 */
//	//The throttle trim
//	float thrtTrim = 0;
//	//The pitch trim
//	float pitchTrim = 0;
//	//The roll trim
//	float rollTrim = 0;
//	//The yaw trim
//	float yawTrim = 0;
//	//whether this is the first time through the while loop
//	int firstTime = 1;
//
//	/**
//	 * Kalman Filter variables
//	 */
//	float phi;
//	float theta;
//	float psi;
//	float times;
//	//The time when we begin collecting the line
//	alt_timestamp_type kalmanBeginTime;
//	//The time when the line has been collected
//	alt_timestamp_type kalmanEndTime;
//
//
//	int numRead = 0;
//	int temp = 0;
//	int cnt = 0;
//
//	int fd;
//
//	//Constants that are given from the quadcopter testing, you can find them on the base station log file
//	UAVLat.Kd = -0.2;
//	UAVLat.Kf = 0;
//	UAVLat.Ki = 0;
//	UAVLat.Kp = -0.4;
//	UAVLat.Kt = 0;
//	UAVLon.Kd = 0.2;
//	UAVLon.Kf = 0;
//	UAVLon.Ki = 0;
//	UAVLon.Kp = 0.4;
//	UAVLon.Kt = 0;
//	UAVAlt.Kd = 139.332;
//	UAVAlt.Kf = 0.23608;
//	UAVAlt.Ki = 0.7777;
//	UAVAlt.Kp = 44.076;
//	UAVAlt.Kt = 0;
//	UAVPitch.Kd = 0;
//	UAVPitch.Kf = 0;
//	UAVPitch.Ki = 0;
//	UAVPitch.Kp = -251;
//	UAVPitch.Kt = 0;
//	UAVRoll.Kd = 0;
//	UAVRoll.Kf = 0;
//	UAVRoll.Ki = 0;
//	UAVRoll.Kp = 251;
//	UAVRoll.Kt = 0;
//	UAVYaw.Kd = 19.6;
//	UAVYaw.Kf = 0.468;
//	UAVYaw.Ki = 0;
//	UAVYaw.Kp = 408;
//	UAVYaw.Kt = 0;
//	FILE *fp; // File poiner to uart_0 phjones added
//
//	//Initialize the Kalman filter
//	//KALMANFILTER_init();
//
//	/**
//	 * Bluetooth stuff
//	 */
//	fp = fopen("/dev/uart_0", "r+"); // Open file for read and write
//	/*-------------------------------------------
//	 Set input to be nonblocking
//	 -------------------------------------------*/
//	fd = fileno(fp);
//	//fcntl(fd, F_SETFL, O_NONBLOCK);
//	if (fd != 0)
//	{
//		printf("opened!=%d\n\r", fd);
//	}
//	else
//	{
//		printf("NOT opened :-( \n\r");
//	}
//	initControls();
//
//	while (1)
//	{
//		/**
//		 * Get the starting time
//		 * If it is the first time, set the times to the begin time (times is used by the Kalman filter)
//		 */
//		kalmanBeginTime = alt_timestamp_start();
//		if(firstTime == 1)
//		{
//			times = (float)kalmanBeginTime;
//		}
//		//If the timestamp is not available print this out
//		if (kalmanBeginTime < 0)
//		{
//			printf("No timestamp device available\n");
//		}
//
//		/**
//		 * Read the 56 bytes that are being sent over bluetooth
//		*/
//
//		//Make sure that we have all the data (56 bytes of data)
//		/*
//		numRead = read(fd, byte_ptr, 56);
//		printf("after\n");
//
//		if(numRead == 56)
//		{
//			printf("complete\n");
//		}
//		else if(numRead == -1)
//		{
//			printf("-1\n");
//		}
//		else if(numRead == 0)
//		{
//			printf("0\n");
//		}
//		else
//		{
//			printf("incomplete\n");
//		}*/
//
//		/**/
//		printf("before\n");
//		temp = read(fd, byte_ptr, 1);
//		printf("after\n");
//
//		while (numRead < SIZE_OF_DATA_PACKET)
//		{
//			//blocks here until reads 1 byte
//			temp = read(fd, byte_ptr, 1);
//			if(temp == 1)
//			{
//				byte_ptr++;
//				numRead += temp;
//			}
//			else if(temp == -1)
//			{
//				fprintf(stderr, "read interrupted by signal\n");
//			}
//			else if(temp == 0)
//			{
//				fprintf(stderr, "end of file\n");
//			}
//			else
//			{
//				printf("UNKNOWN: may have read more than desired bytes\n");
//			}
//
//		}
//
//
//
//		//cnt = cnt + numRead;
//		/**
//		 * Do things once we have data from bluetooth
//		 */
//
//		if (numRead == SIZE_OF_DATA_PACKET)
//		{
//			//If we have not gotten here before initialize everything and set the firstTime
//			//variable to 0
//			if(firstTime == 1){
//				initializeToZero();
//				firstTime = 0;
//			}
//			//The timestampFix is so that we do not have a timestamp value of 0 when the counter rolls over
//			timestampFix = alt_timestamp();
//			//Start the timestamp
//			alt_timestamp_start();
//			//Set the values that were sent over
//			curPosAlt = data[0];
//			curPosLat = data[1];
//			curPosLon = data[2];
//			curPosPitch = data[3];
//			curPosRoll = data[4];
//			curPosYaw = data[5];
//			targetDir = data[6];
//			targetPosAlt = data[7];
//			targetPosLat = data[8];
//			targetPosLon = data[9];
//			targetPitch = data[10];
//			targetRoll = data[11];
//			manualThrottle = data[12];
//			autoThrottle = data[13];
//			readInto = data;
//			printf("VALUES RECIEVED\n\n CurPosAlt = %f\n CurPosLat = %f\n CurPosLon= %f\n CurPostPitch = %f\n CurPosRoll = %f\n CurPosYaw = %f\n TargetDir = %f\n TargetPosAlt = %f\n TargetPosLat = %f\n TargetPosLon = %f\n TargetPitch = %f\n TargetRoll = %f\n Manual Throttle = %f\n AutoThrottle = %f\n",curPosAlt,curPosLat,curPosLon,curPosPitch,curPosRoll,curPosYaw,targetDir, targetPosAlt, targetPosLat,targetPosLon,targetPitch,targetRoll,manualThrottle,autoThrottle);
//
//			/**
//			 * Get the values from the IMU and send them through the Kalman filter
//			 */
//			readUsefulIMU();
//			//KALMANFILTER_update(times, currentHeliState.gyroX, currentHeliState.gyroY, currentHeliState.gyroZ, currentHeliState.accelX, currentHeliState.accelY, currentHeliState.accelZ);
//			//phi is roll
//			//theta is pitch
//			//psi is yaw
//			//KALMANFILTER_getData(&phi, &theta, &psi);
//
//			/**
//			 * Go through the PID with the values that the Kalman filter gives us
//			 */
//			//getCorrections(sigCorPtr, curPosAlt, curPosLon, curPosLat, theta, phi, psi, targetDir, targetPosAlt, targetPosLat, targetPosLon, targetPitch, targetRoll);
//			getCorrections(sigCorPtr, curPosAlt, curPosLon, curPosLat, curPosPitch, curPosRoll, curPosYaw, targetDir, targetPosAlt, targetPosLat, targetPosLon, targetPitch, targetRoll);
//
//			//If we are using auto throttle
//			if(autoThrottle != 0)
//			{
//				thrtVal = thrtVal + (sigCorArr[0] / 6.0);
//			}
//
//			//If we are using manual throttle just set it to what the manual throttle is
//			else
//			{
//				thrtVal = manualThrottle;
//			}
//
//			/**
//			 * Adjust the values as we need to, got this from the base station code
//			 */
//
//			pitchVal = 50 + (sigCorArr[1] / 7.0);
//			rollVal = 50 + (sigCorArr[2] / 7.0);
//			yawVal = 50 + (sigCorArr[3] / 7.0);
//
//			/**
//			 * Make sure that no values are less than 0 or greater than 100
//			 */
//
//			if(thrtVal < 0){
//				thrtVal = 0;
//			}
//			if(thrtVal > 100){
//				thrtVal = 100;
//			}
//			if(pitchVal < 0){
//				pitchVal = 0;
//			}
//			if(pitchVal > 100){
//				pitchVal = 100;
//			}
//			if(rollVal < 0){
//				rollVal = 0;
//			}
//			if(rollVal > 100){
//				rollVal = 100;
//			}
//			if(yawVal < 0){
//				yawVal = 0;
//			}
//			if(yawVal > 100){
//				yawVal = 100;
//			}
//
//			/**
//			 * Set the values that we are going to set the motors to
//			 */
//			RCValuesArr[0] = (thrtVal + thrtTrim);
//			RCValuesArr[1] = (pitchVal + pitchTrim);
//			RCValuesArr[2] = (rollVal + rollTrim);
//			RCValuesArr[3] = (yawVal + yawTrim);
//			//Write the values back to bluetooth so we can check them
//			//TODO Get rid of this when you are confident in the code
//			//fwrite(RCValuesPtr, 4* sizeof (int), 1, fp);
//			/**
//			 * Set the motor values to their perspective values
//			 */
//			//TODO Uncomment this once things are working
//
//			setThrottle(RCValuesArr[0]);
//			setAileron(RCValuesArr[2]);
//			setElevator(RCValuesArr[1]);
//			setRudder(RCValuesArr[3]);
//
//			/*
//			//For right now it sends back the values that we are checking to the basestation
//			RCValuesArr[0] = currentHeliState.gyroX;
//			RCValuesArr[1] = currentHeliState.gyroY;
//			RCValuesArr[2] = currentHeliState.gyroZ;
//			RCValuesArr[3] = currentHeliState.accelX;
//			RCValuesArr[4] = currentHeliState.accelY;
//			RCValuesArr[5] = currentHeliState.accelZ;
//			RCValuesArr[6] = phi;
//			RCValuesArr[7] = theta;
//			RCValuesArr[8] = psi;
//			printf("%f \t %f \t %f \n", phi, theta, psi);
//			//Write the values to bluetooth
//			fwrite(RCValuesPtr, 9* sizeof (float), 1, fp);
//			*/
//			/**
//			 * Reset the number of bytes that we are reading
//			 */
//			numRead = 0;
//			cnt = 0;
//			//End the timestamp to get the end time
//			kalmanEndTime = alt_timestamp();
//			//The timestamp is taken in ms
//			times = (((float) (kalmanEndTime+timestampFix - kalmanBeginTime) * 20)/ 1000000);
//			numRead = 0;
//			byte_ptr = (char *) data;
//
//		}
//		else
//		{
//			fprintf(stderr, "number bytes read is not the correct size of data packet\n");
//		}
//	}
//
//	return 0;
//}
