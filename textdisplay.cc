#include "textdisplay.h"
#include "observer.h"

TextDisplay::TextDisplay (GameManager &game, int row, int col, int sidenums):
    game{game}, row{row}, col{col}, sidenums{sidenums} {}


void TextDisplay::display () {
	out << ' ' << ' ';
	for (int i = 0; i < sidenums; i++) {
		out << bottomletters;
		bottomletters++;
	}
	bottomletters = 'a';
	out << std::endl;
	for (int i = 0; i < row; i++) {
		out << i + 1 << ' ';
		for (int j = 0; j < col; j++) {
			out << game.getTile(j, i);
		}
		out << std::endl;;
	}
}

