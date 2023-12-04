#include <string>
#include "piece.h"
#include "queen.h"
#include <iostream>

//static helper functions
static bool onRight(int i){
	return (7 == (i % 8)) ? true : false;
}

static bool onLeft(int i){
	return (0 == (i % 8)) ? true : false;
}

// 2 Parameter ctor
Queen::Queen(int pos, bool isWhite): Piece(pos,isWhite){}

// determines whether a Queen can move to the desired end coordinates
bool Queen::canMove(const std::string &start, const std::string &end, Piece ** b) const{
	int begin = getPos(start);
	int fin = getPos(end);

	// Queen is moving upwards
	if ((begin % 8 == fin % 8) && begin > fin) {
		begin -= 8;
		while (begin != fin) {
			if (!b[begin]->isEmpty()) {
				return false;
			}
			begin -=8;
		}
		if (b[begin]->isEmpty()) {
			return true;
		}
		else if (b[begin]->isWhite() == isWhite()) {
			return false;
		}
		else {
			return true;
		}
	}

	// Queen is moving downwards
	else if ((begin % 8 == fin % 8) && begin < fin) {
		begin += 8;
		while (begin != fin) {
			if (!b[begin]->isEmpty()) {
				return false;
			}
			begin +=8;
		}
		if (b[begin]->isEmpty()) {
			return true;
		}
		else if (b[begin]->isWhite() == isWhite()) {
			return false;
		}
		else {
			return true;
		}
	}

	// Queen is moving leftwards
	else if ((begin / 8) == (fin / 8) && (begin > fin)) {
		begin--;
		while (begin != fin) {
			if (!b[begin]->isEmpty()) {
				return false;
			}
			begin--;
		}
		if (b[begin]->isEmpty()) {
			return true;
		}
		else if (b[begin]->isWhite() == isWhite()) {
			return false;
		}
		else {
			return true;
		}
	}

	// Queen is moving rightwards
	else if ((begin / 8) == (fin / 8) && (begin < fin)) {
		begin++;
		while (begin != fin) {
			if (!b[begin]->isEmpty()) {
				return false;
			}
			begin++;
		}
		if (b[begin]->isEmpty()) {
			return true;
		}
		else if (b[begin]->isWhite() == isWhite()) {
			return false;
		}
		else {
			return true;
		}
	}

	// Queen is moving diagonally downwards
	else if (begin % 9 == fin % 9 && begin < fin) {
		if(onLeft(begin)){
				return false;
		}
		while (true) {
			begin += 9;
			if(begin > 63){
				return false;
			}
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

	// Queen is moving diagonally upwards
	else if (begin % 9 == fin % 9 && begin > fin) {
		if (onRight(begin)){
				return false;
		}
		while (true) {
			begin -= 9;
			if(begin < 0){
				return false;
			}
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

	// corners
	else if (!(begin==0) && !(begin == 63) && (begin % 7 == fin % 7) && begin < fin) {
		while (true) {
			begin += 7;
			if(begin > 63){
				return false;
			}
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

	// corners
	else if (!(begin==0) && !(begin == 63) && (begin % 7 == fin % 7) && begin > fin) {
		while (true) {
			begin -= 7;
			if(begin < 0){
				return false;
			}
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
	else {
		return false;
	}
}

// returns a char representing the Queen for whichever player's turn it is
char Queen::Type() const {
	return isWhite() ? 'Q' : 'q';
}

// returns if the Queen object is empty
bool Queen::isEmpty() const {
	return false;
}
