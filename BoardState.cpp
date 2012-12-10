#include "stdafx.h"
#include "BoardState.h"
#include "BoardConfig.h"

#include "GravityImpl.h"
#include "NoGravityImpl.h"
#include "EndGameException.h"

#include <sstream>

using namespace std;

BoardState::BoardState(BoardConfig config) : 
	config_(config), numOccupied_(0), winState_(WinState::NO_WINNER)
{
	board_ = new Mark[config.rows * config.cols];
	for (size_t row = 0; row < config.rows; ++row)
		for (size_t col = 0; col < config.cols; ++col)
			board_[row * config.cols + col] = Mark::BLANK;
	gravity_ = (config.gravityFlag) ? new GravityImpl(*this) : new NoGravityImpl(*this);
}

BoardState::~BoardState() {
	delete board_;
	delete gravity_;
}

BoardState::BoardState(const BoardState& board) :
	config_(board.config_), numOccupied_(board.numOccupied_), winState_(board.winState_)
{
	this->board_ = new Mark[config_.rows * config_.cols];
	this->gravity_ = board.gravity_->clone(*this);
	for (size_t row = 0; row < config_.rows; ++row)
		for (size_t col = 0; col < config_.cols; ++col)
			this->board_[row * config_.cols + col] = board.board_[row * config_.cols + col];
}

BoardState& BoardState::operator=(const BoardState& board) {
	if (&board == this)
		return *this;

	delete board_;
	delete gravity_;

	this->config_ = board.config_;
	this->numOccupied_ = board.numOccupied_;
	this->winState_ = board.winState_;
	this->board_ = new Mark[config_.rows * config_.cols];
	this->gravity_ = board.gravity_->clone(*this);
	for (size_t row = 0; row < config_.rows; ++row)
		for (size_t col = 0; col < config_.cols; ++col)
			this->board_[row * config_.cols + col] = board.board_[row * config_.cols + col];
	return *this;
}

const BoardConfig& BoardState::config() const {
	return config_;
}

size_t BoardState::numOccupied() const {
	return numOccupied_;
}

WinState BoardState::winState() const {
	return winState_;
}

bool BoardState::isOccupied(size_t row, size_t col) {
	return board_[row * config_.cols + col] == Mark::BLANK;
}

bool BoardState::inRange(size_t row, size_t col) {
	return row >= 0 && col >= 0 && 
		row < config_.rows && col < config_.cols;
}

Mark& BoardState::at(size_t row, size_t col) {
	return board_[row * config_.cols + col];
}

std::list<Cell> BoardState::getAvailable() {
	if (winState_ != WinState::NO_WINNER)
		throw EndGameException();
	return gravity_->getAvailable();
}

bool BoardState::occupy(size_t row, size_t col, Mark m) {
	if (winState_ != WinState::NO_WINNER)
		throw EndGameException();
	if (!inRange(row, col))
		return false;
	numOccupied_++;
	return gravity_->occupy(row, col, m);
}

WinState BoardState::isEnd() {
	if (winState_ != WinState::NO_WINNER)
		return winState_;
	if (isTie()) {
		winState_ = WinState::DRAW;
		return winState_;
	}

	int eval = 0;

	/* Check all the horizontal groups of config_.kLength */
	for (size_t row = 0; row < config_.rows; row++) {
		for (size_t j = 0; j + config_.kLength - 1 < config_.cols; j++) {
			eval = 0;
			for (size_t k = 0; k < config_.kLength; k++) {
				eval += at(row, j + k);
			}
			if (eval == config_.kLength * Mark::A) {
				winState_ = WinState::A_WIN;
				return WinState::A_WIN;
			}
			else if (eval == config_.kLength * Mark::B) {
				winState_ = WinState::B_WIN;
				return WinState::B_WIN;
			}
		}
	}

	// Vertical wins
	for (size_t col = 0; col < config_.cols; col++) {
		for (size_t i = 0; i + config_.kLength - 1 < config_.rows; i++) {
			eval = 0;
			for (size_t k = 0; k < config_.kLength; k++) {
				eval += at(i + k, col);
			}
			if (eval == config_.kLength * Mark::A) {
				winState_ = WinState::A_WIN;
				return WinState::A_WIN;
			}
			else if (eval == config_.kLength * Mark::B) {
				winState_ = WinState::B_WIN;
				return WinState::B_WIN;
			}
		}
	}

	/// Forward diagonal wins "\"
	for (size_t row = 0; row + config_.kLength - 1 < config_.rows; row++) {
		for (size_t col = 0; col + config_.kLength - 1 < config_.cols; col++) {
			eval = 0;
			for (size_t i = 0; i < config().kLength; i++) {
				eval += at(row + i, col + i);
			}
			if (eval == config_.kLength * Mark::A) {
				winState_ = WinState::A_WIN;
				return WinState::A_WIN;
			}
			else if (eval == config_.kLength * Mark::B) {
				winState_ = WinState::B_WIN;
				return WinState::B_WIN;
			}
		}
	}
	
	/// Backward diagonal wins "/"
	for (size_t row = 0; row + config_.kLength - 1 < config_.rows; row++) {
		for (size_t col = 0; col + config_.kLength - 1 < config_.cols; col++) {
			eval = 0;
			for (size_t i = 0; i < config().kLength; i++) {
				eval += at(row + (config().kLength - 1) - i, col + i);
			}
			if (eval == config_.kLength * Mark::A) {
				winState_ = WinState::A_WIN;
				return WinState::A_WIN;
			}
			else if (eval == config_.kLength * Mark::B) {
				winState_ = WinState::B_WIN;
				return WinState::B_WIN;
			}
		}
	}

	return WinState::NO_WINNER;
}

bool BoardState::isTie() {
	return numOccupied_ == config_.rows * config_.cols; 
}

string BoardState::toString() {
	ostringstream oss;
	oss << "BOARD" << endl;
	for (size_t row = 0; row < config_.rows; row++) {
		for (size_t col = 0; col < config_.cols; col++) {
			if (at(row, col) == Mark::A)
				oss << 'A';
			else if (at(row, col) == Mark::B)
				oss << 'B';
			else
				oss << '-';
		}
		oss << endl;
	}
	return oss.str();
}

size_t BoardState::hash() {
	size_t value = 0;
	for (size_t row = 0; row < config_.rows; row++)
		for (size_t col = 0; col < config_.cols; col++)
			value += at(row, col);
	return value;
}
