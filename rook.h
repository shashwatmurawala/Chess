#ifndef ___ROOK___
#define ___ROOK___

#include <string>
#include "piece.h"

class Rook: public Piece {
	bool firstMove;
public:
	Rook(int pos, bool isWhite);
	char Type() const override;
	bool isEmpty() const override;
	void moved() override;
	bool first() const override;
	bool canMove(const std::string &start, const std::string &end, Piece ** b) const override;
};

#endif
