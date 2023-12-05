#include "board.h"
#include "bishop.h"
#include <string>

static bool onRight(int i){
	return (7 == i) ? true : false;
}

static bool onLeft(int i){
	return (0 == i) ? true : false;
}

// 2 Parameter ctor
Bishop::Bishop(int pos, bool isWhite) : Piece(pos, isWhite) {}

bool Bishop::isEmpty() const{
	return false;
}

// determines whether a Bishop can move to the end coordinates
bool Bishop::canMove(const std::string &start,const std::string &end, Piece ** b) const {
	int begin = getPos(start);
	int fin = getPos(end);
>>>>>>> parent of b87059c (valid move input checked)

	// moving down on the right diagonal
	if (!(begin==0) && !(begin == 63) && (begin % 7 == fin % 7) && begin < fin) {
		while (true) {
			++begin.first;
			++begin.second;
			if (begin == fin && ((b[begin.first][begin.second].isEmpty()) || (isWhite() != b[begin.first][begin.second].isWhite()))) {
				return true;
			}
			else if (begin == fin && b[begin.first][begin.second].isEmpty()) {
				return true;
			}
			else if (!b[begin.first][begin.second].isEmpty()) {
				return false;
			}
		}
	}

	// moving up on the right diagonal
	else if (!(begin==0) && !(begin == 63) && (begin % 7 == fin % 7) && begin > fin) {
		while (true) {
			--begin.first;
			++begin.second;
			if (begin == fin && (b[begin.first][begin.second].isEmpty() || (isWhite() != b[begin.first][begin.second].isWhite()))) {
				return true;
			}
			else if (begin == fin && b[begin.first][begin.second].isEmpty()) {
				return true;
			}
			else if(!b[begin.first][begin.second].isEmpty()) {
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
			++begin.first;
			--begin.second;
			if (begin == fin && (b[begin.first][begin.second].isEmpty() || (isWhite() != b[begin.first][begin.second].isWhite()))) {
				return true;
			}
			else if (begin == fin && b[begin.first][begin.second].isEmpty()) {
				return true;
			}
			else if (!b[begin.first][begin.second].isEmpty()) {
				return false;
			}
			else if(onRight(begin.second)){
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
			--begin.first;
			--begin.second;
			if (begin == fin && (b[begin.first][begin.second].isEmpty() || (isWhite() != b[begin.first][begin.second].isWhite()))) {
				return true;
			}
			else if (begin == fin && b[begin.first][begin.second].isEmpty()) {
				return true;
			}
			else if (!b[begin.first][begin.second].isEmpty()) {
				return false;
			}
			else if(onLeft(begin.second)){
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

