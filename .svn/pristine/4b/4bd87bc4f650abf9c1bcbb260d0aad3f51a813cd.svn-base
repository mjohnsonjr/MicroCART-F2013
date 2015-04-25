/*
 * CLI.h
 *
 *  Created on: Feb 5, 2014
 *      Author: Michael Johnson
 */

#ifndef CLI_H_
#define CLI_H_

#include "Transmitter.h"
#include "CommandInterpreter.h"
#include "Locator.h"
#include "Logger.h"
#include "USBController.h"

#define CAMERA_DATA


class CLI {
public:
	/* fp to transmitter, ip string to camera data, fp to output stream (debug) */
	CLI(Logger& logger);
	virtual ~CLI();
	bool setupTransmitter(const std::string&);
	bool setupCamera(const std::string&);
	bool setupUSBController();
	bool start();
	bool stop();
	void passCommand(const std::string&);

	inline bool is_started(){
		return this->running;
	}
	inline Logger& getLogger(){
	    return this->logger;
	}
	inline CommandInterpreter& getInterpreter(){
		    return *this->interpreter;
	}
	inline USBController& getUSBController(){
		return *this->controller;
	}

	inline volatile float* getDataPacket(){
			    return this->interpreter->getQuadCommand().getPacket();
	}

	inline bool usingCameras(){
		return this->using_cameras;
	}
	inline bool usingController(){
		return this->using_controller;
	}
	void setUsingCameras(bool);
	void setUsingController(bool);
	bool startCameras();
	bool startController();
    bool stopController();


private:
	Logger& logger;
	Transmitter* transmitter;
	CommandInterpreter* interpreter;
	USBController* controller;
	pthread_t main_thread;

	volatile bool running;

	/* Status variables of each component */
	bool using_cameras;
	bool using_controller;

#ifdef CAMERA_DATA
	CameraLocation* locator;
#endif

};

#endif /* CLI_H_ */
