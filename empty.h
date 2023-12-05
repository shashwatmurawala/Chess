#ifndef ___EMPTY___
#define ___EMPTY___

#include <string>
#include "piece.h"

class Empty: public Piece {
public:
	Empty(int index);
	~Empty();
	bool validMove(const std::string &start, const std::string &end, Piece ** b) const override;
	bool isEmpty() const override;
	char PT() const override;
};

#endif
