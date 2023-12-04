#ifndef ___BISHOP___
#define ___BISHOP___
#include <string>
#include "piece.h"

class Bishop: public Piece {
public:
	Bishop(int pos, bool isWhite);
	bool canMove(const std::string &start, const std::string &end, Piece ** b) const override;
	bool isEmpty() const override;
	char Type() const override;
};

#endif

