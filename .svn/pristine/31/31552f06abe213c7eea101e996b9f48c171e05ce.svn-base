/*
 * CLI.cpp
 *
 *  Created on: Feb 5, 2014
 *      Author: Michael Johnson
 */


#include "CLI.h"
#include <cerrno>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <istream>
#include <iterator>
#include <vector>
#include <pthread.h>
#include "QuadCommand.h"
#include "CommandInterpreter.h"
#include "Locator.h"
#include "Transmitter.h"

namespace{

	void* cli_mainloop(void* i_cli){

		CLI* cli = (CLI*) i_cli;
		std::string inputString;

        while(1){
            /* Continuously read user commands */
            if(cli->is_started()){
                /* Get user input from command line */
                std::getline(std::cin, inputString);

                /* Parse into data array, check handleCommand's return for validity */
                if(cli->getInterpreter().interpret(inputString)){

                    /* Execute the command */
                    /*if(!this->transmitter->transmitCommand(this->interpreter->getQuadCommand())){
                        logger << std::cerr << "Error in send!\n";
                    }*/
                }
            }
        }
		pthread_exit(NULL);
	}
}

CLI::CLI(Logger &logger): logger(logger) {

		this->locator = NULL;
		this->transmitter = NULL;
		this->controller = NULL;
		this->interpreter = new CommandInterpreter(logger);
		this->running = false;
		this->main_thread = NULL;
		this->using_cameras = false;
		this->using_controller = false;
}

CLI::~CLI() {
	delete this->interpreter;
	delete this->transmitter;

#ifdef CAMERA_DATA
	delete this->locator;
#endif
}

/**
 * Configures the File Pointer to send the data writes to (bluetooth module).
 * @param transmitter_fp
 * @return True on successful setup.
 */
bool CLI::setupTransmitter(const std::string& transmitter_fp){

	/* Setup UART communication */

        /* Avoid the leaks */
        if(this->transmitter != NULL){

            delete this->transmitter;
            this->transmitter = NULL;
            this->transmitter = new Transmitter();
        }
        else{
            this->transmitter = new Transmitter();
        }

        /* If not successful configuration to fp */
        if(!this->transmitter->configure(transmitter_fp)){
            delete this->transmitter;
            this->transmitter = NULL;
            this->logger << "Specified Bluetooth file pointer failed to setup properly!\n";
            return false;
        }

		/* Successful */
		return true;
}

/**
 * Setup the Camera System data reading.
 * @param camera_address
 * @return True on success.
 */
bool CLI::setupCamera(const std::string& camera_address){


	/* Setup Camera data reading */
	if(!camera_address.empty() && this->interpreter != NULL && this->transmitter != NULL){
			/* Delete old, avoid leaks. */
            if(this->locator != NULL){
//                this->locator->destroy();
//                delete this->locator;
//                this->locator = NULL;
//                this->locator = new CameraLocation(camera_address, *this->interpreter, *this->transmitter);
                return true;
            }
            else{
                this->locator = new CameraLocation(camera_address, *this->interpreter, *this->transmitter);
                return true;
            }
		}

		else{
			this->logger << "Unable to setup Cameras!\n";
			return false;
		}
}

bool CLI::setupUSBController(){
	if(this->controller == NULL){
        this->controller = new USBController(*this->interpreter);
		/* Ensure proper setup */
    }
    else{
        delete this->controller;
        this->controller = new USBController(*this->interpreter);
    }

    if(!this->controller->setup()){
        delete this->controller;
        this->controller = NULL;

        std::cerr << "Unable to setup USB Controller, ensure it is plugged in.\n";
        return false;
    }

	return true;
}

/**
 * Beings the CLI, can't be stopped.
 * EDIT: Now it can be stopped :p
 */
bool CLI::start(){

	/* Enable tx and rx on the transmitter (bluetooth) */
	if(this->transmitter != NULL){
		this->transmitter->enableTx();
		this->transmitter->enableRx();
	}
	else{
		this->logger << "Error, Bluetooth transmitter not setup properly.  Aborting start.\n";
		return false;
	}

	/* Setup the camera system, if necessary */
    if(this->using_cameras){
		if(this->locator != NULL){
			if(this->locator->startTracking()){

			}
			else{
				this->logger << "Error, Failed to start Camera Tracking.  Aborting start.\n";
				return false;
			}
		}
		else{
			this->logger << "Error, Cameras not setup, use setupCamera().  Aborting start.\n";
			return false;
		}
	}


    if(this->using_controller){
		if(this->controller != NULL){
            if(this->controller->start()){

			}
			else{
				this->logger << "Error, Failed to start controller.  Aborting start.\n";
				return false;
			}
		}
		else{
            if(setupUSBController()){
                if(this->controller->start()){
                    return true;
                }
            }
			return false;
		}
	}


	/* Start runner thread*/
    this->running = true;
	if(pthread_create(&this->main_thread, NULL, cli_mainloop, (void*)this) == 0){
		/* CLI is running */
		return true;
	}

    this->running = false;
	return false;
}


/**
 * Stops the CLI, and performs any termination conditions.
 * Throttle to 0.
 */
bool CLI::stop(){

	this->interpreter->getQuadCommand().setAutoThrottle(false);
	this->interpreter->getQuadCommand().setManualThrottle(0.0);

    this->transmitter->disableTx();
    this->transmitter->disableRx();

    /* Stop all components */
	if(this->using_cameras){
		this->locator->stopTracking();
	}

	if(this->using_controller){
		this->controller->stop();
    }
	/* After stopping everything, finally stop CLI */
    this->running = false;
    //pthread_join(this->main_thread, NULL);

    return true;

}


/**
 * Passes the given command to the CommandInterpreter object.
 * Used primarily for any program wrapping the CLI, to pass commands
 * through (in our case this is the GUI, but it could be anything really).
 * @param str Command to be passed.
 */
void CLI::passCommand(const std::string &str){
	this->interpreter->interpret(str);
}

bool CLI::startCameras(){
	if(this->using_cameras){
		return this->locator->startTracking();
	}
	else{
		this->logger << "Camera's aren't enabled, enable them before starting.\n";
		return false;
	}
}

bool CLI::startController(){
    if(this->using_controller){
		return this->controller->start();
	}
	else{
        this->logger << "Controller isn't enabled, enable it before starting.\n";
		return false;
	}
}

bool CLI::stopController(){

    if(this->using_controller && this->controller != NULL){
        return this->controller->stop();
    }
    else{
        return false;
    }
}

void CLI::setUsingCameras(bool val){
	this->using_cameras = val;
}

void CLI::setUsingController(bool val){
	this->using_controller = val;
}
