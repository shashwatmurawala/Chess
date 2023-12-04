#ifndef ___COMP___
#define ___COMP___

#include <string>

#include "player.h"
class Board;

class Comp: public Player {
	int level;
public:
	Comp(int level,bool white);
	int cpuLevel();
	void generateMove(Board *b, std::string &first, std::string &last) override;
	void genMove1(Board *b, std::string &first, std::string &last);
	bool isComputer() const override;
};

#endif

