/*
 * CommandInterpreter.h
 *
 *  Created on: Jan 23, 2014
 *      Author: Michael Johnson
 */

#ifndef COMMANDINTERPRETER_H_
#define COMMANDINTERPRETER_H_

#include "QuadCommand.h"
#include <iostream>
#include <vector>
#include "Logger.h"

class CommandInterpreter{

	private:
		QuadCommand command;
		Logger& logger;

	public:
		CommandInterpreter(Logger&);
		virtual ~CommandInterpreter();

		bool interpret(const std::string&);
		QuadCommand& getQuadCommand() {
			return this->command;
		}

		const QuadCommand& getQuadCommand() const {
			return this->command;
		}

};



#endif /* COMMANDINTERPRETER_H_ */
