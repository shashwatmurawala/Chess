#ifndef ___PLAYER___
#define ___PLAYER___

#include <string>


class Board;

class Player {
	bool isWhite;
public:
	Player(bool white);
	bool isPlayerWhite();
	virtual void generateMove(Board *b, std::string &first, std::string &last);
	virtual bool isComputer() const;
};

#endif
