#include "stdafx.h"
#include "BoardConfig.h"
#include "GravityImpl.h"

using namespace std;

GravityImpl::GravityImpl(BoardState& board) :
	board(board)
{}

list<Cell> GravityImpl::getAvailable() {
	list<Cell> available;
	for (size_t col = 0; col < board.config().cols; ++col)
		for (size_t row = board.config().rows - 1; row >= 0; --row)
			if (board.at(row, col) == BLANK)
				available.push_back(Cell(row, col));
	return available;
}

bool GravityImpl::occupy(size_t row, size_t col, Mark m) {
	do {
		Mark& cell = board.at(row++, col);
		if (cell == Mark::BLANK) {
			cell = m;
			return true;
		}
	} while (row < board.config().rows);
	return false;
}