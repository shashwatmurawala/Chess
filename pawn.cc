#include <string>
#include "piece.h"
#include "pawn.h"
#include "board.h"

Pawn::Pawn(int pos, bool isWhite): Piece{pos , isWhite}, firstMove{true} {}

bool Pawn::isEmpty() const {
	return false;
}

bool Pawn::first() const {
	return firstMove;
}

void Pawn::moved() {
	firstMove = false;
}

bool Pawn::validMove(const std::string &start,const std::string &end, Piece ** b) const {
	if((start[0] < 'a')||(start[0] > 'h')||(start[1] < '1')||(start[1] > '8')) return false;
	if((end[0] < 'a')||(end[0] > 'h')||(end[1] < '1')||(end[1] > '8')) return false;
	int org = getPos(start);
	int newloc = getPos(end);

	if (squarelocation() != org) return false;

	if (isWhite()) {
		if (ColA()) {
			if (((squarelocation() - 8) == newloc && b[newloc]->isEmpty()) ||
				((squarelocation() - 16) == newloc && b[newloc+8]->isEmpty() && b[newloc]->isEmpty() && firstMove) ||
				((squarelocation() - 7) == newloc && !(b[newloc]->isEmpty()))){
				return true;
			}
		}else if (ColH()) {
			if (((squarelocation() - 8) == newloc && b[newloc]->isEmpty()) ||
				((squarelocation() - 16) == newloc && b[newloc+8]->isEmpty() && b[newloc]->isEmpty() && firstMove)||
				((squarelocation() - 9) == newloc && !(b[newloc]->isEmpty()))) {
				return true;
				}
		}else if (((squarelocation() - 8) == newloc && b[newloc]->isEmpty()) ||
				((squarelocation() - 16) == newloc && b[newloc+8]->isEmpty() && b[newloc]->isEmpty() && firstMove) ||
				((squarelocation() - 9) == newloc && !(b[newloc]->isEmpty())) ||
				((squarelocation() - 7) == newloc && !(b[newloc]->isEmpty()))) {
				return true;
		}
	}
	else {
		if (ColA()) {
			if (((squarelocation() + 8) == newloc && b[newloc]->isEmpty())||
				((squarelocation() + 16) == newloc && b[newloc-8]->isEmpty() && b[newloc]->isEmpty() && firstMove) ||
				((squarelocation() + 9) == newloc && !(b[newloc]->isEmpty()))) {
				return true;
			}
		}else if (ColH()) {
			if (((squarelocation() + 8) == newloc && b[newloc]->isEmpty()) ||
				((squarelocation() + 16) == newloc && b[newloc-8]->isEmpty() && b[newloc]->isEmpty() && firstMove) ||
				((squarelocation() + 7) == newloc && !(b[newloc]->isEmpty()))) {
				return true;
			}
		}else if (((squarelocation() + 8) == newloc && b[newloc]->isEmpty()) ||
				((squarelocation() + 16) == newloc && b[newloc - 8]->isEmpty() && b[newloc]->isEmpty() && firstMove) ||
				((squarelocation() + 9) == newloc && !(b[newloc]->isEmpty())) ||
				((squarelocation() + 7) == newloc && !(b[newloc]->isEmpty()))) {
				return true;
		}
	}
	return false;
}

char Pawn::Type() const {
	return isWhite() ? 'P' : 'p';
}

