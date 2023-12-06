#ifndef ___KING___
#define ___KING___

#include <string>
#include "piece.h"

class King: public Piece {
	bool firstMove;
public:
	King(int index, bool white);
	~King();
	bool validMove(const std::string &start, const std::string &end, Piece ** b) const override;
	bool isBlank() const override;
	char PT() const override;
	void moved() override;
	bool first() const override;
};

#endif
