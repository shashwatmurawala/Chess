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
	bool isTurnWhite;
	bool inCheck;
	bool gameOver;
	Scoreboard *s;
	GraphicsDisplay *gd = nullptr;
	Player *p1;
	Player *p2;

	public:
		Board(int p1, int p2);
		~Board();

		void endGame(std::string cmd);
		void clearBoard();
		void normalSetup();
		void place(char piece, const std::string &cmd);
		bool validBoard();
		void newPlayers(int player1, int player2);
		void setTurn(std::string colour);
		void move(const std::string &start, const std::string &end);
		bool isCheck(bool isWhite);
		bool isCheckmate(); 
		bool isStalemate();
		bool canPawnPromote();
		bool testMove(const std::string &start, const std::string &end);
		Piece *getPiece(const std::string &cmd);
		Piece ** getBoard();
		bool getTurnStatus() const;
		void printScore() const;
		bool isGameOver(); 
		void gameOn();
		void setgd(GraphicsDisplay *g);
		bool isP1computer();
		bool isP2computer();
		void ComputerMove();

		std::string findKing(bool isWhite) const;


		friend std::ostream& operator<<(std::ostream& out, Board& b);
};


#endif


