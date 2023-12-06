#include "blank.h"
#include "piece.h"
#include <string>

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

Blank::Blank(int index): Piece{index, true}{}

Blank::~Blank(){};

bool Blank::validMove(const std::string &start, const std::string &end, Piece ** b) const {
	return false;
}

bool Blank::isBlank() const {
	return true;
}

char Blank::PT() const {
	return isWhiteSquare(squarelocation()) ? ' ' : '_' ;
}

