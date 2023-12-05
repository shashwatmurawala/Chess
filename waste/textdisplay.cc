#include "textdisplay.h"
#include <sstream>
using namespace std;

TextDisplay::TextDisplay(){
	cout << "CS246 Chess!" << endl;
	this->showCommands();
	blankBoard();

}

void TextDisplay::showCommands() const {
	
	cout << "---- Commands ----                                             ---- Description ----" << endl;
	cout << "During/For a Game:" << endl;
	cout << "	game *whitePlayer* *blackPlayer* 			---- To begin a game" << endl;
	cout << "	move *move_from* [*move_to] [*Piece_for_promotion*]	---- To play a move" << endl;
	cout << "	resign							---- To resign" << endl;
	cout << "During/For Setup Mode:" << endl;
	cout << "	setup							---- Enters setup mode" << endl;
	cout << "	+ *Piece* *Square* 					---- Places Piece on Square" << endl;
	cout << "	- *Square*						---- Removes the piece on Square" << endl;
	cout << "	= *Colour*						---- Makes it Colour's turn next" << endl;
	cout << "	done							---- Leaves setup mode" << endl;

}

void TextDisplay::blankBoard(){
	for (int i = 0; i < 8; ++i) {
		vector<char> row;
		for (int j = 0; j < 8; ++j) {
			char square = ((i + j) % 2 == 0 ? '_' : ' ');
			row.emplace_back(square);
		}
		display.emplace_back(row);
	}

	cout << *this << endl;
}

void TextDisplay::defaultDisplay(){
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

void TextDisplay::set(char piece, const string &original){
	int col = original[0] - 'a' +1;
	int row = reverse(original[1] - '1');     
	int rectFillColour = (((col + row) % 2 == 0) ? c2 : c1);
	string s(1, piece);
	w->fillRectangle(col * 64, row * 64, 64, 64, rectFillColour);
	w->drawString(col * 64 + 16, row * 64 + 32, s);
}

int TextDisplay::reverse(int row){
	return (8 - row);
}

void TextDisplay::update(char piece,const string &original, const string &newpos){
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

void TextDisplay::Score(bool whitewin, bool stalemate){
	if(stalemate){
		whiteScore += 1;
		blackScore += 1;
	}else if(whitewin){
		whiteScore += 1;
	}
	else{
		blackScore += 1;
	}
	stringstream ss1;
	stringstream ss2;
	ss1 << blackScore;
	ss2 << whiteScore;
	string score = "Black: " + ss1.str() + "  White: " + ss2.str();
	cout << score << endl;
}

void TextDisplay::Turn(bool white){
	string s = (white)? "White's Move" : "Black's Move";
	cout << s << endl;
}

ostream& operator<<(ostream& out, TextDisplay& td) {		
	for (int i = 0; i < td.display.size(); ++i) {
		for (int j = 0; j < td.display[i].size(); ++j) {
			cout << td.display[i][j];
		}
		cout << endl;
	}
	return out;
}

