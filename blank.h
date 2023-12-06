#ifndef ___BLANK___
#define ___BLANK___

#include <string>
#include "piece.h"

class Blank: public Piece {
public:
	Blank(int index);
	~Blank();
	bool validMove(const std::string &start, const std::string &end, Piece ** b) const override;
	bool isBlank() const override;
	char PT() const override;
};

#endif
