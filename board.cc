#include <iostream>
#include <sstream>
#include "board.h"
#include "player.h"
#include "computer.h"
#include "scoreboard.h"
#include "piece.h"
#include "empty.h"
#include "pawn.h"
#include "knight.h"
#include "bishop.h"
#include "rook.h"
#include "queen.h"
#include "king.h"
#include "graphicsdisplay.h"
#include <string>

using namespace std;

// 2 Parameter ctor
Board::Board(int player1, int player2): isTurnWhite{true},
		inCheck{false}, gameOver{true}, s{new Scoreboard()}, p1{new Player(true)}, p2{new Player(false)}{
			clearBoard();
			if (player1 > 0) {
				delete p1;
				p1 = new Comp(player1, true);
			}
			if (player2 > 0) {
				delete p2;
				p1 = new Comp(player2, false);
			}
		}

// clears the Board and makes all spaces the Empty piece.
void Board::clearBoard(){
	for (int i = 0; i < 8; ++i) {
		vector<Piece> row;
		for (int j = 0; j < 8; ++j){
			Empty cur{i};
			row.emplace_back(cur);
		}
		board.emplace_back(row);
	}
}

// sets up the Board to the default configuration of Chess
void Board::normalSetup(){
	setTurn("white");
	gameOn();
	gd->blankBoard();
	// setting up a new black team
	board[7][0] = Rook(0, false);
	board[7][1] = Knight(1,false);
	board[7][2] = Bishop(2,false);
	board[7][3] = Queen(3,false);
	board[7][4] = King(4,false);
	board[7][5] = Bishop(5,false);
	board[7][6] = Knight(6,false);
	board[7][7] = Rook(7, false);
	for (int i = 0; i < 8; ++i) {
		board[6][i] = Pawn(i,false); // row of pawns
	}
	for (int j = 2; j < 6; ++j) {
		for (int i = 0; i < 8; ++i) {
			board[j][i] = Empty(j); // row of pawns
		}
	}
	// setting up a new white team
	for (int i = 0; i < 8; ++i) {
		board[1][i] = Pawn(i,true); // row of pawns
	}
	board[0][0] = Rook(56,true); // back row
	board[0][1] = Knight(57,true);
	board[0][2] = Bishop(58,true);
	board[0][3] = Queen(59,true);
	board[0][4] = King(60,true);
	board[0][5] = Bishop(61,true);
	board[0][6] = Knight(62,true);
	board[0][7] = Rook(63,true);
	gd->defaultDisplay();
}


// adds Player objects (human or computer) to the Board
void Board::newPlayers(int player1, int player2){
	delete p1;
	delete p2;
	if (player1 == 0) {
		p1 = new Player(true);
	}
	else if (player1 > 0) {
		p1 = new Comp(player1, true);
	}
	if (player2 == 0) {
		p2 = new Player(false);
	}
	else if (player2 > 0) {
		p2 = new Comp(player2, false);
	}
}

// places a Piece on the Board
void Board::place(char piece, const string &cmd) { 
	// calling this function with piece == 'E' or 'e' will leave that space empty
	char p = piece;
	pair<int, int> index = getPos(cmd);
	bool isWhite = ('A' < piece) && ('Z' > piece);
	if (!isWhite){
		piece = piece - 'a' + 'A';
	}

	// cases for letters representing the different Pieces
	if (piece == 'P') {
		board[index.first][index.second] = Pawn(index.first, index.second, isWhite);
	}
	else if (piece == 'R') {
		board[index.first][index.second] = Rook(index.first, index.second, isWhite);
	}
	else if (piece == 'Q') {
		board[index.first][index.second] = Queen(index.first, index.second, isWhite);
	}
	else if (piece == 'B') {
		board[index.first][index.second] = Bishop(index.first, index.second, isWhite);
	}
	else if (piece == 'N') {
		board[index.first][index.second] = Knight(index.first, index.second, isWhite);
	}
	else if (piece == 'K') {
		board[index.first][index.second] = King(index.first, index.second, isWhite);
	}
	else if (piece == 'E') {
		board[index.first][index.second] = Empty(index.first, index.second);
	}
	gd->set(p,cmd);
}


