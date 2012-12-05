#include "stdafx.h"
#include "Logger.h"
#include <iostream>

using namespace std;

Logger& Logger::instance() {
	static Logger instance;
	return instance;
}

void Logger::log(string message) {
	TRACE("%s\n", (LPCTSTR)message.c_str());
}

void Logger::logState(unsigned int depth, string message) {
	TRACE("%d: %s\n", depth, (LPCTSTR)message.c_str());
}

void Logger::logMove(unsigned int depth, Cell move, string message) {
	TRACE("%d: (%d, %d) %s\n", depth, move.row, move.col, (LPCTSTR)message.c_str());
}