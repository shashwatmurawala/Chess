#include <string>
#include "piece.h"
#include "queen.h"
#include "rook.h"
#include "bishop.h"
#include <iostream>

static bool onRight(int i){
	return (7 == (i % 8)) ? true : false;
}

static bool onLeft(int i){
	return (0 == (i % 8)) ? true : false;
}

Queen::Queen(int pos, bool isWhite): Piece(pos,isWhite){}

bool Queen::validMove(const std::string &start, const std::string &end, Piece ** b) const{
	if((start[0] < 'a')||(start[0] > 'h')||(start[1] < '1')||(start[1] > '8')) return false;
	if((end[0] < 'a')||(end[0] > 'h')||(end[1] < '1')||(end[1] > '8')) return false;
	int org = arrayloc(start);
	int newloc = arrayloc(end);
	bool col = isWhite();
	Rook rmoves{org, col};
	Bishop dmoves{org, col};
	if (rmoves.validMove(start, end, b)){
		return true;
	}else if(dmoves.validMove(start, end, b)){
		return true;
	}else if (!(org==0) && !(org == 63) && (org % 7 == newloc % 7) && org < newloc) {
		while (true) {
			org += 7;
			if(org > 63){
				return false;
			}
			if (org == newloc && (b[org]->isEmpty() || (isWhite() != b[org]->isWhite()))) {
				return true;
			}
			else if (org == newloc && b[org]->isEmpty()) {
				return true;
			}
			else if (!b[org]->isEmpty()) {
				return false;
			}
		}
	}else if (!(org==0) && !(org == 63) && (org % 7 == newloc % 7) && org > newloc) {
		while (true) {
			org -= 7;
			if(org < 0){
				return false;
			}
			if (org == newloc && (b[org]->isEmpty() || (isWhite() != b[org]->isWhite()))) {
				return true;
			}
			else if (org == newloc && b[org]->isEmpty()) {
				return true;
			}
			else if (!b[org]->isEmpty()) {
				return false;
			}
		}
	}
	else {
		return false;
	}
}

char Queen::PT() const {
	return isWhite() ? 'Q' : 'q';
}

bool Queen::isEmpty() const {
	return false;
}
