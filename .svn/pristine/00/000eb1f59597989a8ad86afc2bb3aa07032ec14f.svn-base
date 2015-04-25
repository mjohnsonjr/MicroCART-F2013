/*---------------------------------------------------------
 File: labet_main_kalman.c

 Procedures:
 - main
 - PredictAccG_pitch
 - PredictAccG_roll
 --------------------------------------------------------*/

/*---------------------------------------------------------
 INCLUDES
 ---------------------------------------------------------*/
#include <system.h>
#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>
#include <stddef.h>
#include <fcntl.h>
#include <stdio.h>
#include <math.h>
#include <sys/alt_timestamp.h>
#include <alt_types.h>
#include <sys/time.h>
#include "hello_world.h"
#include "labet.h"
#include "imu.h"
#include "ars.h"
#include "ping.h"
#include "controls.h"
//#include "attitude.h"


//#include "kalmanfilter.h"
/*---------------------------------------------------------
 DEFINITIONS
 ---------------------------------------------------------*/

/*---------------------------------------------------------
 TYPES
 ---------------------------------------------------------*/

/*---------------------------------------------------------
 GLOBAL VARIABLES
 ---------------------------------------------------------*/
struct MCTPIDERR errLat;
struct MCTPIDERR errLong;
struct MCTPIDERR errAlt;
struct MCTPIDERR errPitch;
struct MCTPIDERR errRoll;
struct MCTPIDERR errYaw;
struct MCTPID UAVLat;
struct MCTPID UAVLon;
struct MCTPID UAVAlt;
struct MCTPID UAVPitch;
struct MCTPID UAVRoll;
struct MCTPID UAVYaw;
//Notation "w" stands for one of the axes, so for example RwAcc[0],RwAcc[1],RwAcc[2] means RxAcc,RyAcc,RzAcc
//Variables below must be global (their previous value is used in getEstimatedInclination)
float RwEst[3];     //Rw estimated from combining RwAcc and RwGyro
unsigned long lastMicros;

//Variables below don't need to be global but we expose them for debug purposes
unsigned long interval; //interval since previous analog samples
float RwAcc[3];         //projection of normalized gravitation force vector on x/y/z axis, as measured by accelerometer
float RwGyro[3];        //Rw obtained from last estimated value and gyro movement
float theta=0.0, phi=0.0,yaw=0.0;
float Awz[2];           //angles between projection of R on XZ/YZ plane and Z axis (deg)
int fd;
int print=0,count=0;
unsigned firstSample = 1;
//This is the data that we will read in
float data[15] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0};
//This is to fix the problem of the timestamp getting too high and rolling over to 0
alt_timestamp_type timestampFix;
//current altitude of the quad
float curPosAlt = 0;
//current latitude of the quad
float curPosLat = 0;
//current longitude of the quad
float curPosLon = 0;
//current pitch of the quad
float curPosPitch = 0;
//current roll of the quad
float curPosRoll = 0;
//current yaw of the quad
float curPosYaw = 0;
/**
 * The target values for the quad
 * Will be sent over from the base station
 */
//current direction of the quad
float targetDir = 0;
//target altitude for the quad
float targetPosAlt = 0;
//target latitude for the quad
float targetPosLat = 0;
//target longitude for the quad
float targetPosLon = 0;
//target pitch for the quad
float targetPitch = 0;
//target roll for the quad
float targetRoll = 0;
//If we are manually throttling what that value is
float manualThrottle = 0;
//whether we are manually throttling or automatically doing it
float autoThrottle = 1;
float manualControl = 0;
/*---------------------------------------------------------
 MACROS
 ---------------------------------------------------------*/

/*---------------------------------------------------------
 PROCEDURES
 ---------------------------------------------------------*/
/*---------------------------------------------------------
 DEFINITIONS
 ---------------------------------------------------------*/
#define SIZE_OF_DATA_PACKET 60
#define VDD 3330.0f       //Analog reference voltage in milivolts
/*---------------------------------------------------------
 TYPES
 ---------------------------------------------------------*/

