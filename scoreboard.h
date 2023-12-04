#ifndef ___SCORE___
#define ___SCORE___

#include <string>

class Scoreboard{
	float whiteScore;
	float blackScore;
public:
	Scoreboard();
	void check(bool IsWhiteInCheck); // sends 
	void tie(); 
	void win(bool isWhite);
	void resign(bool isWhite);
	void printScore();
};

#endif
