/*
 * cli_microcart.cpp
 *
 *  Created on: Dec 9, 2013
 *      Author: michael
 */


#include <cerrno> /* Error number definitions */
#include <sys/fcntl.h> /* File control definitions */
#include <termios.h> /* POSIX terminal control definitions */
#include <unistd.h> /* UNIX standard function definitions */
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>

/* The quad's mode of operation, up startup type following commands in
 * MOVE: Allows for standard movement commands (set alt, adjust alt, set lat, adjust lat, set long, adjust long).
 * CALIBRATION: Allows for calibrations commands, and setting adjustments
 * TEST: Allows for testing commands, (commands such as "pitch, roll, yaw" for test purposes)
 */

// Parsing, chopping carrots, each piece is separated by a "space"


/* DEFINITIONS FOR ENUM/CLASSES, move in the future. */
enum Mode{
	MOVE,CALIBRATION,TEST
};


/* Struct/Class Def and methods */
struct QuadCommand{
	char action;
	std::string value;

	char* pack();
	static struct QuadCommand unpack(char*);
	QuadCommand();
	~QuadCommand();
};

QuadCommand::QuadCommand(){
	this->action = -1;
	this->value = "0";
}
QuadCommand::~QuadCommand(){}

/* Packs the QuadCommand into a byte array to be transmitted. */
char* QuadCommand::pack(){

	/* hacky conversion */
	int i;
	std::stringstream ss;
	ss << this->value;
	const std::string& stringvalue = ss.str();

	char* packed = new char[stringvalue.length() + 2];
	packed[0] = this->action;

	for(i = 0; i < stringvalue.length(); i++){
		packed[i +1] = stringvalue.at(i);
	}
	packed[i + 1] = -128;

	return packed;
}

struct QuadCommand QuadCommand::unpack(char* packed){

	int i = 0;
	struct QuadCommand quad;
	std::stringstream ss;
	quad.action = packed[0];

	while(packed[i] != -128){
		ss << packed[i];
		i++;
	}

	quad.value = std::strtod(ss.str().c_str(), 0);//std::stof(ss.str());

	return quad;
}



/* Prototypes (these can stay) */
bool handleCommand(struct QuadCommand &data, const std::string input);
void executeCommand(struct QuadCommand &data, const int &quad_fd);
const char translateCommand(const std::string &input);
void setupUART(int &fd);


/*
 * Runs in a continuous loop taking user commands.
 */
int main(int argc, char** argv){

	std::string inputString;
	struct QuadCommand data;

	/* Setup UART */
	int quad_fd = -1;
	setupUART(quad_fd);

	/* Continuously read user commands */
	while(true){
		/* Get user input from command line */
		std::getline(std::cin, inputString);

		/* Parse into data array, check handleCommand's return for validity */
		if(!handleCommand(data, inputString)){
			continue;
		}

		/* Execute the command */
		executeCommand(data, quad_fd);
	}
}

/*
 * Checks command validity, and stores into a QuadCommand struct.
 *
 * Returns true on success, and false on failure (invalid input).
 */
bool handleCommand(struct QuadCommand &data, const std::string input){

	/* Data is modified to indicate the type of command */

	/* Put line into string stream */
	std::stringstream inputParser(input);

	/* Holds command token */
	std::string token;


	/* First command component */
	if(inputParser.good()){
		inputParser >> token;
		//LOOKUP CODE FOR EACH COMMAND
		data.action = translateCommand(token);

		/* Check if the action is a valid one, don't continue if it isn't. */
		if(data.action == -1){
			std::cerr << "Error on input, invalid action.\n";
			data.action = -1;
			data.value = "0";
			return false;
		}
	}
	else{
			std::cerr << "Invalid Command Syntax.\n";
			data.action = -1;
			data.value = "0";
			return false;
	}

	/* Second command component (Value) */
	if(inputParser.good()){
		inputParser >> token;
		data.value = token;

	}
	else{
		std::cerr << "Invalid Command Syntax.\n";
		data.action = -1;
		data.value = "0";
		return false;
	}

	/* Ensure it's empty, otherwise error. */
	if(inputParser.good()){
		std::cerr << "Invalid Command Syntax.\n";
		data.action = -1;
		data.value = "0";
		return false;
	}

	return true;
}

/* Writes command to UART
 *
 *  Packed Data format: action, char representation of float value (to be determined units), termination char (-128).
 *	Use the static unpack method to repack it into a struct.
 *
 */
void executeCommand(struct QuadCommand &data, const int &quad_fd){

	std::stringstream ss;
	ss << data.value;

	const std::string str = "OMGWTF\n";
	const char* bytedata = str.c_str();//data.pack();

	//std::cerr << "Equal?: "  << data.action << data.value << (char) -128 <<  " : " << bytedata << "\n";

	short n = write(quad_fd, bytedata, 7);
	std::cerr << "Wrote " << n << " of 7 bytes\n";

	//delete bytedata;
}

const char translateCommand(const std::string &input){

	if(!input.compare("alt")){
		return 0;
	}
	else if(!input.compare("salt")){
		return 1;
	}
	else if(!input.compare("lat")){
		return 2;
	}
	else if(!input.compare("slat")){
		return 3;
	}
	else if(!input.compare("lon")){
		return 4;
	}
	else if(!input.compare("slon")){
		return 5;
	}

	else{
		return -1;
	}
}


/* Sets up the UART to write to (bluetooth)? */
void setupUART(int &fd){

	  fd = open("/dev/ttyUSB0", O_RDWR | O_NDELAY);
	  //fd = open("/dev/ttyS0", O_RDWR | O_NOCTTY | O_NDELAY);

	  if (fd == -1)
	  {
	    //Could not open the port.
	    perror("open_port: Unable to open /dev/ttyS0 - ");
	    exit(1);
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
	    cfsetispeed(&options, B115200);
	    cfsetospeed(&options, B115200);

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




