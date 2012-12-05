#include "stdafx.h"
#include "AINoGravityImpl.h"
#include "BoardState.h"
#include <cmath>
#include <list>

using namespace std;

AINoGravityImpl::AINoGravityImpl(const BoardState& state) :
	AIGravityImpl(state)
{}

unsigned int AINoGravityImpl::calcInitialDepth() {
	return static_cast<unsigned int>(log(5000) /  log(state.config().rows * state.config().cols - state.numOccupied()));
}

double AINoGravityImpl::distFromCenter(const Cell& cell) {
	double centerRow = getCenterRow();
	double centerCol = getCenterCol();
	double cellRow = static_cast<double>(cell.row);
	double cellCol = static_cast<double>(cell.col);
	double dist = abs(sqrt((cellCol - centerCol) * (cellCol - centerCol) + (cellRow - centerRow) * (cellRow - centerRow))); // Calculate distance using distance formula and cast the result to int
																									// Squaring removes negatives
	return dist;
}

double AINoGravityImpl::getCenterRow() {
	return static_cast<double>((state.config().rows-1))/2.0;	// center row (or line) of the gameboard
}

double AINoGravityImpl::getCenterCol() {
	return static_cast<double>((state.config().cols-1))/2.0;	// center column (or line) of the gameboard
}