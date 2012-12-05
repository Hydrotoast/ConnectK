#ifndef AI_GRAVITY_IMPL_H
#define AI_GRAVITY_IMPL_H

#include "BoardState.h"

class AIGravityImpl {
public:
	AIGravityImpl(const BoardState& state);
	virtual unsigned int calcInitialDepth();
	virtual double distFromCenter(const Cell& cell); 

	virtual double getCenterRow();
	virtual double getCenterCol();
protected:
	const BoardState& state;
};

#endif