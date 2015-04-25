///////////////////////////////////////////////////////////////
//                                                           //
// File Name: sendCommand.c                                  //
// Author: Kevin Engel, Mike Johnson, Kelsey Moore           //
//                                                           //
// Description:  Uses UART port to send commands to set      //
// quad's throttle, roll, pitch, yaw PPM values.  Formatted  //
// data array is sent to Digilent board, which is programmed //
// with PPM VHDL.					     //
// 							     //
// command format: {xC1 hi lo xC2 hi lo xC3 hi lo xC4 hi lo} //
// hi and lo: high byte low byte			     //
//			    				     //
// Quad channel interpretation:				     //
// Channel1: Throttle					     //
// Channel2: Roll					     //
// Channel3: Pitch					     //
// Channel4: Yaw                                             //
//                                                           //
/////////////////////////////////////////////////////////////// 
#include <stdio.h> /* Standard input/output definitions */
#include <string.h> /* String function definitions */
#include <unistd.h> /* UNIX standard function definitions */
#include <fcntl.h> /* File control definitions */
#include <errno.h> /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */


// Prototypes
int open_port(void);           		// Open a serial port
void set_uart_options(int fd); 		// Configure serial port
void read_uart(int fd, char *payload, int length); // Read from UART

main(int argc, char** argv)
{
int uart_fd;            	// UART file descriptor
int n = 0, i;              	// number of bytes written out of the UART port
//char payload[100];      	// store/send packet payload
unsigned char command[12];	//command data 


  // Open the UART port
  if((uart_fd = open_port()) == -1)
  {
    fprintf(stderr,"ERROR opening UART port\n");
  }

  // Set UART port options 8N1 (e.g. BAUD rate, parity, flow control)
  set_uart_options(uart_fd);
	
//max value should be 1312 (hi: 5, lo: 32)
  command[0] = 0xC1;
  command[1] = 5;
  command[2] = 32;
  command[3] = 0xC2;
  command[4] = 0;
  command[5] = 0;
  command[6] = 0xC3;
  command[7] = 0;
  command[8] = 0;
  command[9] = 0xC4;
  command[10] = 0;
  command[11] = 0;
  
	for(i = 0; i < 12; i++)
	{
		fprintf(stderr,"%u\n",command[i]);
	}
  

  // Write data out of the UART port
    n = write(uart_fd, command, 12);
    fprintf(stderr,"Wrote %d of 12 bytes\n",n);

  
  // Read data from the UART port (block until requested number of bytes read
  //n = read(0, command, 12);
  
  // Close UART port
  close(uart_fd);

}





///////////////////////////////////
// Define helper functions start //
///////////////////////////////////


//////////////////////////////////////////////////////////////
// 'open_port()' - Open serial port 1.                      //
//                                                          //
// Returns the file descriptor on success or -1 on error.   //
//                                                          //
//////////////////////////////////////////////////////////////
int open_port(void)
{
int fd; /* File descriptor for the port */
  fd = open("/dev/ttyS0", O_RDWR | O_NDELAY);
  //fd = open("/dev/ttyS0", O_RDWR | O_NOCTTY | O_NDELAY);
  if (fd == -1)
  {
    //Could not open the port.
    perror("open_port: Unable to open /dev/ttyS0 - ");
  }
  else
  {
  	fcntl(fd, F_SETFL, 0);
  }
return(fd);
}


///////////////////////////////////////////////////////////
// Function Name: set_uart_options                       //
//                                                       //
//Description: Sets up various UART port attributes      //
//                                                       //
///////////////////////////////////////////////////////////
void set_uart_options(int fd)
{
struct termios options; // UART port options data structure

  // Get the current options for the port...
  tcgetattr(fd, &options);

  // Set the baud rates to 9600...
  cfsetispeed(&options, B38400);
  cfsetospeed(&options, B38400);

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

}


///////////////////////////////////////////////////////////
// Function Name: read_uart                              //
//                                                       //
//Description: Read "length" bytes from the UART and     //
//             store in the "payload" buffer             //
//                                                       //
///////////////////////////////////////////////////////////

void read_uart(int fd, char *payload, int length)
{
char *buf;  // Pointer into payload buffer
int i;

  buf = payload;

  // Read from UART one byte at a time
  for(i=0; i<length; i++)
  {
    if(read(fd, (void *)buf, 1) == -1)
    {
      fprintf(stderr,"READ ERROR!!!");
    }
    buf = buf++;
  }
}

///////////////////////////////////
// Define helper functions end   //
///////////////////////////////////
