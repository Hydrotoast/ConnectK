#include "stdafx.h"
#include "RuntimeState.h"
#include <sstream>

using namespace std;

RuntimeState& RuntimeState::instance() {
	static RuntimeState instance;
	return instance;
}

void RuntimeState::reset() {
	depthStarted = 0;
	depthReached = 0;
	nodesEvaluated = 0;
	nodesPruned = 0;
	nodesSeen = 0;
}

RuntimeState::RuntimeState() :
	depthStarted(0),
	depthReached(0),
	nodesEvaluated(0),
	nodesPruned(0),
	nodesSeen(0)
{}

string RuntimeState::toString() {
	ostringstream oss;
	oss << "Depth Started:\t\t" << depthStarted << endl
		<< "Depth Reached:\t\t" << depthReached << endl
		<< "Nodes Evaluated:\t" << nodesEvaluated << endl
		<< "Nodes Pruned:\t\t" << nodesPruned << endl
		<< "Nodes Seen:\t\t\t" << nodesSeen << endl;
	return oss.str();	
}
