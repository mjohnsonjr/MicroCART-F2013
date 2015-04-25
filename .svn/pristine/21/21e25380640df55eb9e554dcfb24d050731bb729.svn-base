/*
 * Logger.h
 *
 *  Created on: Mar 16, 2014
 *      Author: michael
 */

#ifndef LOGGER_H_
#define LOGGER_H_
#include <fstream>

class Logger {
public:
	Logger(std::ofstream&);
	virtual ~Logger();
	void log(const std::string&);
	friend std::ostream& operator<<(Logger& log, const std::string& str);
	friend std::ostream& operator<<(Logger& log, const volatile float fl);

private:
	std::ofstream& stream;
};

#endif /* LOGGER_H_ */
