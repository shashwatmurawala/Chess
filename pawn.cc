#include <string>
#include "piece.h"
#include "pawn.h"
#include "board.h"

// 2 Parameter ctor
Pawn::Pawn(int pos, bool isWhite): Piece{pos,isWhite}, firstMove{true} {}

// returns if a Pawn is empty
bool Pawn::isEmpty() const {
	return false;
}

// returns the firstMove field on a Pawn object
bool Pawn::first() const {
	return firstMove;
}

// helper to en passant
void Pawn::moved() {
	firstMove = false;
}

// determines whether a Pawn can move to the desired end coordinates
bool Pawn::canMove(const std::string &start,const std::string &end, Piece ** b) const {
	int begin = getPos(start);
	int fin = getPos(end);

	// is the Pawn trying to move to the spot it is currently in
	if (posn() != begin) {
		return false;
	}

	// white
	if (isWhite()) {

		// pawn is in column A
		if (onLeftEdge()) {

			// move forward one space if the piece is white and end is empty 
			if ((posn() - 8) == fin && b[fin]->isEmpty()) {
				return true;
			}

			// move forward 2 spaces if piece is white, path is clear, and pawn hasn't been moved yet
			else if ((posn() - 16) == fin && b[fin+8]->isEmpty() && b[fin]->isEmpty() && firstMove) {
				return true;
			}

			// move diagonally if the piece is white and capturing another piece
			else if ((posn() - 7) == fin && !(b[fin]->isEmpty())) {
				return true;
			}
		}

		// pawn is in column H
		else if (onRightEdge()) {

			// move forward one space if the piece is white and end is empty
			if ((posn() - 8) == fin && b[fin]->isEmpty()) {
				return true;
			}

			// move forward two spaces if the piece is white, the path is clear and the pawn has not moved yet
			else if ((posn() - 16) == fin && b[fin+8]->isEmpty() && b[fin]->isEmpty() && firstMove) {
				return true;
			}

			// move diagonally if the piece is white and capturing another piece
			else if ((posn() - 9) == fin && !(b[fin]->isEmpty())) {
				return true;
			}
		}

		// if the pawn is in column B - G
		else if ((posn() - 8) == fin && b[fin]->isEmpty()) {
				// move forward one space if the piece is white and end is empty
				return true;
		}

		// move forward two spaces if the piece is white, the path is clear and the pawn has not moved yet
		else if ((posn() - 16) == fin && b[fin+8]->isEmpty() && b[fin]->isEmpty() && firstMove) {
				return true;
		}

		// move diagonally if the piece is white and capturing another piece
		else if ((posn() - 9) == fin && !(b[fin]->isEmpty())) {
				return true;
		}

		// move diagonally if the piece is white and capturing another piece
		else if((posn() - 7) == fin && !(b[fin]->isEmpty())) {
				return true;
		}
	}

	// black pawn
	else {

		// pawn is in column A
		if (onLeftEdge()) {

			// move forward one space if the piece is black and end is empty
			if ((posn() + 8) == fin && b[fin]->isEmpty()) {
				return true;
			}

			// move forward two spaces if the piece is black, the path is clear and the pawn has not moved yet
			else if ((posn() + 16) == fin && b[fin-8]->isEmpty() && b[fin]->isEmpty() && firstMove) {
				return true;
			}

			// move diagonally if the piece is black and capturing another piece
			else if ((posn() + 9) == fin && !(b[fin]->isEmpty())) {
				return true;
			}
		}

		// pawn is in column H
		else if (onRightEdge()) {

			// move forward one space if the piece is black and end is empty
			if ((posn() + 8) == fin && b[fin]->isEmpty()) {
				return true;
			}

			// move forward two spaces if the piece is black, the path is clear and the pawn has not moved yet
			else if ((posn() + 16) == fin && b[fin-8]->isEmpty() && b[fin]->isEmpty() && firstMove) {
				return true;
			}

			// move diagonally if the piece is black and capturing another piece
			else if ((posn() + 7) == fin && !(b[fin]->isEmpty())) {
				return true;
			}
		}

		// if the pawn is in column B - G
		else if ((posn() + 8) == fin && b[fin]->isEmpty()) {
				// move forward one space if the piece is black and end is empty
				return true;
		}

		// move forward two spaces if the piece is black, the path is clear and the pawn has not moved yet
		else if ((posn() + 16) == fin && b[fin-8]->isEmpty() && b[fin]->isEmpty() && firstMove) {
				return true;
		}

		// move diagonally if the piece is black and capturing another piece
		else if ((posn() + 9) == fin && !(b[fin]->isEmpty())) {
				return true;
		}

		// move diagonally if the piece is black and capturing another piece
		else if ((posn() + 7) == fin && !(b[fin]->isEmpty())) {
				return true;
		}
	}
	return false;
}

// returns the char representing a Pawn for a player's turn
char Pawn::Type() const {
	return isWhite() ? 'P' : 'p';
}

