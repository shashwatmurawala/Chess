#include <string>
#include "piece.h"
#include "king.h"

using namespace std;

// 2 Parameter ctor
King::King(int index, bool white): Piece{index, white}, firstMove{true} {}

// Dtor
King::~King(){}

// sets the firstMove field to be false for castling
void King::moved(){
	firstMove = false;
}

// returns whether the King can move to the desired end coordinates
bool King::canMove(const string &start, const string &end, Piece ** b) const {
	if((start[0] < 'a')||(start[0] > 'h')||(start[1] < '1')||(start[1] > '8')) return false;
	if((end[0] < 'a')||(end[0] > 'h')||(end[1] < '1')||(end[1] > '8')) return false;
	int begin = getPos(start);
	int fin = getPos(end);

	//check if space is occupied by same team's piece
	if (!b[fin]->isEmpty() && (isWhite() == b[fin]->isWhite())) {
		return false;
	}

	// white castling
	else if (isWhite() && first() && 2 == abs(begin-fin)) {
		
		// short, or King-side castling
		if (b[61]->isEmpty() && b[62]->isEmpty() &&
			b[63]->Type() == 'R' && fin == 62 &&
			begin == 60) {
				return true;
		}

		// long, or Queen-side castling
		else if (b[59]->isEmpty() && b[58]->isEmpty() &&
			b[57]->isEmpty() && b[56]->Type() == 'R' 
			&& fin == 58 && begin == 60) {
				return true;
		}
		else {
			return false;
		}
	}

	// black castling
	else if (!isWhite() && first() && 2 == abs(begin-fin)) {
		
		// short, or King-side castling
		if (b[5]->isEmpty() && b[6]->isEmpty() &&
			b[7]->Type() == 'R' && fin == 6 &&
			begin == 4) {
				return true;
		}

		// long, or Queen-side castling
		else if (b[1]->isEmpty() && b[2]->isEmpty() &&
			b[3]->isEmpty() && b[0]->Type() == 'R' 
			&& fin == 2 && begin == 4) {
				return true;
		}
		else {
			return false;
		}
	}

	// King is on space A1
	else if (0 == begin) {
		return (fin == 1 || fin == 9 || fin == 8) ? true : false;
	}

	// King is on space A8
	else if (7 == begin) {
		return (fin == 6 || fin == 14 || fin == 15) ? true : false;
	}

	// King is on space H8
	else if (56 == begin) {
		return (fin == 48 || fin == 49 || fin == 57) ? true : false;
	}

	// King is on space H1
	else if (63 == begin) {
		return (fin == 62 || fin == 55 || fin == 54) ? true : false;
	}

	// King is on the bottom edge, B1-G1
	else if (onBottomEdge()) {
		return (fin == (begin-8) || fin == (begin-1) || 
				fin == (begin+1) || fin == (begin-7) ||
				fin == (begin-9)) 
				? true : false;
	}

	// King is on the top edge, B8-G8
	else if (onTopEdge()) {
		return (fin == (begin+8) || fin == (begin-1) || 
				fin == (begin+1) || fin == (begin+7) ||
				fin == (begin+9))
				? true : false;
	}
	else if (onRightEdge()) { // King is on H2-H7
		return (fin == (begin-1) || fin == (begin-8) || 
				fin == (begin+8) || fin == (begin+7) ||
				fin == (begin-9))
				? true : false;
	}

	// King is on the left edge, A2-A7
	else if (onLeftEdge()) {
		return (fin == (begin-1) || fin == (begin-8) || 
				fin == (begin+8) || fin == (begin+7) ||
				fin == (begin-9))
				? true : false; 
	} 

	// King is anywhere else on the board
	return (fin == (begin-1) || fin == (begin+1) || 
			fin == (begin-8) || fin == (begin+8) ||
			fin == (begin-7) || fin == (begin+7) || 
			fin == (begin-9) || fin == (begin+9))
			? true : false;
}

// returns the firstMove field of the King object
bool King::first() const {
	return firstMove;
}

// returns if the King object is empty
bool King::isEmpty() const {
	return false;
}

// returns a character for the King representing which character's turn it is.
char King::Type() const {
	return isWhite() ? 'K' : 'k';
}
