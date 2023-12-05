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

int GraphicsDisplay::piececol(char piece){
	return (piece >= 'a' && piece <= 'z')? Xwindow::Black : Xwindow::White;
}

int GraphicsDisplay::rectcol(int col, int row){
	if ((col + row) % 2 == 0){
		return c2;
	}
	else{
		return c1;
	}
}

void GraphicsDisplay::set(char piece, const string &original){
	int col = original[0] - 'a' +1;
	int row = reverse(original[1] - '1');     
	int rectFillColour = rectcol(col,row);
	string s(1, piece);
	int pieceColour = piececol(piece);	
	w->fillRectangle(col * 64, row * 64, 64, 64, rectFillColour);
	w->drawString(col * 64 + 16, row * 64 + 32, s);
}

int GraphicsDisplay::reverse(int row){
	return (8 - row);
}

void GraphicsDisplay::update(char piece,const string &original, const string &newpos){
	//gets originaling coordinates for cells. string information for piece, and the Colour of the piece on the board.
	int roworiginal = reverse(original[1] - '1');
	int coloriginal = original[0] - 'a' + 1;
	int rownewpos = reverse(newpos[1] - '1');
	int colnewpos = newpos[0] - 'a' + 1;
	string s(1, piece);
	int pieceColour = piececol(piece);
	int rectFillColouroriginal = rectcol(coloriginal,roworiginal);
	int rectFillColournewpos = rectcol(colnewpos,rownewpos);
	//first fill rectangle of original position
	w->fillRectangle(coloriginal * 64, roworiginal * 64, 64, 64, rectFillColouroriginal);
	// void fillRectangle(int x, int y, int width, int height, int colour=Black);
	//Then fills rectangle of newpos position(this takes out any existing piece string on the space)
	w->fillRectangle(colnewpos * 64, rownewpos * 64, 64, 64, rectFillColournewpos);


	//Then Writes in the string name of the piece. 
	//        void drawString(int x, int y, std::string msg, int colour = Black);

	w->drawString(colnewpos * 64 + 16, (rownewpos)*64 + 32 , s);
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

