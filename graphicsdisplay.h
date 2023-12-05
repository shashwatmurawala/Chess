#include "window.h"
#include <string>
#ifndef _GRP_H
#define _GRP_H
class GraphicsDisplay{
	int windowsize = 625;
	Xwindow* xw = nullptr;
	int colourPositive = Xwindow::White;
	int colourNegative = Xwindow::Green;
	int flipRow(int row);
	int blackScore = 0;
	int whiteScore = 0;
	
	public:
	//ctor
	GraphicsDisplay();
	//dtor
	~GraphicsDisplay();
	//constants
	const int gridsize = 10;
	const int cellsize = windowsize/gridsize; //62.5 pixels for each cell.
	const int yPadding = cellsize/2;
	const int xPadding = cellsize/4;
	//methods
	int findRectangleColour(int col, int row);
	int findPieceColour(char piece);
	void setPiece(char piece, const std::string &start);
	void updateMove(char piece,const std::string &start,const std::string &end);
	void clearBoard();
	void defaultDisplay();
	void updateScore(bool winnerIsWhite, bool isStalemate);
	void updateTurn(bool white);
	void clearTop(bool forTurn);
};
#endif
