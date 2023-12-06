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

bool Bishop::isBlank() const{
	return false;
}

bool Bishop::validMove(const std::string &start,const std::string &end, Piece ** b) const {
	int org = arrayloc(start);
	int newloc = arrayloc(end);

	if (!(org==0) && !(org == 63) && (org % 7 == newloc % 7) && org < newloc) {
		while (true) {
			org += 7;
			if (org == newloc && (b[org]->isBlank() || (isWhite() != b[org]->isWhite()))) {
				return true;
			}
			else if (org == newloc && b[org]->isBlank()) {
				return true;
			}
			else if (!b[org]->isBlank()) {
				return false;
			}
		}
	}

	else if (!(org==0) && !(org == 63) && (org % 7 == newloc % 7) && org > newloc) {
		while (true) {
			org -= 7;
			if (org == newloc && (b[org]->isBlank() || (isWhite() != b[org]->isWhite()))) {
				return true;
			}
			else if (org == newloc && b[org]->isBlank()) {
				return true;
			}
			else if(!b[org]->isBlank()) {
				return false;
			}
		} 
	}

	else if (org % 9 == newloc % 9 && org < newloc) {
		if(onLeft(org)){
				return false;
		}
		while (true) {
			org += 9;
			if (org == newloc && (b[org]->isBlank() || (isWhite() != b[org]->isWhite()))) {
				return true;
			}
			else if (org == newloc && b[org]->isBlank()) {
				return true;
			}
			else if (!b[org]->isBlank()) {
				return false;
			}
			else if(onRight(org)){
				return false;
			}
		} 
	}

	else if (org % 9 == newloc % 9 && org > newloc) {
		if (onRight(org)){
				return false;
		}
		while (true) {
			org -= 9;
			if (org == newloc && (b[org]->isBlank() || (isWhite() != b[org]->isWhite()))) {
				return true;
			}
			else if (org == newloc && b[org]->isBlank()) {
				return true;
			}
			else if (!b[org]->isBlank()) {
				return false;
			}
			else if(onLeft(org)){
				return false;
			}
		} 
	}
	else {
		return false;
	}
}

char Bishop::PT() const {
	return isWhite() ? 'B' : 'b';
}
