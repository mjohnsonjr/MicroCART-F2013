/*
 * Transmitter.cpp
 *
 *  Created on: Jan 30, 2014
 *      Author: Michael Johnson
 */

#include "Transmitter.h"
#include "QuadCommand.h"
#include <sys/fcntl.h> /* File control definitions */
#include <sys/termios.h>
#include <termios.h> /* POSIX terminal control definitions */
#include <unistd.h> /* UNIX standard function definitions */
#include <cstdlib>
#include <string>
#include <cerrno> /* Error number definitions */
#include <cstdio>
#include <string>
#include <iostream>


namespace{

	/* Finds the CRC of the entire packet.  It's appended to the end as a float(casted
	 * from an unsigned short).  On the quad, read this and cast it back before running it
	 * through this function.  If the data is correct, the return value should be exactly 0.
	 * If not, the data is corrupt and should be ignored.
	 */
	unsigned short CRC(char const message[], int numbytes, unsigned short crccheck){

		unsigned short crc = 0xFFFF;
		int i = 0, j = 0;

		for(i = 0; i < numbytes; i++){
			crc = (crc ^ (message[i] << 8));

			for(j = 1; j <= 8; j++){
				if(crc & (0x8000))
				{
                     crc = (crc << 1) ^ 0x1021; //polynomial
				}
				else crc = (crc << 1);
			}
		}
		return crc ^ crccheck;
	}
}

/**
 * Transmitter constructor.  Sets up a new transmitter object with the specified path
 * as a file pointer (e.g. ttyS0).
 * @param path Path (file-pointer) to write transmitted data.
 */
Transmitter::Transmitter() {

	this->tx = false;
	this->rx = false;
	this->fd = -1;
}

Transmitter::~Transmitter(){
	close(this->fd);
}

/**
 * Configures the transmitter to bind the path specified.
 * @param path
 * @return
 */
bool Transmitter::configure(const std::string& path){

	this->fd = open(path.c_str(), O_RDWR | O_NDELAY);
	  //fd = open("/dev/ttyS0", O_RDWR | O_NOCTTY | O_NDELAY);

	  if (fd == -1)
	  {
	    //Could not open the port.
	    perror("open_port: Unable to open /dev/ttyS0 - ");
	    return false;
	  }
	  else
	  {
	  	fcntl(fd, F_SETFL, 0);
	  }

	  /* SET OPTIONS */
	  	struct termios options; // UART port options data structure
	    // Get the current options for the port...
	    tcgetattr(fd, &options);
	    // Set the baud rates to 115200...
	    cfsetispeed(&options, B19200); //B115200
	    cfsetospeed(&options, B19200);
	    // Enable the receiver and set local mode...
	    options.c_cflag |= (CLOCAL | CREAD);
	    // Set charater size
	    options.c_cflag &= ~CSIZE; // Mask the character size bits
	    options.c_cflag |= CS8;    // Select 8 data bits
	    // Set no parity 8N1
	    options.c_cflag &= ~PARENB;
	    options.c_cflag &= ~CSTOPB;
	    options.c_cflag &= ~CSIZE;
	    options.c_cflag |= CS8;
	    // Disable Hardware flow control
	    options.c_cflag &= ~CRTSCTS;
	    // Use raw input
	    options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
	    // Disable SW flow control
	    options.c_iflag &= ~(IXON | IXOFF | IXANY);
	    // Use raw output
	    options.c_oflag &= ~OPOST;
	    // Set new options for the port...
	    tcsetattr(fd, TCSANOW, &options);

        /* Success */
        return true;
}


/**
 *  Writes command to UART.
 *
 *	@param data The QuadCommand object containing the command to be executed.
 * 	@return True on successful transmission of all data, false otherwise.
 */
bool Transmitter::transmitCommand(QuadCommand& data){

	if(this->tx == false){
		return false;
	}
	const char* bytedata = (char*) data.getPacket();
	char start_byte = -1;
    unsigned short crc = CRC(bytedata, data.getPacketSize(), 0x0);


	/* Send Start byte */
	unsigned short n = write(this->fd, &start_byte, 1);

	/* Send position data (cur and target) */
    n += write(this->fd, bytedata, data.getPacketSize());

	/* Send CRC */
	n += write(this->fd, (unsigned*)&crc, 2);

	//fprintf(stderr, "CRC: %x \n", crc);

    /* Slow down transmissions, avoid too many stacked, causing lag. */
    usleep(30000);

    return n == (data.getPacketSize() + sizeof(crc) + sizeof(start_byte)) ? true : false;
}


