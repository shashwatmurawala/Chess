#ifndef ___KNIGHT___
#define ___KNIGHT___

#include <string>
#include "piece.h"

class Knight: public Piece {
public:
	Knight(int pos, bool isWhite);
	bool isEmpty() const override;
	bool validMove(const std::string &start, const std::string &end, Piece ** b) const override;
	char PT() const override;
};

#endif
