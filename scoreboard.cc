#include "scoreboard.h"
#include <string>
#include <iostream>
#include <sstream>

using namespace std; 

// Default ctor
Scoreboard::Scoreboard() : whiteScore{0}, blackScore{0}{}

// prints the final scores for a game of Chess
void Scoreboard::printScore(){
	ostringstream oss;
	oss << "Final score:" << endl;
	oss << "White: " << whiteScore << endl;
	oss << "Black: " << blackScore << endl;
	cout << oss.str();
}

// prints if a player is in check
void Scoreboard::check(bool isWhiteInCheck){
	string s;
	if (isWhiteInCheck) {
		s = "White";
	}
	else {
		s = "Black";
	}
	cout << s << " is in check." << endl;
}

// updates scoreboard in the event of a tie
void Scoreboard::tie(){
	whiteScore += 0.5;
	blackScore += 0.5;
	cout << "Stalemate!" <<endl;
}

// updates scoreboard in the event of a win and prints the winner
void Scoreboard::win(bool isWhite){
	if (isWhite) {
		whiteScore += 1.0;
		cout << "Checkmate! White wins!" << endl;
	}
	else {
		blackScore += 1.0;
		cout << "Checkmate! Black wins!" << endl;
	}
}

// updates scoreboard in the event of resignation and prints who wins.
void Scoreboard::resign(bool isWhite){
	if (!isWhite) {
		whiteScore += 1.0;
		cout << "White wins!" << endl;
	}
	else {
		blackScore += 1.0;
		cout << "Black wins!" << endl;
	}
}
