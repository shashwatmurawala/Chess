#include "empty.h"
#include "piece.h"
#include <string>

// returns if the current position is the white player's square
static int isWhiteSquare(int pos){
	pos = pos % 16;
	if (pos < 8 && (pos % 2) == 0) {
		return true;
	}
	else if (pos > 7 && (pos % 2) == 1) {
		return true;
	}
	return false;
}

// 1 Parameter ctor
Empty::Empty(int index): Piece{index, true}{}

// Dtor
Empty::~Empty(){};

// determines if the Empty piece can move, but this is illogical so it returns false right away
bool Empty::canMove(const std::string &start, const std::string &end, Piece ** b) const {
	return false;
}

// returns if the current Piece is empty.
bool Empty::isEmpty() const {
	return true;
}

// returns the character representing the Black player's empty or the White player's empty.
char Empty::Type() const {
	return isWhiteSquare(posn()) ? ' ' : '_' ;
}

