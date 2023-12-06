#include <iostream>
#include <sstream>
#include <string>
#include "board.h"
#include "player.h"
#include "scoreboard.h"
#include "piece.h"
#include "blank.h"
#include "pawn.h"
#include "knight.h"
#include "bishop.h"
#include "rook.h"
#include "queen.h"
#include "king.h"
#include "graphicsdisplay.h"

using namespace std;

Board::Board(int player1, int player2): board{new Piece*[64]}, Turn{true},
		inCheck{false}, gameOver{true}, s{new Scoreboard()}, p1{new Player(true)}, p2{new Player(false)}{
			for (int i = 0; i < 64; ++i) {
				board[i] = new Blank(i);
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
		board[i] = new Blank(i);
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
		board[j] = new Blank(j);
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

void Board::place(char piece, const string &task) { 
	char p = piece;
	int index = arrayloc(task);
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
		board[index] = new Blank(index);
	}
	gd->set(p,task);
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
		board[arrayloc(end)] = p;
		board[arrayloc(start)] = new Blank(arrayloc(start));
		if (Check(Turn)) {
			delete board[arrayloc(start)];
			board[arrayloc(start)] = p;
			board[arrayloc(end)] = temp;
			return false;
		}
		delete board[arrayloc(start)];
		board[arrayloc(start)] = p;
		board[arrayloc(end)] = temp;
		return true;
	}
	else {
		return false;
	}
}

bool Board::Promotion(){
	for (int i = 0; i < 8; ++i) {
		if ('P' == board[i]->PT()) {
			return true;
		}
	}
	for (int j = 56; j < 64; ++j) {
		if ('p' == board[j]->PT()) {
			return true;
		}
	}
	return false;
}

bool Board::getTurnStatus() const {
	return Turn;
}

void Board::move(const string &start, const string &end){
	Piece *p = getPiece(start);
	if (testMove(start,end)) {
		delete board[arrayloc(end)];
		board[arrayloc(end)] = p;
		p->changePos(arrayloc(end));
		board[arrayloc(start)] = new Blank(arrayloc(start));
		if (board[arrayloc(end)]->PT() == 'K' && !inCheck) {
			if (start == "e1" && end == "g1") {
				Piece *castle = getPiece("h1");
				delete board[61];
				board[arrayloc("f1")] = castle;
				castle->changePos(61);
				board[63] = new Blank(63);
				castle->moved();
				gd->update('R',"h1","f1");
			}
			else if (start == "e1" && end == "c1") {
				Piece *castle = getPiece("a1");
				delete board[59];
				board[arrayloc("d1")] = castle;
				castle->changePos(59);
				board[56] = new Blank(56);
				castle->moved();
				gd->update('R',"a1","f1");
			}
		}
		else if (board[arrayloc(end)]->PT() == 'k' && !inCheck) { 
			if (start == "e8" && end == "g8") {
				Piece *castle = getPiece("h8");
				delete board[5];
				board[arrayloc("f8")] = castle;
				castle->changePos(5);
				board[7] = new Blank(7);
				castle->moved();
				gd->update('r',"h8","f8");
			}
			else if (start == "e8" && end == "c8") {
				Piece *castle = getPiece("a8");
				delete board[3];
				board[arrayloc("d8")] = castle;
				castle->changePos(3);
				board[0] = new Blank(0);
				castle->moved();
				gd->update('r',"a8","d8");
			}
		}
		Turn = (! Turn);
		gd->updateTurn(Turn);
		gd->update(board[arrayloc(end)]->PT(),start,end);
		inCheck = Check(Turn);
		p->moved();
		
		if (Check(true)) {
			s->check(true);
		}
		else if (Check(false)) {
			s->check(false);
		}

		if (inCheck && Checkmate()) {
			string winner;
			if (Turn) {
				winner = "black";
			}
			else { 
				winner = "white";
			}
			endGame(winner);
			return; 
		}
		else if (Statemate()) {
			endGame("draw");
			return;
		}
	}
}

bool Board::Check(bool isWhite) {
	string king = findKing(isWhite);
	bool flag = false;
	for(int i = 0; i < 64; ++i){
		if (board[i]->validMove(BoardCoord(i),king, getBoard())) {
			flag = true;
		}
	}
	return flag;
}

