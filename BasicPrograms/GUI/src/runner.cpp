/*
 * runner.cpp
 *
 *  Created on: Dec 9, 2013
 *      Author: michael
 */
#include "CLI.h"


/* The quad's mode of operation, upon startup type following commands in
 * MOVE: Allows for standard movement commands (set alt, adjust alt, set lat, adjust lat, set long, adjust long).
 * CALIBRATION: Allows for calibration commands, and setting adjustments
 * TEST: Allows for testing commands, (commands such as "pitch, roll, yaw" for test purposes)
 */

/**
 * TODO: List
 *
 * Read data back.
 *
 */

/*
 * Runs in a continuous loop taking user commands.
 */
int main(int argc, char** argv){

	std::ofstream fs("./OUTPUTTEST.txt");

	Logger log(fs);
	CLI cli(log);
	cli.setupTransmitter("/dev/ttyUSB0");
	cli.setupCamera("192.160.0.50:3883");

	if(cli.start()){

	}
}






