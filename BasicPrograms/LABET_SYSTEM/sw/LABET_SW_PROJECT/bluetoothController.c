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

int fd;
int print=0,count=0;
unsigned firstSample = 1;
//This is the data that we will read in
float data[15] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0};
//This is to fix the problem of the timestamp getting to high and rolling over to 0
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
	//hold accelerometer, gyro, and mag values
	int numRead = 0;
	int temp = 0;
	unsigned wantData = 0;
	char startbyte;
	int fd;

	/* Last 2 bytes after packet in transmission */
	unsigned short crccheck;

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
			timestampFix = alt_timestamp();
			startbyte = read(fd,readBuffer,1);

			if(startbyte > 0){
				if(readBuffer[0] == -1){
					//printf("Read Start Byte.");
					wantData = 1;
					break;
				}
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
				continue;
			}
			//assign data from basestation
			curPosAlt = data[0];
			curPosLat = data[1];
			curPosLon = data[2];
			curPosPitch = data[3];
			curPosRoll = data[4];
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
			if(manualControl == 1){
				setThrottle(manualThrottle);
				setAileron(targetRoll);
				setElevator(100-targetPitch);
				setRudder(targetDir);
			}
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
