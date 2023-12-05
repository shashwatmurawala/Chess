#include <string>
#include "piece.h"
#include <sstream>


// Abstract Piece class

// 2 Parameter ctor
Piece::Piece(int row, int col, bool white): white{white}{
	pos.first = row;
	pos.second = col;
}

// returns is a Piece is white
bool Piece::isWhite() const{
	return white;
}

// mutator/setter: sets the pos field of a Piece object
void Piece::changePos(pair<int, int> posn){
	pos = posn;
}

// accessor/getter: gets the pos field of a Piece object
pair<int, int> Piece::posn() const {
	return pos;
}

// Dtor
Piece::~Piece(){}

void Piece::moved(){}

bool Piece::first() const {
	return false;
}

// returns is a Piece is on the right edge of the Board
bool Piece::onRightEdge() const {
	return (pos.second == 7) ? true : false;
}

// returns is a Piece is on the left edge of the Board
bool Piece::onLeftEdge() const {
	return (pos.second == 0) ? true : false;
}

// returns if a Piece is on the top edge of the Board
bool Piece::onTopEdge() const {
	return (pos.first == 0) ? true : false;
}

// returns if a Piece is on the bottom edge of the Board
bool Piece::onBottomEdge() const {
	return (pos.first == 7) ? true : false;
}

// converts the coordinate into a unique integer position
pair<int, int> getPos(const std::string &cmd) {
	int col = cmd[0] - 'a';
	int row = cmd[1] - '1';
	pair<int, int> coord;
	coord.first = 7 - row;
	coord.second = col; 
	return coord;
}

// converts the unique integer position to a string coordinate
std::string getCor(pair<int, int> index) {
	// inverse of getPos
	std::string s;
	std::ostringstream oss;
	char row = '0' + index.first; 
	char col = 'a' + index.second;
	oss << col;
	oss << row;
	s = oss.str();
	return s;
}

