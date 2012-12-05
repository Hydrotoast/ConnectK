#ifndef RUNTIME_STATE_H
#define RUNTIME_STATE_H

#include <string>

class RuntimeState {
public:
	unsigned int depthStarted;
	unsigned int depthReached;
	unsigned int nodesEvaluated;
	unsigned int nodesPruned;
	unsigned int nodesSeen;

	static RuntimeState& instance();
	void reset();

	std::string toString();
private:
	RuntimeState();
};


#endif