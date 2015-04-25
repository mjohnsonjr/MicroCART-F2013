/*---------------------------------------------------------
 File: barebones_main.c

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
#include <sys/termios.h>
#include <sys/ioctl.h>
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

int main()
{

    printf("Hello from luke's barebones main.  it works on other pc, why would this be any different?\n\r");
    char readBuffer[2];
    //This is the data that we will read in
    float data[18] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    //This is the pointer to the data that we read in
    float *readInto = data;
    //Lets us read in the data
    char *byte_ptr = (char *) data;
    /**
     * The current values of the quad
     * Are sent over from the camera system now, will eventually be GPS and Kalman filter
     */
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

    int numRead = 0;
    int temp = 0;
    FILE *fp;
    int fd;
    unsigned wantData = 0;
    char startbyte;
    /**
    	 * Bluetooth stuff
    	 */
    	//fp = fopen("/dev/uart_0", "r+"); // Open file for read and write

    	/*-------------------------------------------
    	 Set input to be nonblocking
    	 -------------------------------------------*/
    	//fd = fileno(fp);
		fd = open( "/dev/uart_0", O_RDWR | O_NONBLOCK | O_NOCTTY );
		//fcntl(fd, F_SETFL, O_NONBLOCK);

    	//MIKE TESTING
//    	struct termios options;
//    	int res = 0;
//
//    	res= ioctl(fd,TIOCMGET,&options);
//    	if(res<0) {
//    	printf("ERROR ioctl res:%d\r\n",res);
//    	return 0;
//    	}
//
//    	options.c_ospeed = 57600;
//    	options.c_ispeed = 57600;
//        cfsetispeed(&options, B57600);
//        cfsetospeed(&options, B57600);
//        options.c_cflag |= (CLOCAL | CREAD);
//        options.c_cflag &= ~CSIZE;
//        options.c_cflag |= CS8;
//        options.c_cflag &= ~PARENB;
//        options.c_cflag &= ~CSTOPB;
//        options.c_cflag &= ~CSIZE;
//        options.c_cflag |= CS8;
//        options.c_cflag &= ~CRTSCTS;
//        options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
//        options.c_oflag &= ~OPOST;
//    	res=ioctl(fd,TIOCMSET,&options);
//    	if(res<0) {
//    	printf("ERROR2 ioctl res:%d\r\n",res);
//    	return 0;
//   	}
   	//END MIKE TESTING.  Added: ALTERA_AVALON_UART_USE_IOCTL


//    	if (fd != 0)
//    	{
//    		printf("opened!=%d, baud: %d\n\r", fd, options.c_ispeed);
//    	}
//    	else
//    	{
//    		printf("NOT opened :-( \n\r");
//    	}
//    	while((numRead=read(fd, byte_ptr, 1)) != 0){
//    	                printf("clearing");
//    	                read(fd, byte_ptr, 1);
//    	}

    while(1)
    {
        /*-------------------------------------------
        Nonblocking read: returns 0 if nothing there
        -------------------------------------------*/
        //printf("Numread = %i",numRead);
        /**
         * Read the 56 bytes that are being sent over bluetooth
        */

    	while(wantData == 0){

        	startbyte = read(fd,readBuffer,1);

        	if(startbyte > 0){
        		//printf("SpeedI: %d SpeedO: %d", options.c_ispeed, options.c_ospeed);
        		if(readBuffer[0] == -1){
        			printf("Read Start Byte.");
        			wantData = 1;
        		}
        	}
    	}

		//Make sure that we have all the data (56 bytes of data)
    	while (numRead < SIZE_OF_DATA_PACKET) {
    		temp = read(fd, byte_ptr, 1);

			if (temp > 0) {
				numRead = numRead + temp;
				byte_ptr=byte_ptr+temp;
			}
		}

        if (numRead == SIZE_OF_DATA_PACKET)
        {
            //Set the values that were sent over
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
            readInto = data;
            printf("VALUES RECIEVED\n\n CurPosAlt = %f\n CurPosLat = %f\n CurPosLon= %f\n CurPostPitch = %f\n CurPosRoll = %f\n CurPosYaw = %f\n TargetDir = %f\n TargetPosAlt = %f\n TargetPosLat = %f\n TargetPosLon = %f\n TargetPitch = %f\n TargetRoll = %f\n Manual Throttle = %f\n AutoThrottle = %f\n",curPosAlt,curPosLat,curPosLon,curPosPitch,curPosRoll,curPosYaw,targetDir, targetPosAlt, targetPosLat,targetPosLon,targetPitch,targetRoll,manualThrottle,autoThrottle);


            /**
             * Reset the number of bytes that we are reading
             */
            numRead = 0;
            wantData = 0;
            /**
            *Read from buffer(?) until it returns zero, then reset vars and wait for the next packet
            **/
            byte_ptr = (char *) data;

        }
            /*while((numRead=read(fd, byte_ptr, 1)) != 0){
                printf("clearing");
                read(fd, byte_ptr, 1);
            }
            numRead = 0;
            byte_ptr = (char *) data;*/


    }

    while (1);

    return 0;
}
