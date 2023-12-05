#include <string>
#include "board.h"
#include "knight.h"

Knight::Knight(int pos, bool isWhite): Piece(pos, isWhite) {}

bool Knight::isEmpty() const{
	return false;
}

bool Knight::validMove(const std::string &start,const std::string &end, Piece ** b) const {
	if((start[0] < 'a')||(start[0] > 'h')||(start[1] < '1')||(start[1] > '8')) return false;
	if((end[0] < 'a')||(end[0] > 'h')||(end[1] < '1')||(end[1] > '8')) return false;
	if(!b[getPos(end)]->isEmpty() && isWhite() == b[getPos(end)]->isWhite()){
		return false;
	}
	int org_x = getPos(start) % 8;
	int org_y = getPos(start) / 8;
	int newloc_x = getPos(end) % 8;
	int newloc_y = getPos(end) / 8;
	if ((abs(org_x - newloc_x) == 1 && abs(org_y - newloc_y) == 2 ) ||
		(abs(org_x - newloc_x) == 2 && abs(org_y - newloc_y) == 1)) {
		return true;
	}
	else {
		return false;
	}
}

char Knight::Type() const {
	return isWhite() ? 'N' : 'n';
}
