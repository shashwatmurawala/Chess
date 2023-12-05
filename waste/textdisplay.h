#include <iostream>
#include <string>
#include <vector>
#ifndef _GRP_H
#define _GRP_H

using namespace std;

class Board;

class TextDisplay{
	std::vector<std::vector<char>> display;
	int blackScore = 0;
	int whiteScore = 0;
	int reverse(int row);
	
	public:
		TextDisplay();
		void showCommands() const;
		void set(char piece, const std::string &original);
		void update(char piece,const std::string &original,const std::string &newpos);
		void blankBoard();
		void defaultDisplay();
		void Score(bool whitewin, bool stalemate);
		void Turn(bool white);

	friend ostream& operator<<(ostream& out, TextDisplay& td);
};
#endif
