/*
 * CommandInterpreter.cpp
 *
 *  Created on: Jan 23, 2014
 *      Author: Michael Johnson
 */
#include "CommandInterpreter.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cstdlib>

/* Prototype */


/* Unnamed namespace/statics, these are used to translate and break up the
 * passed in command (needed for string -> primitive type (float) conversions. */
namespace {
	const std::vector<std::string> vectorize(const std::string &input){

		std::stringstream ss;
        if(!input.empty()){
            ss << input;

            std::string str;
            std::vector<std::string> args;

            while(ss >> str){
                args.push_back(str);
            }
            return args;
        }
        /* Input error ? */
        else{
            std::vector<std::string> args2;
            args2.push_back("-1");
            args2.push_back("0");
            return args2;
        }
	}

	const char translateAction(const std::string &input){

		if(!input.compare("salt")){
			return 0;
		}
		else if(!input.compare("alt")){
			return 1;
		}
		else if(!input.compare("slat")){
			return 2;
		}
		else if(!input.compare("lat")){
			return 3;
		}
		else if(!input.compare("slon")){
			return 4;
		}
		else if(!input.compare("lon")){
			return 5;
		}
        else if(!input.compare("sman")){
            return 6;
        }
        else if(!input.compare("smanv")){
            return 7;
        }
		else{
			return -1;
		}
	}
}


CommandInterpreter::CommandInterpreter(Logger& logger) : logger(logger){}
CommandInterpreter::~CommandInterpreter(){}


/**
 * Interprets the entire input string, returns true if it finds it valid, false otherwise.
 *
 * @param input
 * @return True if interpreted correctly and command is recognized.
 */
bool CommandInterpreter::interpret(const std::string &input){

	std::stringstream ss;
	const std::vector<std::string> args = vectorize(input);
	//std::vector<float> &data = this->command.values;

	/* Translate the action, return if invalid */
	char action = translateAction(args[0]);

	/* Pack transmission based on command (futureproofing?)*/
	switch(action){
		case -1:
			return false;
			break;

		/* SALT */
		case 0:
			if(args.size() == 2){
				/* Update ALT */
				this->command.setTargetAltitude(strtod(args[1].c_str(), NULL));
				ss << "Altitude set to: " << this->command.getPacket()[TARGET_POS_ALT] << "!\n";
				std::cerr << ss.str();
			}
			else{
				//ERROR
			}
			break;

		/* ALT */
		case 1:
			//TODO:
			break;

		/* SLAT */
		case 2:
			if(args.size() == 2){
				/* Update LAT */
				this->command.setTargetLatitude(strtod(args[1].c_str(), NULL));
				ss << "Latitude set to: " << this->command.getPacket()[TARGET_POS_LAT] << "!\n";
				std::cerr << ss.str();
			}
			else{
				//ERROR
			}
			break;

		/* LAT */
		case 3:
			//TODO:
			break;

		/* SLON */
		case 4:
			if(args.size() == 2){
				/* Update LON */
				this->command.setTargetLongitude(strtod(args[1].c_str(), NULL));
				ss << "Longitude set to: " << this->command.getPacket()[TARGET_POS_LON] << "!\n";
				std::cerr << ss.str();
			}
			else{
				//ERROR
			}
			break;

		/* LON */
		case 5:
			//TODO:
			break;

		/* SMAN */
		case 6:
			if(!args[1].compare("false")){
				this->command.setManualThrottle(false);
				ss << "Manual Throttle disabled!\n";
				std::cerr << ss.str();
			}
			else if(!args[1].compare("true")){
				this->command.setManualThrottle(true);
				ss << "Manual Throttle enabled!\n";
				std::cerr << ss.str();
			}
			else{
				ss << "Unrecognized Manual Throttle!\n";
				std::cerr << ss.str();
			}
			break;

		/* SMANV */
		case 7:
			this->command.setManualThrottle(strtod(args[1].c_str(), NULL));
			ss << "Manual Throttle level set to: " << this->command.getPacket()[MANUAL_THROTTLE] << "!\n";
			std::cerr << ss.str();
			break;

		default:
			return false;
	}

	return true;
}

