#include <string>
#include "board.h"
#include "knight.h"

Knight::Knight(int pos, bool isWhite): Piece(pos, isWhite) {}

bool Knight::isBlank() const{
	return false;
}

bool Knight::validMove(const std::string &start,const std::string &end, Piece ** b) const {
	int org_x = arrayloc(start) % 8;
	int org_y = arrayloc(start) / 8;
	int newloc_x = arrayloc(end) % 8;
	int newloc_y = arrayloc(end) / 8;
	if((start[0] < 'a')||(start[0] > 'h')||(start[1] < '1')||(start[1] > '8')) return false;
	if((end[0] < 'a')||(end[0] > 'h')||(end[1] < '1')||(end[1] > '8')) return false;
	if(!b[arrayloc(end)]->isBlank() && isWhite() == b[arrayloc(end)]->isWhite()){
		return false;
	}
	if (abs(org_x - newloc_x) == 1 && abs(org_y - newloc_y) == 2 ) {
		return true;
	}
	else if (abs(org_x - newloc_x) == 2 && abs(org_y - newloc_y) == 1){
		return true;
	}
	else {
		return false;
	}
}

char Knight::PT() const {
	return isWhite() ? 'N' : 'n';
}
