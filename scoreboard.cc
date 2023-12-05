#include "scoreboard.h"
#include <string>
#include <iostream>
#include <sstream>

using namespace std; 

Scoreboard::Scoreboard() : whiteScore{0}, blackScore{0}{}

void Scoreboard::Score(){
	ostringstream oss;
	oss << "Scores:" << endl << "White: " << whiteScore << endl << "Black: " << blackScore << endl;
	cout << oss.str();
}

void Scoreboard::check(bool isWhiteInCheck){
	if (isWhiteInCheck) {
		cout << "Check on White" << endl;
	}
	else {
		cout << "Check on Black" << endl;
	} 
}

void Scoreboard::tie(){
	++whiteScore;
	++blackScore;
	cout << "Draw via Stalemate" <<endl;
}

void Scoreboard::win(bool isWhite){
	if (isWhite) {
		++whiteScore;
		cout << "White Wins via Checkmate" << endl;
	}
	else {
		++blackScore;
		cout << "Black Wins via Checkmate" << endl;
	}
}

void Scoreboard::resign(bool isWhite){
	if (!isWhite) {
		whiteScore += 1.0;
		cout << "The Winner is White" << endl;
	}
	else {
		blackScore += 1.0;
		cout << "The Winner is White" << endl;
	}
}