//Sets everything in the struct to zero
void setZero(struct MCTPIDERR *pid) {
    pid->preverr=0;
    pid->err = 0;
    pid->prevD = 0;
    pid->prevI = 0;
    pid->mark = alt_timestamp_start();
    //If the timestamp is not available print this out
    if (pid->mark < 0) {
    	printf("No timestamp device available\n");
    }
}
/*
 * Convert IMU data to useful units
 */
float convert(alt_16 data, int type){
	switch(type){
		//Convert gyro data to degrees per second
		case 1:
			return (float)data/20.0;
		//Convert accel data to ???
		case 2:
			return (float)data * (3.33/1000.0);
		//Convert magnetometer data to ??
		case 3:
			return (float)data/2000.0;
		//Convert gyro data to radians per second
		case 4:
			return (float)data/20.0 * (3.1416/180);
	}
	//failure
	return 1000.0;
}
//Initializes all structs by setting them to zero
void initializeToZero(){
	//Set all the errors to 0
	setZero(&errAlt);
	setZero(&errLat);
	setZero(&errLong);
	setZero(&errPitch);
	setZero(&errYaw);
	setZero(&errRoll);
}

//The PID from the basestation
int getCorrections(float *sigCor, float curAlt, float curLon, float curLat, float curPitch, float curRoll, float curDir, float targetDir, float targetAlt, float targetLat, float targetLon, float targetPitch, float targetRoll)
{
	count++;
	float front = cos(curDir)*(targetLat-curLat) + sin(curDir)*(targetLon - curLon);
	float side = -sin(curDir)*(targetLat-curLat) + cos(curDir)*(targetLon - curLon);
	targetPitch = get_PID_correction( 0.0, front, &errLat, UAVLat);
	print = 0;
	targetRoll = get_PID_correction(0.0, side, &errLong, UAVLon);
	sigCor[0] = get_PID_correction(curAlt, targetAlt , &errAlt, UAVAlt);
    sigCor[1] = get_PID_correction(curPitch, targetPitch , &errPitch, UAVPitch);
    sigCor[2] = get_PID_correction(curRoll, targetRoll , &errRoll, UAVRoll);
    printf("\nPitch Correction: %f    Roll Correction: %f",sigCor[1],sigCor[2]);
    sigCor[3] = get_PID_correction(curDir, targetDir , &errYaw, UAVYaw);
    return 1;
}

//The PID stuff that was copied from the base station
float get_PID_correction(float current, float target, struct MCTPIDERR *err, struct MCTPID pid)
{
    // check if there is new data
    if( (target - current) == err->err) {
        return err->correction;
    } else {
        double timeslice;
        alt_timestamp_type now;
        float p,i,d;
        now = alt_timestamp();
        //calculate timeslice in seconds
        if(now < err->mark){
        	err->mark = now;
        	return err->correction;
        }
        timeslice = (double) (now - err->mark + 1);
       //move all current to previous
        err->mark = now;
        err->preverr = err->err;
        //caluclate new error and filtered error
        err->err = target - current;

        //calculate p term
        p = pid.Kp * err->err;
        //calculate i term
        i = ( pid.Ki * timeslice * err->err ) + err->prevI;
        err->prevI = i;
        //calculate d term
        d = ( ( pid.Kd * ( err->err - err->preverr ) ) + (pid.Kf * err->prevD) ) / (pid.Kf + timeslice);
        err->prevD = d;
        err->correction = ( p + i + d);
        return err->correction;

    }
}

/* CHECK THE CRC TO ENSURE DATA PACKET IS VALID
 * LOTS OF ISSUES WITH PACKET VALIDITY IN 13-14 BE WARNED.
 * ALL IS STABLE WITH THE CURRENT SET UP OF 19200 BAUD RATE AND THIS CRC CHECK
 * POTENTIALLY REPLACE THIS WITH SOMETHING MORE LIGHTWEIGHT, MAY BE OVERKILL*/
