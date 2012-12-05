#include "stdafx.h"
#include "AIGravityImpl.h"
#include "BoardState.h"
#include <cmath>

using namespace std;

AIGravityImpl::AIGravityImpl(const BoardState& state) :
	state(state)
{}

unsigned int AIGravityImpl::calcInitialDepth() {
	return static_cast<unsigned int>(log(5000) / log(state.config().rows));
}

double AIGravityImpl::distFromCenter(const Cell& cell) {
	double centerCol = getCenterCol();
	double cellCol = static_cast<double>(cell.col);
	double dist = abs(cellCol - centerCol); // Calculate distance using distance formula and cast the result to int
																									// Squaring removes negatives
	return dist;
}

double AIGravityImpl::getCenterRow() {
	return static_cast<double>((state.config().rows-1))/2.0;	// center row (or line) of the gameboard
}

double AIGravityImpl::getCenterCol() {
	return static_cast<double>((state.config().cols-1))/2.0;	// center column (or line) of the gameboard
}
