#include <string>
#include "piece.h"
#include "king.h"

using namespace std;

King::King(int arrayloc, bool white): Piece{arrayloc, white}, firstMove{true} {}

King::~King(){}

void King::moved(){
	firstMove = false;
}

bool King::validMove(const string &start, const string &end, Piece ** b) const {
	if((start[0] < 'a')||(start[0] > 'h')||(start[1] < '1')||(start[1] > '8')) return false;
	if((end[0] < 'a')||(end[0] > 'h')||(end[1] < '1')||(end[1] > '8')) return false;
	int org = arrayloc(start);
	int newloc = arrayloc(end);

	if (!b[newloc]->isBlank() && (isWhite() == b[newloc]->isWhite())) {
		return false;
	}else if (first() && 2 == abs(org - newloc)) {
		if (isWhite()){
			if ((b[61]->isBlank() && b[62]->isBlank() &&
				b[63]->PT() == 'R' && newloc == 62 &&
				org == 60) || 
				(b[59]->isBlank() && b[58]->isBlank() &&
				b[57]->isBlank() && b[56]->PT() == 'R' 
				&& newloc == 58 && org == 60)) {
					return true;
			}
			else {
				return false;
			}
		} else{
			if ((b[5]->isBlank() && b[6]->isBlank() &&
				b[7]->PT() == 'R' && org == 4 &&
				newloc == 6) ||
				(b[1]->isBlank() && b[2]->isBlank() &&
				b[3]->isBlank() && b[0]->PT() == 'R' 
				&& newloc == 2 && org == 4)) {
					return true;
			}

			else {
				return false;
			}
		}
	}else if (0 == org) {
		return (newloc == 1 || newloc == 9 || newloc == 8) ? true : false;
	}else if (7 == org) {
		return (newloc == 6 || newloc == 14 || newloc == 15) ? true : false;
	}else if (56 == org) {
		return (newloc == 48 || newloc == 49 || newloc == 57) ? true : false;
	}else if (63 == org) {
		return (newloc == 62 || newloc == 55 || newloc == 54) ? true : false;
	}else if (ColH()) {
		return (newloc == (org - 1) || newloc == (org - 8) || 
				newloc == (org + 8) || newloc == (org + 7) ||
				newloc == (org - 9))
				? true : false;
	}else if (ColA()) {
		return (newloc == (org - 1) || newloc == (org - 8) || 
				newloc == (org + 8) || newloc == (org + 7) ||
				newloc == (org - 9))
				? true : false; 
	}else if (Row1()) {
		return (newloc == (org - 8) || newloc == (org - 1) || 
				newloc == (org + 1) || newloc == (org - 7) ||
				newloc == (org - 9)) 
				? true : false;
	}else if (Row8()) {
		return (newloc == (org + 8) || newloc == (org - 1) || 
				newloc == (org + 1) || newloc == (org + 7) ||
				newloc == (org + 9))
				? true : false;
	}else{
		return (newloc == (org - 1) || newloc == (org + 1) || 
				newloc == (org - 8) || newloc == (org + 8) ||
				newloc == (org - 7) || newloc == (org + 7) || 
				newloc == (org - 9) || newloc == (org + 9))
				? true : false;
	}
}

bool King::first() const {
	return firstMove;
}

bool King::isBlank() const {
	return false;
}

char King::PT() const {
	return isWhite() ? 'K' : 'k';
}
