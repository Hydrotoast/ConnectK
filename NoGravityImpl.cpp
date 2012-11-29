#include "stdafx.h"
#include "BoardConfig.h"
#include "NoGravityImpl.h"

using namespace std;

NoGravityImpl::NoGravityImpl(BoardState& board) :
	GravityImpl(board)
{}

list<Cell> NoGravityImpl::getAvailable() {
	list<Cell> available;
	for (size_t row = 0; row < board.config().rows; ++row)
		for (size_t col = 0; col < board.config().cols; ++col)
			if (board.at(row, col) == BLANK)
				available.push_back(Cell(row, col));
	return available;
}

bool NoGravityImpl::occupy(size_t row, size_t col, Mark m) {
	Mark& cell = board.at(row, col);
	if (cell != Mark::BLANK)
		return false;
	cell = m;
	return true;
}