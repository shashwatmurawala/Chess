#include "board.h"
#include "bishop.h"
#include <string>

static bool onRight(int i){
	return (7 == (i % 8)) ? true : false;
}

static bool onLeft(int i){
	return (0 == (i % 8)) ? true : false;
}

Bishop::Bishop(int pos, bool isWhite) : Piece(pos, isWhite) {}

bool Bishop::isEmpty() const{
	return false;
}

bool Bishop::validMove(const std::string &start,const std::string &end, Piece ** b) const {
	int begin = getPos(start);
	int fin = getPos(end);

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

char Bishop::Type() const {
	return isWhite() ? 'B' : 'b';
}

