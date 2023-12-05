#include "board.h"
#include "bishop.h"
#include <string>
// static helpers 
static bool onRight(int i){
	return (7 == (i % 8)) ? true : false;
}

static bool onLeft(int i){
	return (0 == (i % 8)) ? true : false;
}

// 2 Parameter ctor
Bishop::Bishop(int pos, bool isWhite) : Piece(pos, isWhite) {}

// returns if the Piece is empty or not
bool Bishop::isEmpty() const{
	return false;
}

// determines whether a Bishop can move to the end coordinates
bool Bishop::canMove(const std::string &start,const std::string &end, Piece ** b) const {
	if((start[0] < 'a')||(start[0] > 'h')||(start[1] < '1')||(start[1] > '8')) return false;
	if((end[0] < 'a')||(end[0] > 'h')||(end[1] < '1')||(end[1] > '8')) return false;
	int begin = getPos(start);
	int fin = getPos(end);



	// moving down on the right diagonal
	if (!(begin==0) && !(begin == 63) && (begin % 7 == fin % 7) && begin < fin) {
		while (true) {
			begin += 7;
			if (begin == fin && (b[begin]->isEmpty() || (isWhite() != b[begin]->isWhite()))) {
				return true;
			}
			else if (begin == fin && b[begin]->isEmpty()) {
				return true;
			}
			else if (!b[begin]->isEmpty()) {
				return false;
			}
		}
	}

	// moving up on the right diagonal
	else if (!(begin==0) && !(begin == 63) && (begin % 7 == fin % 7) && begin > fin) {
		while (true) {
			begin -= 7;
			if (begin == fin && (b[begin]->isEmpty() || (isWhite() != b[begin]->isWhite()))) {
				return true;
			}
			else if (begin == fin && b[begin]->isEmpty()) {
				return true;
			}
			else if(!b[begin]->isEmpty()) {
				return false;
			}
		} 
	}

	// moving down on the left diagonal
	else if (begin % 9 == fin % 9 && begin < fin) {
		if(onLeft(begin)){
				return false;
		}
		while (true) {
			begin += 9;
			if (begin == fin && (b[begin]->isEmpty() || (isWhite() != b[begin]->isWhite()))) {
				return true;
			}
			else if (begin == fin && b[begin]->isEmpty()) {
				return true;
			}
			else if (!b[begin]->isEmpty()) {
				return false;
			}
			else if(onRight(begin)){
				return false;
			}
		} 
	}

	// moving up on the left diagonal
	else if (begin % 9 == fin % 9 && begin > fin) {
		if (onRight(begin)){
				return false;
		}
		while (true) {
			begin -= 9;
			if (begin == fin && (b[begin]->isEmpty() || (isWhite() != b[begin]->isWhite()))) {
				return true;
			}
			else if (begin == fin && b[begin]->isEmpty()) {
				return true;
			}
			else if (!b[begin]->isEmpty()) {
				return false;
			}
			else if(onLeft(begin)){
				return false;
			}
		} 
	}
	else {
		return false;
	}
}

// returns uppercase or lowercase b, depending on which Player's turn it is
char Bishop::Type() const {
	return isWhite() ? 'B' : 'b';
}

