/*
 * Logger.cpp
 *
 *  Created on: Mar 16, 2014
 *      Author: michael
 */

#include "Logger.h"
#include <iostream>
#include <sstream>

Logger::Logger(std::ofstream& fs) : stream(fs) {

}

Logger::~Logger() {

}

void Logger::log(const std::string& str){

	std::cerr << str;
	stream << str;
}

/* Any stream operator overloads.. may end up being a lot */
std::ostream& operator<<(Logger& log, const std::string& str){
	log.log(str);
    return log.stream;
}

std::ostream& operator<<(Logger& log, const volatile float fl){
	std::stringstream ss;
	ss << fl;
	log.log(ss.str());
	return log.stream;
}