// Dtor, destroys the Board, Scoreboard, Players, and GraphicsDisplay
Board::~Board() {
	for(int i =0; i < 64;++i){ // deletes all piece pointers in the Board object
		delete board[i];
	}
	delete [] board;
	delete s;
	delete p1;
	delete p2;
	delete gd;
}


// tests out the move, mutates the board and assesses if the player is left in 
// check. If the move is valid, the function returns true, else it returns
// false. In either case, the board is mutated back to its original state
bool Board::testMove(const string &start, const string &end) {	
	Piece *p = getPiece(start);
	Piece *temp = getPiece(end);
	if(p->isWhite() != getTurnStatus()){
		return false;
	}

	// temporarily move
	if (p->canMove(start, end, getBoard())) {
		board[getPos(end)] = p;
		board[getPos(start)] = new Empty(getPos(start));
		if (isCheck(isTurnWhite)) {
			delete board[getPos(start)];
			board[getPos(start)] = p;
			board[getPos(end)] = temp;
			return false;
		}
		delete board[getPos(start)];
		board[getPos(start)] = p;
		board[getPos(end)] = temp;
		return true;
	}
	else {
		return false;
	}
}

// determines if a Pawn can be promoted
bool Board::canPawnPromote(){
	for (int i = 0; i < 8; ++i) {
		if ('P' == board[i]->Type()) {
			return true;
		}
	}
	for (int j = 56; j < 64; ++j) {
		if ('p' == board[j]->Type()) {
			return true;
		}
	}
	return false;
}

// returns if the current turn belongs to the White player
bool Board::getTurnStatus() const {
	return isTurnWhite;
}

// performs the moving of the Pieces
void Board::move(const string &start, const string &end){
	// makes the move, if valid, and checks if the opposing player is now in check
	// changes whose turn it is 
	Piece *p = getPiece(start);
	if (testMove(start,end)) {
		delete board[getPos(end)];
		board[getPos(end)] = p;
		p->changePos(getPos(end));
		board[getPos(start)] = new Empty(getPos(start));
		if (board[getPos(end)]->Type() == 'K' && !inCheck) { // handles the case of castling 
			if (start == "e1" && end == "g1") {
				Piece *castle = getPiece("h1");
				delete board[61];
				board[getPos("f1")] = castle;
				castle->changePos(61);
				board[63] = new Empty(63);
				castle->moved();
				gd->update('R',"h1","f1");
			}
			else if (start == "e1" && end == "c1") {
				Piece *castle = getPiece("a1");
				delete board[59];
				board[getPos("d1")] = castle;
				castle->changePos(59);
				board[56] = new Empty(56);
				castle->moved();
				gd->update('R',"a1","f1");
			}
		}
		else if (board[getPos(end)]->Type() == 'k' && !inCheck) { 
			if (start == "e8" && end == "g8") {
				Piece *castle = getPiece("h8");
				delete board[5];
				board[getPos("f8")] = castle;
				castle->changePos(5);
				board[7] = new Empty(7);
				castle->moved();
				gd->update('r',"h8","f8");
			}
			else if (start == "e8" && end == "c8") {
				Piece *castle = getPiece("a8");
				delete board[3];
				board[getPos("d8")] = castle;
				castle->changePos(3);
				board[0] = new Empty(0);
				castle->moved();
				gd->update('r',"a8","d8");
			}
		}
		isTurnWhite = (! isTurnWhite);
		gd->updateTurn(isTurnWhite);
		gd->update(board[getPos(end)]->Type(),start,end);
		inCheck = isCheck(isTurnWhite);
		p->moved();
		
		if (isCheck(true)) {
			s->check(true);
		}
		else if (isCheck(false)) {
			s->check(false);
		}

		if (inCheck && isCheckmate()) {
			string winner;
			if (isTurnWhite) {
				winner = "black";
			}
			else { 
				winner = "white";
			}
			endGame(winner);
			return; 
		}
		else if (isStalemate()) {
			endGame("draw");
			return;
		}
	}else{
		cout << "Invalid move. Please try again" << endl;
	}
}

