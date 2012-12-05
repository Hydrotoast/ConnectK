#ifndef LOGGER_H
#define LOGGER_H

#include "BoardState.h"
#include <string>

class Logger {
public:
	static Logger& instance();
	void log(std::string message);
	void logState(unsigned int depth, std::string message);
	void logMove(unsigned int depth, Cell move, std::string message);
};

#endif