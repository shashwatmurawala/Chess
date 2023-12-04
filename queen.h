#ifndef ___QUEEN___
#define ___QUEEN___

#include <string>
#include "piece.h"

class Queen: public Piece {
public:
	Queen(int pos, bool isWhite);
	bool canMove(const std::string &start, const std::string &end, Piece ** b) const override;
	char Type() const override;
	bool isEmpty() const override;
};

#endif