void Board::endGame(string task) {
	gameOver = true;
	if (task == "black") {
		s->win(false);
		gd->updateScore(false,false);
	}
	else if (task == "white") {
		s->win(true);
		gd->updateScore(true,false);
	}
	else if (task == "white resigns") {
		s->resign(true);
		gd->updateScore(false,false);
	}
	else if (task == "black resigns") {
		s->resign(false);
		gd->updateScore(true,false);
	}
	else if (task == "draw") {
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
		if (board[i]->PT() =='P' || board[i]->PT() =='p') {
			return false;
		}
		else if (board[i]->PT() == 'K') {
			++numWhiteKings;
		}
		else if (board[i]->PT() == 'k') {
			++numBlackKings;
		}
	}
	for (int j = 8; j < 56; ++j) {
		if (board[j]->PT() == 'K') {
			++numWhiteKings;
		}
		else if (board[j]->PT() == 'k') {
			++numBlackKings;
		}
	}
	for (int k = 56; k < 64; ++k) {
		if (board[k]->PT() =='P' || board[k]->PT() =='p') {
			return false;
		}
		else if (board[k]->PT() == 'K') {
			++numWhiteKings;
		}
		else if (board[k]->PT() == 'k') {
			++numBlackKings;
		}
	}
	if (numBlackKings != 1 || numWhiteKings != 1) {
		return false;
	}
	else if (Checkmate()) {
		return false;
	}
	else if (Statemate()) {
		return false;
	}
	else {
		return true;
	}
}

bool Board::Checkmate() {
	int king = arrayloc(findKing(Turn));
	if (Turn) {
		for (int i = 0; i < 64; ++i) {
			char type = board[i]->PT();
			if (Turn == board[i]->isWhite() && 'P' == type &&
				(testMove(BoardCoord(i), BoardCoord(i-1)) || testMove(BoardCoord(i), BoardCoord(i+1)) || 
					testMove(BoardCoord(i), BoardCoord(i-9)) || testMove(BoardCoord(i), BoardCoord(i-8)) || 
					testMove(BoardCoord(i), BoardCoord(i-7)))) {
				return false;
			}
			else if (Turn == board[i]->isWhite()) {
				for (int j = 0; j < 64; ++j) {
					if (j == i) {
						continue;
					}
					else if (testMove(BoardCoord(i), BoardCoord(j))) {
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
			char type = board[i]->PT();
			if (Turn == board[i]->isWhite() && 'p' == type &&
				(testMove(BoardCoord(i), BoardCoord(i-1)) || testMove(BoardCoord(i), BoardCoord(i+1)) || 
					testMove(BoardCoord(i), BoardCoord(i-9)) || testMove(BoardCoord(i), BoardCoord(i-8)) || 
					testMove(BoardCoord(i), BoardCoord(i-7)))) {
				return false;
			}
			else if (Turn == board[i]->isWhite()) {
				for (int j = 0; j < 64; ++j) {
					if (j == i) {
						continue;
					}
					else if (testMove(BoardCoord(i), BoardCoord(j))) {
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

bool Board::Statemate(){
	if (Turn) {
		for(int i = 0; i < 64; ++i) {
			char type = board[i]->PT();
			if (Turn == board[i]->isWhite() && 'P' == type &&
				(testMove(BoardCoord(i), BoardCoord(i-1)) || testMove(BoardCoord(i), BoardCoord(i+1)) || 
					testMove(BoardCoord(i), BoardCoord(i-9)) || testMove(BoardCoord(i), BoardCoord(i-8)) || 
					testMove(BoardCoord(i), BoardCoord(i-7)))) {
				return false;
			}
			else if (Turn == board[i]->isWhite()) {
				for (int j = 0; j < 64; ++j) {
					if (j == i) {
						continue;
					}
					else if (testMove(BoardCoord(i), BoardCoord(j))) {
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
			char type = board[i]->PT();
			if (Turn == board[i]->isWhite() && 'p' == type &&
				(testMove(BoardCoord(i), BoardCoord(i-1)) || testMove(BoardCoord(i), BoardCoord(i+1)) || 
					testMove(BoardCoord(i), BoardCoord(i-9)) || testMove(BoardCoord(i), BoardCoord(i-8)) || 
					testMove(BoardCoord(i), BoardCoord(i-7)))) {
				return false;
			}
			else if (Turn == board[i]->isWhite()) {
				for (int j = 0; j < 64; ++j) {
					if (j == i) {
						continue;
					}
					else if (testMove(BoardCoord(i), BoardCoord(j))) {
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
			oss << (b.board[j]->PT());
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
		Turn = false;
	}
	else if ("white" == colour || "WHITE" == colour) {
		Turn = true;
	}
	gd->updateTurn(Turn);
}

string Board::findKing(bool isWhite) const {
	char king = 'k';
	if (isWhite) {
		king = 'K';
	}
	for (int i = 0; i < 64; ++i) {
		if (king == (board[i])->PT()) {
			return BoardCoord(i); 
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

Piece *Board::getPiece(const string &task) {
	int index = arrayloc(task);
	return board[index];
}

void Board::setgd(GraphicsDisplay *g) {
	this->gd = g;
}

bool Board::P1computer(){
	return p1->isComputer();
}

bool Board::P2computer() {
	return p2->isComputer();
}

void Board::ComputerMove(){
	string start;
	string last;
	if (Turn) {
		p1->generateMove(this,start,last);
	}
	else {
		p2->generateMove(this,start,last);
	}
	move(start,last);
}

