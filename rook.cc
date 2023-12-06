#include <string>
#include "piece.h"
#include "rook.h"

Rook::Rook(int pos, bool isWhite) : Piece{pos, isWhite}, firstMove{true} {}

bool Rook::validMove(const std::string &start, const std::string &end, Piece ** b) const {
	if((start[0] < 'a')||(start[0] > 'h')||(start[1] < '1')||(start[1] > '8')) return false;
	if((end[0] < 'a')||(end[0] > 'h')||(end[1] < '1')||(end[1] > '8')) return false;
	int org = arrayloc(start);
	int newloc = arrayloc(end);

	if ((org % 8 == newloc % 8) && org > newloc) {
		org -= 8;
		while (org != newloc) {
			if (!b[org]->isBlank()) {
				return false;
			}
			org -=8;
		}
		if ((b[org]->isBlank()) || 
			(!(!b[org]->isBlank() && b[org]->isWhite() == isWhite()))){
			return true;
		}else {
			return false;
		}
	}else if ((org % 8 == newloc % 8) && org < newloc) {
		org += 8;
		while (org != newloc) {
			if (!b[org]->isBlank()) {
				return false;
			}
			org +=8;
		}
		if ((b[org]->isBlank()) ||
			(!(!b[org]->isBlank() && b[org]->isWhite() == isWhite()))) {
			return true;
		}else{
			return false;
		}
	}else if ((org / 8) == (newloc / 8) && (org > newloc)) {
		org--;
		while (org != newloc) {
			if (!b[org]->isBlank()) {
				return false;
			}
			org--;
		}
		if ((b[org]->isBlank()) ||
			(!(!b[org]->isBlank() && b[org]->isWhite() == isWhite()))) {
			return true;
		}
		else{
			return false;
		}
	}else if ((org / 8) == (newloc / 8) && (org < newloc)) {
		org++;
		while (org != newloc) {
			if (!b[org]->isBlank()) {
				return false;
			}
			org++;
		}
		if ((b[org]->isBlank()) ||
			(!(!b[org]->isBlank() && b[org]->isWhite() == isWhite()))) {
			return true;
		}else{
			return false;
		}	
	}
	else {
		return false;
	}
}

char Rook::PT() const {
	return isWhite() ? 'R' : 'r';
}

bool Rook::isBlank() const {
	return false;
}

void Rook::moved() {
	firstMove = false;
}

bool Rook::first() const {
	return firstMove;
}