unsigned short CRC(const char* message, int numbytes, unsigned short crccheck)
{
	unsigned short crc = 0xFFFF;
	short i = 0, j = 0;

	for(i = 0; i < numbytes; i++)
	{
		crc = (crc ^ (message[i] << 8));
		for(j = 1; j <= 8; j++)
		{
			if(crc & (0x8000)){
				 crc = (crc << 1) ^ 0x1021; //poly
			}
			else{
				crc = (crc << 1);
			}
		}
	}
	return crc ^ crccheck;
}



void normalize3DVector(float* vector){
  static float R;
  R = sqrt(vector[0]*vector[0] + vector[1]*vector[1] + vector[2]*vector[2]);
  vector[0] /= R;
  vector[1] /= R;
  vector[2] /= R;
}

float squared(float x){
  return x*x;
}
/*********************************************************
 * Title:               main
 *
 * Description:
 *      The entry point to the program
 *
 ********************************************************/
int main()
{
	//printf("Hello from jones III Control TEST Nios II");
	//This is the data that we will read in
	//This is the pointer to the data that we read in
	float *readInto = data;
	//Lets us read in the data
	char *byte_ptr = (char *) data;
	char readBuffer[2];
	/**
	 * The current values of the quad
	 * Are sent over from the camera system now, will eventually be GPS and Kalman filter
	 */


	//0 is altitude error
	//1 is pitch error
	//2 is roll error
	//3 is yaw error
	//The error values that the PID finds
	float sigCorArr[4] = {0, 0, 0 ,0};
	//Pointer to the sigCorArr that we pass to functions
	float *sigCorPtr = sigCorArr;
	//The values that we are sending to the RC controller
	int RCValuesArr[4] = {0, 0, 0, 0};
	//Pointer to the RCValuesArr so we can pass to functions
	int *RCValuesPtr = RCValuesArr;
	//The throttle value
	int thrtVal = 0;
	//The pitch value
	int pitchVal = 50;
	//The roll value
	int rollVal = 50;
	//The yaw value
	int yawVal = 50;
	/**
	 * The trim values may need to be set eventually
	 */
	//The throttle trim
	float thrtTrim = 0;
	//The pitch trim
	float pitchTrim = 0;
	//The roll trim
	float rollTrim = 0;
	//The yaw trim
	float yawTrim = 0;
	//whether this is the first time through the while loop
	int firstTime = 1;
	int numRead = 0;
	int temp = 0;
	unsigned wantData = 0;
	char startbyte;
	int fd;

	/* Last 2 bytes after packet in transmission */
	unsigned short crccheck;

	//Constants that are given from the quadcopter testing, you can find them on the base station log file
	UAVLat.Kd = -1.5;
	UAVLat.Kf = 0;
	UAVLat.Ki = 0;
	UAVLat.Kp = -0.7;
	UAVLat.Kt = 0;
	UAVLon.Kd = 1.5;
	UAVLon.Kf = 0;
	UAVLon.Ki = 0;
	UAVLon.Kp = 0.7;
	UAVLon.Kt = 0;
	UAVAlt.Kd = 139.3324;
	UAVAlt.Kf = 0.23608;
	UAVAlt.Ki = 0.7777;
	UAVAlt.Kp = 44.076;
	UAVAlt.Kt = 0;
	UAVPitch.Kd = 0;
	UAVPitch.Kf = 0;
	UAVPitch.Ki = 0;
	UAVPitch.Kp = -251;
	UAVPitch.Kt = 0;
	UAVRoll.Kd = 0;
	UAVRoll.Kf = 0;
	UAVRoll.Ki = 0;
	UAVRoll.Kp = 251;
	UAVRoll.Kt = 0;
	UAVYaw.Kd = 21;
	UAVYaw.Kf = 0.468;
	UAVYaw.Ki = 0;
	UAVYaw.Kp = 408;
	UAVYaw.Kt = 0;
	FILE *fp; // File poiner to uart_0 phjones added


	/**
	 * Bluetooth stuff
	 */
	fp = fopen("/dev/uart_0", "r+"); // Open file for read and write
	/*-------------------------------------------
	 Set input to be nonblocking
	 -------------------------------------------*/
	fd = fileno(fp);
	fcntl(fd, F_SETFL, O_NONBLOCK);
	if (fd != 0)
	{
		//printf("opened!=%d\n\r", fd);
	}
	else
	{
		printf("NOT opened :-( \n\r");
	}
	initControls();
	while (1)
	{

		while(wantData == 0){
			//Start the timestamp
			alt_timestamp_start();
			//The timestampFix is so that we do not have a timestamp value of 0 when the counter rolls over
			timestampFix = 1;//alt_timestamp();
			startbyte = read(fd,readBuffer,1);

			if(startbyte > 0){
				if(readBuffer[0] == -1){
					//printf("Read Start Byte.");
					wantData = 1;
					break;
				}
			}
			getEstimatedInclination();
			if(manualControl){
				setThrottle(manualThrottle);
				setAileron(targetRoll);
				setElevator(targetPitch);
				setRudder(targetDir);
			}
			else{
				getCorrections(sigCorPtr, curPosAlt, curPosLon, curPosLat, curPosPitch, curPosRoll, curPosYaw, targetDir, curPosAlt, curPosLat,curPosLon, targetPitch, targetRoll);
				//printf("\n\n CurPosAlt = %f\n CurPosLat = %f\n CurPosLon= %f\n CurPostPitch = %f\n CurPosRoll = %f\n CurPosYaw = %f\n TargetDir = %f\n TargetPosAlt = %f\n TargetPosLat = %f\n TargetPosLon = %f\n TargetPitch = %f\n TargetRoll = %f\n Manual Throttle = %f\n AutoThrottle = %f\n ManualControl = %f\n",curPosAlt,curPosLat,curPosLon,curPosPitch,curPosRoll,curPosYaw,targetDir, targetPosAlt, targetPosLat,targetPosLon,targetPitch,targetRoll,manualThrottle,autoThrottle,manualControl);
				//printf("\nPitch: %f Roll: %f",curPosPitch, curPosRoll);
				//If we are using auto throttle
				if(autoThrottle != 0){
					thrtVal = thrtVal + (sigCorArr[0] / 6.0);
				}
				//If we are using manual throttle just set it to what the manual throttle is
				else{
					thrtVal = manualThrottle;
				}

				/**
				 * Adjust the values as we need to, got this from the base station code
				 */

				pitchVal = 50 + (sigCorArr[1] / 7.0);
				rollVal = 50 + (sigCorArr[2] / 7.0);
				yawVal = 50 + (sigCorArr[3] / 7.0);

				/**
				 * Make sure that no values are less than 0 or greater than 100
				 */

				if(thrtVal < 0){
					thrtVal = 0;
				}
				if(thrtVal > 100){
					thrtVal = 100;
				}
				if(pitchVal < 0){
					pitchVal = 0;
				}
				if(pitchVal > 100){
					pitchVal = 100;
				}
				if(rollVal < 0){
					rollVal = 0;
				}
				if(rollVal > 100){
					rollVal = 100;
				}
				if(yawVal < 0){
					yawVal = 0;
				}
				if(yawVal > 100){
					yawVal = 100;
				}

				/**
				 * Set the values that we are going to set the motors to
				 */
				RCValuesArr[0] = (thrtVal + thrtTrim);
				RCValuesArr[1] = (pitchVal + pitchTrim);
				RCValuesArr[2] = (rollVal + rollTrim);
				RCValuesArr[3] = (yawVal + yawTrim);
				//Write the values back to bluetooth so we can check them
				//TODO Get rid of this when you are confident in the code
				//fwrite(RCValuesPtr, 4* sizeof (int), 1, fp);
				/**
				 * Set the motor values to their perspective values
				 */
				printf("\n throttle:%i     \n rollVal + rollTrim(aileron):%i     \n ", RCValuesArr[0],RCValuesArr[2]);
				setThrottle(RCValuesArr[0]);
				setAileron(RCValuesArr[2]);
				setElevator(RCValuesArr[1]);
				setRudder(RCValuesArr[3]);
			}
		}
		/* Now start reading the packet */
    	while (numRead < SIZE_OF_DATA_PACKET) {
    		temp = read(fd, byte_ptr, 1);

			if (temp > 0) {
				numRead = numRead + temp;
				byte_ptr=byte_ptr+temp;
			}
		}

    	/* We have the whole packet, now the CRC, and timestamp.
    	 * If both check out, we can use this data. */
		while (numRead == SIZE_OF_DATA_PACKET)
		{
			//If we have not gotten here before initialize everything and set the firstTime
			//variable to 0
			if(firstTime == 1){
				initializeToZero();
				firstTime = 0;
			}


			/* READ THE CRC (last 2 bytes) */
			temp = 0;
			while(temp < 2){
				temp += read(fd, ((void*)&crccheck) + temp, 1);
				if(temp == -1)
				{
					break;
				}
			}

			/* CHECK THE CRC, ensure data integrity. */
			//printf("CRC CHECKSUM READ: %x\n", crccheck);
			crccheck = CRC((char*)readInto, SIZE_OF_DATA_PACKET, crccheck);
			//printf("REMAINDER CALCULATED: %x\n", crccheck);

			/* Check data integrity, break loop if garbage */
			if(crccheck != 0){
				printf("CRC bad: %x\n", crccheck);
				numRead = 0;
				wantData = 0;
				byte_ptr = (char *) data;
				break;
			}
			//assign data from basestation
			curPosAlt = data[0];
			curPosLat = data[1];
			curPosLon = data[2];
			//curPosPitch = data[3];
			//curPosRoll = data[4];
			curPosYaw = data[5];
			targetDir = data[6];
			targetPosAlt = data[7];
			targetPosLat = data[8];
			targetPosLon = data[9];
			targetPitch = data[10];
			targetRoll = data[11];
			manualThrottle = data[12];
			autoThrottle = data[13];
			manualControl = data[14];
			readInto = data;
			//printf("VALUES RECIEVED\n\n CurPosAlt = %f\n CurPosLat = %f\n CurPosLon= %f\n CurPostPitch = %f\n CurPosRoll = %f\n CurPosYaw = %f\n TargetDir = %f\n TargetPosAlt = %f\n TargetPosLat = %f\n TargetPosLon = %f\n TargetPitch = %f\n TargetRoll = %f\n Manual Throttle = %f\n AutoThrottle = %f\n ManualControl = %f\n",curPosAlt,curPosLat,curPosLon,curPosPitch,curPosRoll,curPosYaw,targetDir, targetPosAlt, targetPosLat,targetPosLon,targetPitch,targetRoll,manualThrottle,autoThrottle,manualControl);
			/**
			 * END LOOP RESETS
			 */
			wantData = 0;
			byte_ptr = (char *) data;
			numRead = 0;
		}
	}

	while (1);

	return 0;
}