// determines if a Player is in check
bool Board::isCheck(bool isWhite) {
	string king = findKing(isWhite);
	bool flag = false; // flag will change to true if an opposing piece can move
	// to the space of the King 
	for(int i = 0; i < 64; ++i){
		if (board[i]->canMove(getCor(i),king, getBoard())) {
			flag = true;
		}
	}
	return flag;
}

// ends the game and clears the board through a method calls
void Board::endGame(string cmd) {
	gameOver = true;
	if (cmd == "black") {
		s->win(false);
		gd->updateScore(false,false);
	}
	else if (cmd == "white") {
		s->win(true);
		gd->updateScore(true,false);
	}
	else if (cmd == "white resigns") {
		s->resign(true);
		gd->updateScore(false,false);
	}
	else if (cmd == "black resigns") {
		s->resign(false);
		gd->updateScore(true,false);
	}
	else if (cmd == "draw") {
		s->tie();
		gd->updateScore(false,true);
	}
	clearBoard();
	gd->blankBoard();
}

// accessor/getter: returns the gameOver field of the Board class
bool Board::isGameOver(){
	return gameOver;
}

// mutator/setter: sets the gameOver field of the Board class to false.
void Board::gameOn(){
	gameOver = false;
}

// checks for Board validity
bool Board::validBoard() {
	int numBlackKings = 0;
	int numWhiteKings = 0;
	for (int i = 0; i < 8; ++i) {
		if (board[i]->Type() =='P' || board[i]->Type() =='p') {
			return false;
		}
		else if (board[i]->Type() == 'K') {
			++numWhiteKings;
		}
		else if (board[i]->Type() == 'k') {
			++numBlackKings;
		}
	}
	for (int j = 8; j < 56; ++j) {
		if (board[j]->Type() == 'K') {
			++numWhiteKings;
		}
		else if (board[j]->Type() == 'k') {
			++numBlackKings;
		}
	}
	for (int k = 56; k < 64; ++k) {
		if (board[k]->Type() =='P' || board[k]->Type() =='p') {
			return false;
		}
		else if (board[k]->Type() == 'K') {
			++numWhiteKings;
		}
		else if (board[k]->Type() == 'k') {
			++numBlackKings;
		}
	}
	if (numBlackKings != 1 || numWhiteKings != 1) {
		return false;
	}
	else if (isCheckmate()) {
		return false;
	}
	else if (isStalemate()) {
		return false;
	}
	else {
		return true;
	}
}

// checks if there is a checkmate on the Board
bool Board::isCheckmate() {
	int king = getPos(findKing(isTurnWhite));
	if (isTurnWhite) {
		for (int i = 0; i < 64; ++i) {
			char type = board[i]->Type();
			if (isTurnWhite == board[i]->isWhite() && 'P' == type &&
				(testMove(getCor(i), getCor(i-1)) || testMove(getCor(i), getCor(i+1)) || 
					testMove(getCor(i), getCor(i-9)) || testMove(getCor(i), getCor(i-8)) || 
					testMove(getCor(i), getCor(i-7)))) {
				return false;
			}
			else if (isTurnWhite == board[i]->isWhite()) {
				for (int j = 0; j < 64; ++j) {
					if (j == i) {
						continue;
					}
					else if (testMove(getCor(i), getCor(j))) {
						return false;
					}
				}
			}
			else {
				continue;
			}
		}
	}
	else {
		for(int i = 0; i < 64; ++i) {
			char type = board[i]->Type();
			if (isTurnWhite == board[i]->isWhite() && 'p' == type &&
				(testMove(getCor(i), getCor(i-1)) || testMove(getCor(i), getCor(i+1)) || 
					testMove(getCor(i), getCor(i-9)) || testMove(getCor(i), getCor(i-8)) || 
					testMove(getCor(i), getCor(i-7)))) {
				return false;
			}
			else if (isTurnWhite == board[i]->isWhite()) {
				for (int j = 0; j < 64; ++j) {
					if (j == i) {
						continue;
					}
					else if (testMove(getCor(i), getCor(j))) {
						return false;
					}
				}
			}
			else {
				continue;
			}
		}
	}
	return true;
}

