#include <string>
#include "piece.h"
#include <sstream>

int arrayloc(const std::string &cmd) {
	int col = cmd[0] - 'a';
	int row = cmd[1] - '1';
	int pos = 8 * (7 - row) + col; 
	return pos;
}

std::string BoardCoord(int index) {
	std::string s;
	std::ostringstream oss;
	char row = '0' + (8 - (index / 8)); 
	char col = 'a' + (index % 8);
	oss << col;
	oss << row;
	s = oss.str();
	return s;
}

Piece::Piece(int pos, bool white): pos{pos}, white{white}{}

bool Piece::isWhite() const{
	return white;
}

void Piece::changePos(int posn){
	pos = posn;
}

int Piece::squarelocation() const {
	return pos;
}

Piece::~Piece(){}

void Piece::moved(){}

bool Piece::first() const {
	return false;
}

bool Piece::ColH() const {
	return (7 == (squarelocation() % 8)) ? true : false;
}

bool Piece::ColA() const {
	return (0 == (squarelocation() % 8)) ? true : false;
}

bool Piece::Row8() const {
	return (0 <= squarelocation() && squarelocation() <= 7) ? true : false;
}

bool Piece::Row1() const {
	return (56 <= squarelocation() && squarelocation() <= 63) ? true : false;
}