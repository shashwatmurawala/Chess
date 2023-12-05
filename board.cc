#include <iostream>
#include <sstream>
#include <string>
#include "board.h"
#include "player.h"
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

using namespace std;

Board::Board(int player1, int player2): board{new Piece*[64]}, isTurnWhite{true},
		inCheck{false}, gameOver{true}, s{new Scoreboard()}, p1{new Player(true)}, p2{new Player(false)}{
			for (int i = 0; i < 64; ++i) {
				board[i] = new Empty(i);
			}
			if (player1 > 0) {
				delete p1;
				p1 = new Player(true);
			}
			if (player2 > 0) {
				delete p2;
				p1 = new Player(true);
			}
		}

void Board::clearBoard(){
	for (int i = 0; i < 64; ++i) {
		delete board[i];
		board[i] = new Empty(i);
	}
}

void Board::normalSetup(){
	setTurn("white");
	gameOn();
	for (int i = 0; i < 64; ++i) {
		delete board[i];
	}
	gd->blankBoard();
	board[0] = new Rook(0,false); 
	board[1] = new Knight(1,false);
	board[2] = new Bishop(2,false);
	board[3] = new Queen(3,false);
	board[4] = new King(4,false);
	board[5] = new Bishop(5,false);
	board[6] = new Knight(6,false);
	board[7] = new Rook(7, false);
	for (int i = 8; i < 16; ++i) {
		board[i] = new Pawn(i,false);
	}
	for (int j = 16; j < 48; ++j) {
		board[j] = new Empty(j);
	}
	for (int k = 48; k < 56; ++k) {
		board[k] = new Pawn(k,true);
	}
	board[56] = new Rook(56,true);
	board[57] = new Knight(57,true);
	board[58] = new Bishop(58,true);
	board[59] = new Queen(59,true);
	board[60] = new King(60,true);
	board[61] = new Bishop(61,true);
	board[62] = new Knight(62,true);
	board[63] = new Rook(63,true);
	gd->defaultDisplay();
}

void Board::newPlayers(int player1, int player2){
	delete p1;
	delete p2;
	p1 = new Player(true);
	p2 = new Player(false);
}

void Board::place(char piece, const string &cmd) { 
	char p = piece;
	int index = getPos(cmd);
	bool isWhite = ('A' < piece) && ('Z' > piece);
	if (!isWhite){
		piece = piece - 'a' + 'A';
	}

	if (piece == 'P') {
		delete board[index];
		board[index] = new Pawn(index, isWhite);
	}
	else if (piece == 'R') {
		delete board[index];
		board[index] = new Rook(index,isWhite);
	}
	else if (piece == 'Q') {
		delete board[index];
		board[index] = new Queen(index,isWhite);
	}
	else if (piece == 'B') {
		delete board[index];
		board[index] = new Bishop(index,isWhite);
	}
	else if (piece == 'N') {
		delete board[index];
		board[index] = new Knight(index,isWhite);
	}
	else if (piece == 'K') {
		delete board[index];
		board[index] = new King(index,isWhite);
	}
	else if (piece == 'E') {
		delete board[index];
		board[index] = new Empty(index);
	}
	gd->set(p,cmd);
}

Board::~Board() {
	for(int i =0; i < 64;++i){
		delete board[i];
	}
	delete [] board;
	delete s;
	delete p1;
	delete p2;
	delete gd;
}

bool Board::testMove(const string &start, const string &end) {	
	Piece *p = getPiece(start);
	Piece *temp = getPiece(end);
	if(p->isWhite() != getTurnStatus()){
		return false;
	}

	if (p->validMove(start, end, getBoard())) {
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

bool Board::getTurnStatus() const {
	return isTurnWhite;
}

void Board::move(const string &start, const string &end){
	Piece *p = getPiece(start);
	if (testMove(start,end)) {
		delete board[getPos(end)];
		board[getPos(end)] = p;
		p->changePos(getPos(end));
		board[getPos(start)] = new Empty(getPos(start));
		if (board[getPos(end)]->Type() == 'K' && !inCheck) {
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
	}
}

bool Board::isCheck(bool isWhite) {
	string king = findKing(isWhite);
	bool flag = false;
	for(int i = 0; i < 64; ++i){
		if (board[i]->validMove(getCor(i),king, getBoard())) {
			flag = true;
		}
	}
	return flag;
}

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

bool Board::isGameOver(){
	return gameOver;
}

void Board::gameOn(){
	gameOver = false;
}

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

ostream& operator<<(ostream& out, Board& b) {
	ostringstream oss;
	char zero = '0';
	int j = 0;
	int end = 8;
	for(int i = 8; i > 0; --i) {
		char temp = zero + i;
		oss << temp << " "; 
		for (; j < end; ++j) {
			oss << (b.board[j]->Type());
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
	out << oss.str();
	return out;
}

void Board::setTurn(string colour) {
	if ("black" == colour || "BLACK" == colour) {
		isTurnWhite = false;
	}
	else if ("white" == colour || "WHITE" == colour) {
		isTurnWhite = true;
	}
	gd->updateTurn(isTurnWhite);
}

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

void Board::printScore() const {
	s->Score();
}

Piece ** Board::getBoard(){
	Piece ** tmp = board; 
	return tmp;
}

Piece *Board::getPiece(const string &cmd) {
	int index = getPos(cmd);
	return board[index];
}

void Board::setgd(GraphicsDisplay *g) {
	this->gd = g;
}

bool Board::isP1computer(){
	return p1->isComputer();
}

bool Board::isP2computer() {
	return p2->isComputer();
}

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