// checks if there is a stalemate on the Board
bool Board::isStalemate(){
	if (isTurnWhite) {
		for(int i = 0; i < 64; ++i) {
			char type = board[i]->Type();
			if (isTurnWhite == board[i]->isWhite() && 'P' == type &&
				(testMove(getCor(i), getCor(i-1)) || testMove(getCor(i), getCor(i+1)) || 
					testMove(getCor(i), getCor(i-9)) || testMove(getCor(i), getCor(i-8)) || 
					testMove(getCor(i), getCor(i-7)))) {
				return false;
			}
			else if (isTurnWhite == board[i]->isWhite()) {
				for (int j = 0; j < 64; ++j) {
					if (j == i) {
						continue;
					}
					else if (testMove(getCor(i), getCor(j))) {
						return false;
					}
				}
			}
			else {
				continue;
			}
		} 
	}
	else {
		for (int i = 0; i < 64; ++i) {
			char type = board[i]->Type();
			if (isTurnWhite == board[i]->isWhite() && 'p' == type &&
				(testMove(getCor(i), getCor(i-1)) || testMove(getCor(i), getCor(i+1)) || 
					testMove(getCor(i), getCor(i-9)) || testMove(getCor(i), getCor(i-8)) || 
					testMove(getCor(i), getCor(i-7)))) {
				return false;
			}
			else if (isTurnWhite == board[i]->isWhite()) {
				for (int j = 0; j < 64; ++j) {
					if (j == i) {
						continue;
					}
					else if (testMove(getCor(i), getCor(j))) {
						return false;
					}
				}
			}
			else {
				continue;
			}
		}
	}
	return true;
}

// sends the Board to be displayed as text
string Board::sendToDisplay() const{
	ostringstream oss;
	char zero = '0';
	int j = 0;
	int end = 8;
	for(int i = 8; i > 0; --i) {
		char temp = zero + i;
		oss << temp << " "; 
		for (; j < end; ++j) {
			oss << (board[j]->Type());
		}
		end += 8;
		oss << "\n";
	}
	oss << "\n  ";
	for (int k = 0; k < 8; ++k) {
		char temp = 'a' + k;
		oss << temp;
	}
	oss << '\n';
	oss << endl;
	return oss.str();
}


/*
ostream& operator<<(ostream& out, Board& b) {
	char zero = '0';
	int end = 8;

	for(int i = 8; i > 0; --i) {
		char temp = zero + i;
		out << temp << " "; 
		for (int j = 0; j < end; ++j) {
			out << (b.board[j]->Type());
		}
		end += 8;
		out << endl;
	}

	out << "\n  ";
	for (int k = 0; k < 8; ++k) {
		char temp = 'a' + k;
		out << temp;
	}

	out << '\n';
	return out;
}*/


// sets the turn of the Board to colour
void Board::setTurn(string colour) {
	if ("black" == colour || "BLACK" == colour) {
		isTurnWhite = false;
	}
	else if ("white" == colour || "WHITE" == colour) {
		isTurnWhite = true;
	}
	gd->updateTurn(isTurnWhite);
}

// finds the Kings on the Board
string Board::findKing(bool isWhite) const {
	char king = 'k';
	if (isWhite) {
		king = 'K';
	}
	for (int i = 0; i < 64; ++i) {
		if (king == (board[i])->Type()) {
			return getCor(i); 
		}
	}
	return "";
}

// calls the printScore method on the Scoreboard
void Board::printScore() const {
	s->printScore();
}

// accessor/getter: gets the Board
Piece ** Board::getBoard(){
	Piece ** tmp = board; 
	return tmp;
}

// accessor/getter: gets the Piece stored at cmd
Piece *Board::getPiece(const string &cmd) {
	int index = getPos(cmd);
	return board[index];
}

// mutator/setter: sets the GraphicsDisplay to g
void Board::setgd(GraphicsDisplay *g) {
	this->gd = g;
}

// returns if Player 1 is a computer
bool Board::isP1computer(){
	return p1->isComputer();
}

// returns if Player 2 is a computer
bool Board::isP2computer() {
	return p2->isComputer();
}

// makes a move for the Computer
void Board::makeCompMove(){
	string start;
	string last;
	if (isTurnWhite) {
		p1->generateMove(this,start,last);
	}
	else {
		p2->generateMove(this,start,last);
	}
	move(start,last);
}

