#include "board.h"
#include "bishop.h"
#include <string>
// static helpers 
static bool onRight(int i){
	return (7 == i) ? true : false;
}

static bool onLeft(int i){
	return (0 == i) ? true : false;
}

// 2 Parameter ctor
Bishop::Bishop(int row, int col, bool isWhite) : Piece(row, col, isWhite) {}

// returns if the Piece is empty or not
bool Bishop::isEmpty() const{
	return false;
}

// determines whether a Bishop can move to the end coordinates
bool Bishop::canMove(const std::string &start,const std::string &end, Piece ** b) const {
<<<<<<< HEAD
	if((start[0] < 'a')||(start[0] > 'h')||(start[1] < '1')||(start[1] > '8')) return false;
	if((end[0] < 'a')||(end[0] > 'h')||(end[1] < '1')||(end[1] > '8')) return false;
	pair<int, int> begin = getPos(start);
	pair<int, int> fin = getPos(end);

	pair<int, int> coord1;
	pair<int, int> coord2;
	coord1.first = 7;
	coord1.second = 0;
	coord2.first = 0;
	coord2.second = 7;
=======
	int begin = getPos(start);
	int fin = getPos(end);
>>>>>>> parent of b87059c (valid move input checked)

	// moving down on the right diagonal
	if (!(begin==coord1) && !(begin == coord2) && 
		(begin.first - fin.first == begin.second - fin.second) && 
		begin.first < fin.first &&
		begin.second < fin.second) {
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
	else if (!(begin==coord1) && !(begin == coord2) && 
		(begin.first - fin.first == fin.second - begin.second) && 
		begin.first > fin.first &&
		begin.second < fin.second) {
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
	else if ((fin.first - begin.first == begin.second - fin.second) && 
		begin.first < fin.first &&
		begin.second > fin.second) {
		if(onLeft(begin.second)){
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
	else if ((fin.first - begin.first == fin.second - begin.second) && 
		begin.first > fin.first &&
		begin.second > fin.second) {
		if (onRight(begin.second)){
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

// returns uppercase or lowercase b, depending on which Player's turn it is
char Bishop::Type() const {
	return isWhite() ? 'B' : 'b';
}

