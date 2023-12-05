#include "graphicsdisplay.h"
#include <sstream>
#include <iomanip>
using namespace std;

GraphicsDisplay::GraphicsDisplay(){
	w= new Xwindow(640,640);
	blankBoard();
}

GraphicsDisplay::~GraphicsDisplay(){
	delete w;
}

void GraphicsDisplay::blankBoard(){
	for (int i = 1; i <= 8; ++i){
		for (int j = 1; j <= 8; ++j){
			if((i % 2 == 0 && j % 2 ==  0) || (i % 2 == 1 && j % 2 == 1)){
				w->fillRectangle(i * 64, j * 64, 64, 64, c2);
			}
			else{
				w->fillRectangle(i * 64, j * 64, 64, 64, c1);
			}
		}
		string s = to_string(reverse(i - 1));
		w->drawString(16, i * 64 + 32 + 16, s);
		s = 'a' + i - 1;
		w->drawString(i * 64 + 16, 9 * 64 + 32 + 16, s);
	}
	stringstream ss1;
	stringstream ss2;
	ss1 << blackScore;
	ss2 << whiteScore;
	string score = "Black: " + ss1.str() + "  White: " + ss2.str();
	w->drawString(10, 40, score);
	updateTurn(true);
}

void GraphicsDisplay::defaultDisplay(){
	for(int i = 1; i <= 8; ++i){
		if(i == 1 || i == 8){
			w->drawString(i * 64 + 16, 64 + 32, "r");
			w->drawString(i * 64 + 16, 64 * 8 + 32, "R");
		}
		else if(i == 2|| i == 7){
			w->drawString(i * 64 + 16, 64 + 32, "n");
			w->drawString(i * 64 + 16, 64 * 8 + 32, "N");
		}
		else if(i == 3 || i == 6){
			w->drawString(i * 64 + 16, 64 + 32, "b");
			w->drawString(i * 64 + 16, 64 * 8 + 32, "B");
		}
		else if(i == 4){
			w->drawString(i * 64 + 16, 64 + 32, "q");
			w->drawString(i * 64 + 16, 64 * 8 + 32, "Q");
		}
		else{
			w->drawString(i * 64 + 16, 64 + 32, "k");
			w->drawString(i * 64 + 16, 64 * 8 + 32, "K");
		}
		w->drawString(i * 64 + 16, 2 * 64 + 32, "p");
		w->drawString(i * 64 + 16, 7 * 64 + 32, "P");
	}
}

void GraphicsDisplay::set(char piece, const string &original){
	int col = original[0] - 'a' +1;
	int row = reverse(original[1] - '1');     
	int rectFillColour = (((col + row) % 2 == 0) ? c2 : c1);
	string s(1, piece);
	w->fillRectangle(col * 64, row * 64, 64, 64, rectFillColour);
	w->drawString(col * 64 + 16, row * 64 + 32, s);
}

int GraphicsDisplay::reverse(int row){
	return (8 - row);
}

void GraphicsDisplay::update(char piece,const string &original, const string &newpos){
	int ogrow = reverse(original[1] - '1');
	int ogcol = original[0] - 'a' + 1;
	int newrow = reverse(newpos[1] - '1');
	int newcol = newpos[0] - 'a' + 1;
	string s(1, piece);
	int rectFillColouroriginal = (((ogcol + ogrow) % 2 == 0) ? c2 : c1);
	int rectFillColournewpos = (((newcol + newrow) % 2 == 0) ? c2 : c1);
	w->fillRectangle(ogcol * 64, ogrow * 64, 64, 64, rectFillColouroriginal);
	w->fillRectangle(newcol * 64, newrow * 64, 64, 64, rectFillColournewpos);
	w->drawString(newcol * 64 + 16, (newrow)*64 + 32 , s);
}

void GraphicsDisplay::updateScore(bool whitewin, bool stalemate){
	if(stalemate){
		whiteScore += 1;
		blackScore += 1;
	}else if(whitewin){
		whiteScore += 1;
	}
	else{
		blackScore += 1;
	}
	w->fillRectangle(0, 0, 300, 50, Xwindow::White);
	stringstream ss1;
	stringstream ss2;
	ss1 << blackScore;
	ss2 << whiteScore;
	string score = "Black: " + ss1.str() + "  White: " + ss2.str();
	w->drawString(10, 40, score);
}

void GraphicsDisplay::updateTurn(bool white){
	string s = (white)? "White's Move" : "Black's Move";
	w->fillRectangle(365 , 0, 265 , 50, Xwindow::White);
	w->drawString(380, 40, s);
}

