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
bool Pawn::validMove(const std::string &start,const std::string &end, Piece ** b) const {
	if((start[0] < 'a')||(start[0] > 'h')||(start[1] < '1')||(start[1] > '8')) return false;
	if((end[0] < 'a')||(end[0] > 'h')||(end[1] < '1')||(end[1] > '8')) return false;
	int begin = getPos(start);
	int fin = getPos(end);

	// is the Pawn trying to move to the spot it is currently in
	if (squarelocation() != begin) {
		return false;
	}

	// white
	if (isWhite()) {

		// pawn is in column A
		if (ColA()) {

			// move forward one space if the piece is white and end is empty 
			if ((squarelocation() - 8) == fin && b[fin]->isEmpty()) {
				return true;
			}

			// move forward 2 spaces if piece is white, path is clear, and pawn hasn't been moved yet
			else if ((squarelocation() - 16) == fin && b[fin+8]->isEmpty() && b[fin]->isEmpty() && firstMove) {
				return true;
			}

			// move diagonally if the piece is white and capturing another piece
			else if ((squarelocation() - 7) == fin && !(b[fin]->isEmpty())) {
				return true;
			}
		}

		// pawn is in column H
		else if (ColH()) {

			// move forward one space if the piece is white and end is empty
			if ((squarelocation() - 8) == fin && b[fin]->isEmpty()) {
				return true;
			}

			// move forward two spaces if the piece is white, the path is clear and the pawn has not moved yet
			else if ((squarelocation() - 16) == fin && b[fin+8]->isEmpty() && b[fin]->isEmpty() && firstMove) {
				return true;
			}

			// move diagonally if the piece is white and capturing another piece
			else if ((squarelocation() - 9) == fin && !(b[fin]->isEmpty())) {
				return true;
			}
		}

		// if the pawn is in column B - G
		else if ((squarelocation() - 8) == fin && b[fin]->isEmpty()) {
				// move forward one space if the piece is white and end is empty
				return true;
		}

		// move forward two spaces if the piece is white, the path is clear and the pawn has not moved yet
		else if ((squarelocation() - 16) == fin && b[fin+8]->isEmpty() && b[fin]->isEmpty() && firstMove) {
				return true;
		}

		// move diagonally if the piece is white and capturing another piece
		else if ((squarelocation() - 9) == fin && !(b[fin]->isEmpty())) {
				return true;
		}

		// move diagonally if the piece is white and capturing another piece
		else if((squarelocation() - 7) == fin && !(b[fin]->isEmpty())) {
				return true;
		}
	}

	// black pawn
	else {

		// pawn is in column A
		if (ColA()) {

			// move forward one space if the piece is black and end is empty
			if ((squarelocation() + 8) == fin && b[fin]->isEmpty()) {
				return true;
			}

			// move forward two spaces if the piece is black, the path is clear and the pawn has not moved yet
			else if ((squarelocation() + 16) == fin && b[fin-8]->isEmpty() && b[fin]->isEmpty() && firstMove) {
				return true;
			}

			// move diagonally if the piece is black and capturing another piece
			else if ((squarelocation() + 9) == fin && !(b[fin]->isEmpty())) {
				return true;
			}
		}

		// pawn is in column H
		else if (ColH()) {

			// move forward one space if the piece is black and end is empty
			if ((squarelocation() + 8) == fin && b[fin]->isEmpty()) {
				return true;
			}

			// move forward two spaces if the piece is black, the path is clear and the pawn has not moved yet
			else if ((squarelocation() + 16) == fin && b[fin-8]->isEmpty() && b[fin]->isEmpty() && firstMove) {
				return true;
			}

			// move diagonally if the piece is black and capturing another piece
			else if ((squarelocation() + 7) == fin && !(b[fin]->isEmpty())) {
				return true;
			}
		}

		// if the pawn is in column B - G
		else if ((squarelocation() + 8) == fin && b[fin]->isEmpty()) {
				// move forward one space if the piece is black and end is empty
				return true;
		}

		// move forward two spaces if the piece is black, the path is clear and the pawn has not moved yet
		else if ((squarelocation() + 16) == fin && b[fin-8]->isEmpty() && b[fin]->isEmpty() && firstMove) {
				return true;
		}

		// move diagonally if the piece is black and capturing another piece
		else if ((squarelocation() + 9) == fin && !(b[fin]->isEmpty())) {
				return true;
		}

		// move diagonally if the piece is black and capturing another piece
		else if ((squarelocation() + 7) == fin && !(b[fin]->isEmpty())) {
				return true;
		}
	}
	return false;
}

// returns the char representing a Pawn for a player's turn
char Pawn::Type() const {
	return isWhite() ? 'P' : 'p';
}

