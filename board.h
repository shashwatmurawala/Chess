#ifndef ___BOARD___
#define ___BOARD___

#include <string>
#include <iostream>
#include <vector>
#include "scoreboard.h"
#include "player.h"
#include "graphicsdisplay.h"

class Piece;


// Board objects 
class Board {
	std::vector<std::vector<Piece>> board; // an array of 64 Piece pointers
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

		// setup methods
		void endGame(std::string cmd); // cmd is "black", "white", "white resigns",
		// "black resigns" or "draw";
		void clearBoard(); // clears all the current pieces from the board 
		void normalSetup(); // default configuration for a game
		void place(char piece, const std::string &cmd); // only used during setup mode 
		bool validBoard(); // only used during setup mode, checks if board is in a valid setup
		void newPlayers(int player1, int player2); // generate two new players
		void setTurn(std::string colour); //sets turn to colour

		// game logic methods 
		void move(const std::string &start, const std::string &end);
		bool isCheck(bool isWhite); //
		bool isCheckmate(); 
		bool isStalemate();
		bool canPawnPromote();
		bool testMove(const std::string &start, const std::string &end);


	

	//  
		Piece *getPiece(const std::string &cmd); // returns a pointer to the piece stored at
	// cmd
		Piece ** getBoard(); // provides a copy of the board
	// for other classes to reference

	//
		bool getTurnStatus() const;
		void printScore() const;
		bool isGameOver(); 
		void gameOn(); // sets gameOver flag to false
		void setgd(GraphicsDisplay *g);
		std::string sendToDisplay() const;

	// 
		bool isP1computer(); // checks if P1 is a computer
		bool isP2computer(); // checks if P2 is a computer
		void makeCompMove();

		std::string findKing(bool isWhite) const;


		friend std::ostream& operator<<(std::ostream& out, Board& b);
};


#endif


