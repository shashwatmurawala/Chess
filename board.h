#ifndef ___BOARD___
#define ___BOARD___

#include <string>
#include <iostream>
#include "scoreboard.h"
#include "player.h"
#include "graphicsdisplay.h"

class Piece;
class Scoreboard;
class Board {
	Piece **board;
	bool Turn;
	bool inCheck;
	bool gameOver;
	Scoreboard *s;
	GraphicsDisplay *gd = nullptr;
	Player *p1;
	Player *p2;

	public:
		Board(int p1, int p2);
		~Board();

		void endGame(std::string task);
		void clearBoard();
		void normalSetup();
		void place(char piece, const std::string &task);
		bool validBoard();
		void newPlayers(int player1, int player2);
		void setTurn(std::string colour);
		void move(const std::string &start, const std::string &end);
		bool Check(bool isWhite);
		bool Checkmate(); 
		bool Statemate();
		bool Promotion();
		bool testMove(const std::string &start, const std::string &end);
		Piece *getPiece(const std::string &task);
		Piece ** getBoard();
		bool getTurnStatus() const;
		void printScore() const;
		bool isGameOver(); 
		void gameOn();
		void setgd(GraphicsDisplay *g);
		bool P1computer();
		bool P2computer();
		void ComputerMove();

		std::string findKing(bool isWhite) const;


		friend std::ostream& operator<<(std::ostream& out, Board& b);
};


#endif


