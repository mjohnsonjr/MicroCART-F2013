/*
 * QuadCommand.cpp
 *
 *  Created on: Jan 23, 2014
 *      Author: Michael Johnson
 */

#include "QuadCommand.h"
#include <cstdlib>
#include <iostream>


	QuadCommand::QuadCommand(){
		this->setAutoThrottle(false);
	}

	QuadCommand::~QuadCommand(){}

	QuadCommand::QuadCommand(float *packet){
		for(int i = 0; i < this->getPacketSize(); i++){
            this->packet[i] = packet[i];
            this->packet[MANUAL_CONTROL] = false;
            this->packet[MANUAL_THROTTLE] = false;
		}
	}

	/* Methods */
	void QuadCommand::setPacket(const float *packet){

		for(int i = 0; i < this->getPacketSize(); i++){
					this->packet[i] = packet[i];
		}
	}

	void QuadCommand::setCurrentAltitude(const float val){
		this->packet[CUR_POS_ALT] = val;
	}
	void QuadCommand::setCurrentLatitude(const float val){
		this->packet[CUR_POS_LAT] = val;
	}
	void QuadCommand::setCurrentLongitude(const float val){
		this->packet[CUR_POS_LON] = val;
	}
	void QuadCommand::setCurrentPitch(const float val){
		this->packet[CUR_OR_PITCH] = val;
	}
	void QuadCommand::setCurrentRoll(const float val){
		this->packet[CUR_OR_ROLL] = val;
	}
	void QuadCommand::setCurrentYaw(const float val){
		this->packet[CUR_OR_YAW] = val;
	}

	void QuadCommand::setTargetAltitude(const float val){
		this->packet[TARGET_POS_ALT] = val;
	}
	void QuadCommand::setTargetLatitude(const float val){
		this->packet[TARGET_POS_LAT] = val;
	}
	void QuadCommand::setTargetLongitude(const float val){
		this->packet[TARGET_POS_LON] = val;
	}
	void QuadCommand::setTargetDirection(const float val){
		this->packet[TARGET_DIR] = val;
	}
	void QuadCommand::setTargetPitch(const float val){
		this->packet[TARGET_PITCH] = val;
	}
	void QuadCommand::setTargetRoll(const float val){
		this->packet[TARGET_ROLL] = val;
	}
	void QuadCommand::setManualThrottle(const float val){
		this->packet[MANUAL_THROTTLE] = val;
	}
	void QuadCommand::setAutoThrottle(const bool val){
		this->packet[AUTO_THROTTLE] = val;
	}
    void QuadCommand::setManualControl(const bool val){
        this->packet[MANUAL_CONTROL] = val;
    }

