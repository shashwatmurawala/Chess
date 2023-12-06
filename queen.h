#ifndef ___QUEEN___
#define ___QUEEN___

#include <string>
#include "piece.h"

class Rook;

class Queen: public Piece {
public:
	Queen(int pos, bool isWhite);
	bool validMove(const std::string &start, const std::string &end, Piece ** b) const override;
	char PT() const override;
	bool isBlank() const override;
};

#endif
