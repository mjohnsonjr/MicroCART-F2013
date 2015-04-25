/*
 * gps_tests.c
 *
 *  Created on: Mar 8, 2014
 *      Author: ucart
 */
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
#define SIZE_OF_DATA_PACKET 56


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
int count = 0;
int print = 0;

//This is to fix the problem of the timestamp getting to high and rolling over to 0
alt_timestamp_type timestampFix;
/*---------------------------------------------------------
 MACROS
 ---------------------------------------------------------*/
/*---------------------------------------------------------
 PROCEDURES
 ---------------------------------------------------------*/



/*********************************************************
 * Title:               main
 *
 * Description:
 *      The entry point to the program
 *
 ********************************************************/
int main()
{
	printf("Hello TEST \n");

	char numBytes = 0;
	char gpsChar = 0;
	FILE* fp; //file pointer to uart_0 (added by jones) (c abstraction)
	int fd; //file descriptor to uarto_0 (unix level)



	/**
	 * Bluetooth stuff
	 */
	fp = fopen("/dev/uart_0", "r+"); // Open file for read and write
	/*-------------------------------------------
	 Set input to be nonblocking
	 -------------------------------------------*/
	fd = fileno(fp);
	fcntl(fd, F_SETFL, O_NONBLOCK);

	//change baud rate can be done in altera_avalon_uart_regs.h - divisor reg or through software altera_avalon_uart.h --> define ALTERA_AVALON_UART_USE_IOCTL
	//ioctl(fd, );

	if (fd != 0)
	{
		printf("opened!=%d\n\r", fd);
	}
	else
	{
		printf("NOT opened :-( \n\r");
	}
	initControls();

	while (1)
	{
		//read UART for GPS stream
		numBytes = read(fd,gpsChar,1);

		if(numBytes > 0){
		    printf("%c", gpsChar );
		}

		//Parse GPS stream of characters (NMEA protocol)

	}

	while (1);

	return 0;
}

