#include <string>
#include "piece.h"
#include "rook.h"

// 2 Parameter ctor
Rook::Rook(int pos, bool isWhite) : Piece{pos, isWhite}, firstMove{true} {}

// determines if a Rook can move to the desired end coordinate
bool Rook::validMove(const std::string &start, const std::string &end, Piece ** b) const {
	if((start[0] < 'a')||(start[0] > 'h')||(start[1] < '1')||(start[1] > '8')) return false;
	if((end[0] < 'a')||(end[0] > 'h')||(end[1] < '1')||(end[1] > '8')) return false;
	int begin = getPos(start);
	int fin = getPos(end);

	// Rook is moving upwards
	if ((begin % 8 == fin % 8) && begin > fin) {
		begin -= 8;
		while (begin != fin) {
			if (!b[begin]->isEmpty()) {
				return false;
			}
			begin -=8;
		}
		if (b[begin]->isEmpty()) {
			return true;
		}
		else if (!b[begin]->isEmpty() && b[begin]->isWhite() == isWhite()) {
			return false;
		}
		else {
			return true;
		}
	}

	// Rook is moving downwards
	else if ((begin % 8 == fin % 8) && begin < fin) {
		begin += 8;
		while (begin != fin) {
			if (!b[begin]->isEmpty()) {
				return false;
			}
			begin +=8;
		}
		if (b[begin]->isEmpty()) {
			return true;
		}
		else if (!b[begin]->isEmpty() && b[begin]->isWhite() == isWhite()) {
			return false;
		}
		else {
			return true;
		}
	}

	// Rook is moving rightwards
	else if ((begin / 8) == (fin / 8) && (begin > fin)) {
		begin--;
		while (begin != fin) {
			if (!b[begin]->isEmpty()) {
				return false;
			}
			begin--;
		}
		if (b[begin]->isEmpty()) {
			return true;
		}
		else if (!b[begin]->isEmpty() && b[begin]->isWhite() == isWhite()) {
			return false;
		}
		else {
			return true;
		}	
	}

	// Rook is moving leftwards
	else if ((begin / 8) == (fin / 8) && (begin < fin)) {
		begin++;
		while (begin != fin) {
			if (!b[begin]->isEmpty()) {
				return false;
			}
			begin++;
		}
		if (b[begin]->isEmpty()) {
			return true;
		}
		else if (!b[begin]->isEmpty() && b[begin]->isWhite() == isWhite()) {
			return false;
		}
		else {
			return true;
		}	
	}
	else {
		return false;
	}
}

// returns a char representin a Rook depending on whose turn it is
char Rook::Type() const {
	return isWhite() ? 'R' : 'r';
}

// returns if a Rook is empty
bool Rook::isEmpty() const {
	return false;
}

// sets the firstMove field to false
void Rook::moved() {
	firstMove = false;
}

// returns the firstMove field on a Rook object
bool Rook::first() const {
	return firstMove;
}
