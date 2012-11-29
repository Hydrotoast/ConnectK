#ifndef MARK_H
#define MARK_H

enum Mark {
	BLANK, A, B
};

struct Cell {
	size_t row;
	size_t col;

	Cell(size_t row, size_t col);
};

#endif