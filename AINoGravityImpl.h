#ifndef AI_NO_GRAVITY_IMPL_H
#define AI_NO_GRAVITY_IMPL_H

#include "AIGravityImpl.h"

class AINoGravityImpl : public AIGravityImpl {
public:
	AINoGravityImpl(const BoardState& state);
	virtual unsigned int calcInitialDepth();
	virtual double distFromCenter(const Cell& cell);

	virtual double getCenterRow();
	virtual double getCenterCol();
};

#endif