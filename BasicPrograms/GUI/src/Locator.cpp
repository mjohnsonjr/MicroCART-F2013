/*
 * Locator.cpp
 *
 *  Created on: Jan 27, 2014
 *      Author: Michael Johnson
 */

//#define PRINT_DEBUG

#include <iostream>
#include <iomanip>
#include <vrpn_Connection.h>
#include <sys/time.h>
#include <vrpn_Tracker.h>
#include <quat.h>
#include <cstdlib>
#include <unistd.h>
#include <pthread.h>
#include "Locator.h"
#include "QuadCommand.h"
#include "CommandInterpreter.h"
#include "Transmitter.h"


/* These are used as wrapper function pointers for Pthread.. Lab computer doesn't have
 *  C++ 11 compiler so I can't use std::thread :(.
 */
namespace {

	/* Some Helper Vars */
	volatile bool got_report = false;
	double secmillis = 0, usecmillis = 0;
	double yawPitchRoll[3];

	/* Setup function for camera thread */
	void* getCameraLoop(void* location){

		CameraLocation* cameras = (CameraLocation*) location;
		while(cameras->is_started()){
            cameras->track();
		}

		pthread_exit(NULL);
	}

	/* VRPN Callback function, used solely by VRPN once the tracker has been configured.
	 */
	void VRPN_CALLBACK getHandleLoc(void* location, const vrpn_TRACKERCB t){
		((CameraLocation *) location)->handleLocation(t);
	}
}


/**
 *  Do stuff every time the UAV's location is found (camera update callback).
 *  Once moving to IMU, yawPitchRoll will need to be removed to restore bandwidth.
 **/
void CameraLocation::handleLocation(const vrpn_TRACKERCB& t){

		secmillis = t.msg_time.tv_sec * 1000;
		usecmillis = t.msg_time.tv_usec/1000;

		/* Converts quarternion coordinates too euler angles (in radians) */
		q_to_euler(yawPitchRoll, t.quat);

		this->interpreter.getQuadCommand().setCurrentAltitude(t.pos[2]);
		this->interpreter.getQuadCommand().setCurrentLatitude(t.pos[0]);
		this->interpreter.getQuadCommand().setCurrentLongitude(t.pos[1]);
		this->interpreter.getQuadCommand().setCurrentPitch(yawPitchRoll[1]);
		this->interpreter.getQuadCommand().setCurrentRoll(yawPitchRoll[2]);
		this->interpreter.getQuadCommand().setCurrentYaw(yawPitchRoll[0]);

#ifdef PRINT_DEBUG
	//fprintf(stderr, "%.3f %.6f %.6f %.6f %.6f %.6f %.6f\n", (secmillis + usecmillis)/1000.0, t.pos[0], t.pos[1], t.pos[2], yawPitchRoll[0], yawPitchRoll[1], yawPitchRoll[2]);

	std::cerr << (secmillis + usecmillis)/1000.0 << std::setfill('0') << " "
			<< t.pos[0] << std::setprecision(6) << std::setfill('0') << " "
			<< t.pos[1] << std::setprecision(6) << std::setfill('0') << " "
			<< t.pos[2] << std::setprecision(6) << std::setfill('0') << " "
			<< yawPitchRoll[0] << std::setprecision(6) << std::setfill('0') << " "
			<< yawPitchRoll[1] << std::setprecision(6) << std::setfill('0') << " "
			<< yawPitchRoll[2] << std::setprecision(6) << std::setfill('0') << "\n";

#endif
		got_report = true;
}


/**
 * Constructor setup the connection, tracker remote, and register a function pointer to the change handler.
 */
CameraLocation::CameraLocation(const std::string& addr, CommandInterpreter& inter, Transmitter& trans) : interpreter(inter), transmitter(trans){

	this->thread = (pthread_t) NULL;
    this->addr = addr;
	this->connection = vrpn_get_connection_by_name(addr.c_str());
    this->tracker = new vrpn_Tracker_Remote("UAV", connection);
    this->tracker->register_change_handler(this, getHandleLoc);
    this->running = false;
}
CameraLocation::~CameraLocation(){
	delete this->connection;
	delete this->tracker;
}

void CameraLocation::destroy(){
    this->connection->removeReference();
    this->connection->removeReference();
    this->tracker->unregister_change_handler(this, getHandleLoc);
    delete this->tracker;
    delete this->connection;
}


/**
 * Starts the camera tracking loop, continuously retreiving camera data and transmitting it until
 * the stopTracking() method is called.
 * @return True on success.
 */
bool CameraLocation::startTracking(){

	/* Ensure we have the connection before creating
	 * the thread.. Precautionary.
	 */
    std::cerr << "Bound to VRPN Server with status: " << this->connection->doing_okay() << "\n";
    std::cerr << "Listening for data from VRPN Server (" << this->addr << ")...\n";


    /* IT CAN GET STUCK HERE! */
    if(this->connection->mainloop() == -1){
        return false;
    }
//    if(!this->connection->connected()){
//        return false;
//    }

    std::cerr << "Successful connection to (" << this->addr << ")!\n";

    this->running = true;
	if(pthread_create(&this->thread, NULL, getCameraLoop, (void*)this) == 0){
		return true;
	}

    this->running = false;
	return false;

}

/**
 * Tracks the UAV's location one time, and transmits that capture over UART.
 */
void CameraLocation::track(){

	/* Purge old reports:
	http://www.cs.unc.edu/Research/vrpn/vrpn_Tracker_Remote.html#simple_example */
	/** TODO: QT DOES NOT LIKE THIS WHY??? OH GOD WHY?
	 * UPDATE: I FIXED IT BUT CAN'T REMEMBER HOW.  SOMETHING WITH THREADS */
    this->tracker->mainloop();
	got_report = false;

	/* Make sure it's new data */
	while(!got_report){
		this->tracker->mainloop();
	}

	/* Transmit data here ! */
	if(!this->transmitter.transmitCommand(interpreter.getQuadCommand())){
		std::cerr << "ERROR ON TRANSMIT!\n";
	}
}

/**
 * Stops a tracking loop if one is started.
 * @return True on successful stop, false otherwise.
 */
bool CameraLocation::stopTracking(){

	this->running = false;
	pthread_join(this->thread, NULL);
	return true;
//	void *res;
//
//	if(pthread_cancel(this->thread) != 0){
//		 return false;
//	 }
//
//	if(pthread_join(this->thread, &res)){
//		return false;
//	}
//	if(res == PTHREAD_CANCELED){
//		return true;
//	}
//
//	return false;
}
