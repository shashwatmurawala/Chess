#include <string>
#include "piece.h"
#include <sstream>

// Abstract Piece class

// 2 Parameter ctor
Piece::Piece(int pos, bool white): pos{pos}, white{white}{}

// returns is a Piece is white
bool Piece::isWhite() const{
	return white;
}

// mutator/setter: sets the pos field of a Piece object
void Piece::changePos(int posn){
	pos = posn;
}

// accessor/getter: gets the pos field of a Piece object
int Piece::posn() const {
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
	return (7 == (posn() % 8)) ? true : false;
}

// returns is a Piece is on the left edge of the Board
bool Piece::onLeftEdge() const {
	return (0 == (posn() % 8)) ? true : false;
}

// returns if a Piece is on the top edge of the Board
bool Piece::onTopEdge() const {
	return (0 <= posn() && posn() <= 7) ? true : false;
}

// returns if a Piece is on the bottom edge of the Board
bool Piece::onBottomEdge() const {
	return (56 <= posn() && posn() <= 63) ? true : false;
}

// converts the coordinate into a unique integer position
int getPos(const std::string &cmd) {
	int col = cmd[0] - 'a';
	int row = cmd[1] - '1';
	row = 7 - row;
	int pos = 8*row+col; 
	return pos;
}

// converts the unique integer position to a string coordinate
std::string getCor(int index) {
	// inverse of getPos
	std::string s;
	std::ostringstream oss;
	char row = '0' + (8 - (index / 8)); 
	char col = 'a' + (index % 8);
	oss << col;
	oss << row;
	s = oss.str();
	return s;
}

