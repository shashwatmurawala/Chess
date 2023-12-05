#ifndef ___SCORE___
#define ___SCORE___

#include <string>
#include "board.h"

class Scoreboard{
	int whiteScore;
	int blackScore;
public:
	Scoreboard();
	void check(bool IsWhiteInCheck);
	void tie(); 
	void win(bool isWhite);
	void resign(bool isWhite);
	void Score();
};

#endif
