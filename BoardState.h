#ifndef BOARD_STATE_H
#define BOARD_STATE_H

#include "BoardConfig.h"
#include "Mark.h"

#include <list>
#include <string>

class GravityImpl;

enum WinState {
	A_WIN, B_WIN, DRAW, NO_WINNER
};

class BoardState {
public:
	explicit BoardState(BoardConfig config);
	~BoardState();
	BoardState(const BoardState& board);
	BoardState& operator=(const BoardState& board);
	BoardState clone();

	const BoardConfig& config() const;
	size_t numOccupied() const;
	WinState winState() const;

	bool isOccupied(size_t row, size_t col);
	bool inRange(size_t row, size_t col);
	
	Mark& at(size_t row, size_t col);

	std::list<Cell> getAvailable();
	bool occupy(size_t row, size_t col, Mark m);

	WinState isEnd();
	bool isTie();

	size_t hash();
	std::string toString();
protected:
	BoardConfig config_;
	size_t numOccupied_;
	WinState winState_;

	Mark* board_;
	GravityImpl* gravity_;
};

#endif