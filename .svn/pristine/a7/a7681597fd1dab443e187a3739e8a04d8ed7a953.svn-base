/*
 * Locator.h
 *
 *  Created on: Jan 26, 2014
 *      Author: Michael Johnson
 */

#include <vrpn_Tracker.h>
#include <vrpn_Connection.h>
#include "CommandInterpreter.h"
#include "Transmitter.h"


#ifndef LOCATOR_H_
#define LOCATOR_H_


class CameraLocation{

	public:
		CameraLocation(const std::string&, CommandInterpreter&, Transmitter&);

		virtual ~CameraLocation();
		bool startTracking();
		void track();
		bool stopTracking();
        void destroy();

		void VRPN_CALLBACK handleLocation(const vrpn_TRACKERCB&);

		inline bool is_started(){
			return this->running;
		}

	private:
        std::string addr;
		vrpn_Connection *connection;
		vrpn_Tracker_Remote *tracker;
		pthread_t thread;
		CommandInterpreter& interpreter;
		Transmitter& transmitter;
		volatile bool running;
};

#endif /* LOCATOR_H_ */
