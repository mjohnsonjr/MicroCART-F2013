
#include <unistd.h> /* UNIX standard function definitions */
#include <stdio.h> /* Standard input/output definitions */        
#include <string.h> /* String function definitions */
#include <errno.h> /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */    
#include <fcntl.h>   //open (file options)

#define SIZE_GPS 100
#define SIZE_TOK 10
#define NUM_DATA 4
#define GGA_TIME 1	//token location of time in GGA sentence, using "," as delimiter
#define GGA_LAT 2
#define GGA_LON 4
#define GGA_QLTY 6
#define GGA_ALT 9



int open_port(int usbPortNum);
void set_uart_options(int fd);
void strAppendChar(char* s, char c);

struct GPS
{
 	float time;
 	float lat;
 	float lon;
 	char quality;
 	float alt;
};

int main()
{   
   
   int fdGPS;            //GPS file descriptor
   FILE* logFile;
	char toWrite;
	char readBuffer;
	
	//testing
	char hasChar = 0;
	
	//gps parsing
	char isReadingCommand = 0;
	char hasGPS = 0;
	char isReadingGPS = 0;
	char GPSsentence[SIZE_GPS];	//GGA sentence is 71 chars long
 	char delimiters[] = ",";
 	//char GPStoken[SIZE_TOK];
 	char* GPStoken;
 	int tokenCount = 0;
 	struct GPS gpsData = {0.0, 0.0, 0.0, 0, 0.0};
 	
 	
 		
	
   //open and set up usb/uart for GPS
  	fdGPS = open_port(0);
   set_uart_options(fdGPS);
   
   printf("GPS fd: %d\n", fdGPS);
 	
   /*
	//test
   while(1)
   {
      hasChar = read(fdGPS, &readBuffer, 1);
     
	  printf("%c", readBuffer);
     fflush(stdout);
	
	 }
	*/  
	
	/*
	printf("size of float: %d\n", sizeof(float));
	printf("size of double: %d\n", sizeof(double));
		printf("size of int: %d\n", sizeof(int));
	printf("size of short: %d\n", sizeof(short));
		printf("size of long: %d\n", sizeof(long));
		*/

	
	while(1)
	{  
		//read GPS sentence, form string, and notify tokenizer
		if(read(fdGPS, &readBuffer, 1))
		{
			//located beginning of GPS setence
		  	if(readBuffer == '$')
		  	{
		  		isReadingGPS = 1;
		  		hasGPS = 0;
		  		memset(GPSsentence, 0, SIZE_GPS);
		  		/*
		  		//test
		  		printf("found beginning\n");
		  		*/
		  	}
		  	
		  	//located end of GPS sentence
		  	if(readBuffer == '\r')
			{
				isReadingGPS = 0;
				hasGPS = 1;
				/*
				//test
				printf("found end\n");
				*/
				printf("%s\n", GPSsentence);
			}
			
			//forming string of GPS setence
			if(isReadingGPS && readBuffer != '$' && readBuffer != '\r' && readBuffer != '\n')
			{
				strAppendChar(GPSsentence, readBuffer);
			}	  	
		}
		
		//tokenize GPS sentence, parse and store important data
		if(hasGPS)
		{
			GPStoken = strtok(GPSsentence, delimiters);
			tokenCount++;
			
			if(strcmp(GPStoken, "GPGGA") == 0)
			{
				while(GPStoken != NULL)
				{
					//test
					printf("token: %s, count: %d\n", GPStoken, tokenCount);
				
					GPStoken = strtok(NULL, delimiters);
					
					if(tokenCount == GGA_TIME)
					{
						gpsData.time = strtof(GPStoken, NULL);
						printf("time: %.3f\n", gpsData.time);
					}
					else if(tokenCount == GGA_LAT)
					{
						gpsData.lat = strtof(GPStoken, NULL);
						printf("lat: %.3f\n", gpsData.lat);
					}
					else if(tokenCount == GGA_LON)
					{
						gpsData.lon = strtof(GPStoken, NULL);
						printf("lon: %.3f\n", gpsData.lon);						
					}
					else if(tokenCount == GGA_QLTY)
					{
						gpsData.quality = atoi(GPStoken);
						printf("quality: %d\n", gpsData.quality);
					}
					else if(tokenCount == GGA_ALT)
					{
						gpsData.alt = strtof(GPStoken, NULL);
						printf("alt: %.3f\n", gpsData.alt);
					}
					
					tokenCount++;
				}
			}
			
			hasGPS = 0;
			tokenCount = 0;
		}
	}
  
	
   //memset(writeOut, 0, 100);
  // memset(writeIn, 0, 100);

}


//////////////////////////////////////////////////////////////
// 'open_port()' - Open serial port 1.                      //
//                                                          //
// Returns the file descriptor on success or -1 on error.   //
//                                                          //
//////////////////////////////////////////////////////////////
int open_port( int usbPortNum)
{
   int fd; /* File descriptor for the port */
   char device[30];
   sprintf( device, "/dev/ttyUSB%d", usbPortNum );
   fd = open(device, O_RDWR | O_NDELAY);
   //fd = open("/dev/ttyUSB0", O_RDWR | O_NOCTTY | O_NDELAY);
   if (fd == -1)
   {
      //Could not open the port.
      char errString[30];
      sprintf( errString, "open_port: Unable to open %s", device );
      perror(errString);
   }
   else
   {
      //set flag that device opened properly      
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

   // Get the current options for the port
   tcgetattr(fd, &options);
   
   // Set the in out baud rates
   cfsetispeed(&options, B9600);
   cfsetospeed(&options, B9600);
   
   // Enable the receiver and set local mode
   options.c_cflag |= (CLOCAL | CREAD);

   // Set charater size
   options.c_cflag &= ~CSIZE;    // Mask the character size bits
   options.c_cflag |= CS8;       // Select 8 data bits

   // Set no parity 8N1
   options.c_cflag &= ~PARENB;   //no parity
   options.c_cflag &= ~CSTOPB;   //1 stop bit 
   options.c_cflag &= ~CSIZE;    //mask to delete old
   options.c_cflag |= CS8;       //8 bits data (character size)

   // Disable Hardware flow control
   options.c_cflag &= ~CRTSCTS;

   // Use raw input
   options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);   

   // Disable SW flow control
   options.c_iflag &= ~(IXON | IXOFF | IXANY);  // - can normally be all 0

   // Use raw output
   options.c_oflag &= ~OPOST;                   // - can normally be all 0

   // Set new options for the port...
   tcsetattr(fd, TCSANOW, &options);   //terminal control set now

}

void strAppendChar(char* s, char c)
{
        int len = strlen(s);
        s[len] = c;
        s[len+1] = '\0';
}