void getEstimatedInclination(){
  static int w;
  static float tmpf,tmpf2;
  static char signRzGyro;
  //get raw adc readings
  alt_timestamp_start();
  alt_timestamp_type currentT = alt_timestamp();//save the time when sample is taken
  alt_timestamp_type previousT;
  readUsefulIMU();
  //compute interval since last sampling time
  interval = currentT - previousT;    //please note that overflows are ok, since for example 0x0001 - 0x00FE will be equal to 2
  previousT = currentT;               //save for next loop, please note interval will be invalid in first sample but we don't use it


  //get accelerometer readings in g, gives us RwAcc vector
  //Convert ADC value for to physical units see http://starlino.com/imu_guide.html for explanation.
  //For accelerometer it will return  g  (acceleration) , applies when  xyz = 0..2
  //For gyro it will return  deg/ms (rate of rotation)  , applies when xyz = 3..5
  tmpf = currentHeliState.accelX * VDD / 1023.0f;  //voltage (mV)
  tmpf -= 0;  //voltage relative to zero level (mV)
  tmpf /= 400;   //input sensitivity in mV/G(acc) or mV/deg/ms(gyro)
  tmpf *= 1;  //invert axis value according to configuration
  RwAcc[0] = tmpf;
  tmpf = currentHeliState.accelY * VDD / 1023.0f;  //voltage (mV)
  tmpf -= 0;  //voltage relative to zero level (mV)
  tmpf /= 400;    //input sensitivity in mV/G(acc) or mV/deg/ms(gyro)
  tmpf *= 1;  //invert axis value according to configuration
  RwAcc[1] = tmpf;
  tmpf = currentHeliState.accelZ * VDD / 1023.0f;  //voltage (mV)
  tmpf -= 0;  //voltage relative to zero level (mV)
  tmpf /= 400;    //input sensitivity in mV/G(acc) or mV/deg/ms(gyro)
  tmpf *= 1;  //invert axis value according to configuration
  RwAcc[2] = tmpf;


  //normalize vector (convert to a vector with same direction and with length 1)
  normalize3DVector(RwAcc);

  if (firstSample){
    for(w=0;w<=2;w++) RwEst[w] = RwAcc[w];    //initialize with accelerometer readings
  }else{
    //evaluate RwGyro vector
    if(abs(RwEst[2]) < 0.1){
      //Rz is too small and because it is used as reference for computing Axz, Ayz it's error fluctuations will amplify leading to bad results
      //in this case skip the gyro data and just use previous estimate
      for(w=0;w<=2;w++) RwGyro[w] = RwEst[w];
    }else{
      //get angles between projection of R on ZX/ZY plane and Z axis, based on last RwEst
	  tmpf2 = currentHeliState.gyroX;                         //get current gyro rate in deg/ms
	  tmpf2 *= interval / 1000.0f;                     //get angle change in deg
	  Awz[0] = atan2(RwEst[0],RwEst[2]) * 180 / PI;   //get angle and convert to degrees
	  Awz[0] += tmpf;                                 //get updated angle according to gyro movement
	  tmpf2 = currentHeliState.gyroY;                         //get current gyro rate in deg/ms
	  tmpf2 *= interval / 1000.0f;                     //get angle change in deg
	  Awz[1] = atan2(RwEst[1],RwEst[2]) * 180 / PI;   //get angle and convert to degrees
      Awz[1] += tmpf;                                 //get updated angle according to gyro movement

      //estimate sign of RzGyro by looking in what qudrant the angle Axz is,
      //RzGyro is pozitive if  Axz in range -90 ..90 => cos(Awz) >= 0
      signRzGyro = ( cos(Awz[0] * PI / 180) >=0 ) ? 1 : -1;

      //reverse calculation of RwGyro from Awz angles, for formulas deductions see  http://starlino.com/imu_guide.html
      for(w=0;w<=1;w++){
        RwGyro[0] = sin(Awz[0] * PI / 180);
        RwGyro[0] /= sqrt( 1 + squared(cos(Awz[0] * PI / 180)) * squared(tan(Awz[1] * PI / 180)) );
        RwGyro[1] = sin(Awz[1] * PI / 180);
        RwGyro[1] /= sqrt( 1 + squared(cos(Awz[1] * PI / 180)) * squared(tan(Awz[0] * PI / 180)) );
      }
      RwGyro[2] = signRzGyro * sqrt(1 - squared(RwGyro[0]) - squared(RwGyro[1]));
    }

    //combine Accelerometer and gyro readings        readUsefulIMU();

    for(w=0;w<=2;w++) RwEst[w] = (RwAcc[w] + 10* RwGyro[w]) / (1 + 10);
    normalize3DVector(RwEst);
    //RwEst[0] = atan2(RwEst[0],RwEst[2]);
    //RwEst[1] = atan2(RwEst[1],(squared(RwEst[2])+squared(RwEst[0]))/sqrt(squared(RwEst[2])+squared(RwEst[0])));
    //RwEst[2] = atan2(RwEst[0],RwEst[1]);
    curPosPitch = -atan(RwEst[0]/sqrt(squared(RwEst[1]) + squared(RwEst[2])));
    curPosRoll =atan(RwEst[1]/sqrt(squared(RwEst[0]) + squared(RwEst[2])));
    //curPosYaw = atan(RwEst[2]/sqrt(squared(RwEst[0]) + squared(RwEst[1])));

    //printf("\nRoll:%f  Pitch:%f Yaw:%f",theta, phi,yaw);

  }

  firstSample = 0;
}
