#include "window.h"
#include <string>
#ifndef _GRP_H
#define _GRP_H
class GraphicsDisplay{
	Xwindow* w = nullptr;
	int blackScore = 0;
	int whiteScore = 0;
	int c1 = Xwindow::White;
	int c2 = Xwindow::Green;
	int reverse(int row);
	
	public:
		GraphicsDisplay();
		~GraphicsDisplay();
		int rectcol(int col, int row);
		int piececol(char piece);
		void set(char piece, const std::string &original);
		void update(char piece,const std::string &original,const std::string &newpos);
		void blankBoard();
		void defaultDisplay();
		void updateScore(bool whitewin, bool stalemate);
		void updateTurn(bool white);
};
#endif
