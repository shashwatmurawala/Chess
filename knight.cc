#include <string>
#include "board.h"
#include "knight.h"

// 2 Parameter ctor
Knight::Knight(int pos, bool isWhite): Piece(pos, isWhite) {}

// returns whether a Knight is empty
bool Knight::isEmpty() const{
	return false;
}

// determines if a Knight can move to the desired end coordinates
bool Knight::canMove(const std::string &start,const std::string &end, Piece ** b) const {
	if((start[0] < 'a')||(start[0] > 'h')||(start[1] < '1')||(start[1] > '8')) return false;
	if((end[0] < 'a')||(end[0] > 'h')||(end[1] < '1')||(end[1] > '8')) return false;
	int begin_x = getPos(start) % 8;
	int begin_y = getPos(start) / 8;
	int fin_x = getPos(end) % 8;
	int fin_y = getPos(end) / 8;
	if(!b[getPos(end)]->isEmpty() && isWhite() == b[getPos(end)]->isWhite()){
		return false;
	}
	// position changes x +/- 1 and y +/- 2
	if (abs(begin_x - fin_x) == 1 && abs(begin_y - fin_y) == 2 ) {
		return true;
	}

	// position changes x +/- 2 and y +/- 1
	else if (abs(begin_x - fin_x) == 2 && abs(begin_y - fin_y) == 1){
		return true;
	}
	else {
		return false;
	}
}

// returns the character for a Knight representing which player's turn it is.
char Knight::Type() const {
	return isWhite() ? 'N' : 'n';
}
