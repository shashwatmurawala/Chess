#include <iostream>
#include <sstream>
#include <string>
#include "controller.h"
using namespace std;


Controller::Controller(GameManager& gm): gm {gm}, graphicView {nullptr} {
	board = gm.getBoard(); // returns a raw pointer

	// ownership of board corresponds to gm
	// but controller simply 'has-a' board


	cout << "Playing Chess with CS 246!" << endl;
	showCommands();
};

void Controller::showCommands() const {
	cout << " === Command ===	=== Description ===" << endl;
	cout << " 	- setup 		Enters setup mode" << endl;
	cout << "	- done			Leaves setup mode (if in a valid board state)" << endl;
	cout << "	- game <white> <black>  Creates a new game with the given players." << endl;
	cout << "				(each of the players may be 'human' or 'computer[x]')" << endl;
}

void Controller::setup() {
	requiresDefaultSetup = false;

	if(!graphicView){
		graphicView = new GraphicsDisplay();
		board->setgd(graphicView);
	}

	board->clearBoard();

	string action;
	char piece;
	string colour;
	string coord;

	while (cin >> action) {

		// placing a piece
		if (action[0] == '+') {
			cin >> piece >> coord;
			if (coord[0] >= 'a' && coord[0] <= 'h' && 
				coord[1] >= '1' && coord[1] <= '8') {
				board->place(piece, coord);
				cout << board->sendToDisplay();
				//cout << board << endl; //doesn't work
			}
		}

		// setting whose turn is next
		else if (action[0] == '=') {
			cin >> colour;
			board->setTurn(colour);
		}

		// removing a piece
		else if (action[0] == '-') {
			cin >> coord;
			if (coord[0] >= 'a' && coord[0] <= 'h' &&
				coord[1] >= '1' && coord[1] <= '8') {
				// insert remove method
				board->place('e',coord);
				cout << board->sendToDisplay();
			}
		}

		// complete setup mode
		else if (action == "done" && board->validBoard()) {
			// check for valid board before exiting
			board->gameOn();	
			break;
		}

		else if (action == "done" && !board->validBoard()) {
			// check for valid board before exiting
			cout << "Invalid board. Continue placing pieces." << endl;
		}

	}
}

void Controller::game() {
	string action;
	string start;
	string end;

	if (requiresDefaultSetup) {

		if (!graphicView) {
			graphicView = new GraphicsDisplay();
			board->setgd(graphicView);
		}

		board->normalSetup();
	}

	cout << board->sendToDisplay();

	if (board->isP1computer() && board->isP2computer()){
		while(!board->isGameOver()){
			board->makeCompMove();
			cout << board->sendToDisplay();
		}

	} else if (board->isP1computer()) {
		
		while(true) {
			if (board->getTurnStatus()) {
				board->makeCompMove();
			} else {
				cin >> action;

				if (action == "move") {
					cin >> start >> end;
					// insert move method
					if(start.length() != 2 || end.length() != 2){
						cout << "Invalid move. Try again." << endl;
						continue;
					}
					board->move(start,end);
					if (board->canPawnPromote()) { // requires input from the user in the case of pawn promotion
						cout << "Your pawn has been promoted. Select a piece" << endl;
						string prom;
						cin >> prom;
						while (!('r' == prom[0] || prom[0] == 'n' || 'q' == prom[0] || 'b' == prom[0])){
							cout << "Invalid promotion" << endl;
							if(!(cin >> prom)){
								return;
							}
						}
						board->place(prom[0], end);
					}
					if(board->isGameOver()){
						break;
					}
					cout << board->sendToDisplay();
				}	

				else if (action == "resign") {
						board->endGame("black resigns");
						break;
				}
			}
		}

	} else if (board->isP2computer()) {

		while(true){

			if (!board->getTurnStatus()) {
				board->makeCompMove();
			} else {
				cin >> action;
				if (action == "move") {
					cin >> start >> end;
					// insert move method
					if(start.length() != 2 || end.length() != 2){
						cout << "Invalid move. Try again." << endl;
						continue;
					}
					board->move(start,end);
					if (board->canPawnPromote()) { // requires input from the user in the case of pawn promotion
						cout << "Your pawn has been promoted. Select a piece" << endl;
						string prom;
						cin >> prom;
						while (!('R' == prom[0] || prom[0] == 'N' || 'Q' == prom[0] || 'B' == prom[0])){
							cout << "Invalid promotion" << endl;
							if(!(cin >> prom)){
								return;
							}
						}
						board->place(prom[0], end);
					}
					cout << board->sendToDisplay();
				}	
				else if (action == "resign") {
						board->endGame("white resigns");
						break;
				}
			}
			if(board->isGameOver()){
				break;
			}
		}
	} else {
		while (cin >> action) { // 
			// move command
			if (action == "move") {
				cin >> start >> end;
				// insert move method
				if(start.length() != 2 || end.length() != 2){
					cout << "Invalid move. Try again." << endl;
					continue;
				}
				board->move(start,end);
				if (board->canPawnPromote()) { // requires input from the user in the case of pawn promotion
					cout << "Your pawn has been promoted. Select a piece" << endl;
					string prom;
					bool validProm = false;
					while(!validProm){
						if(!(cin >> prom)){
								return;
						}
						if (!board->getTurnStatus() && 
						('R' == prom[0] || prom[0] == 'N' || 'Q' == prom[0] || 'B' == prom[0])) {
							validProm = true;
						}
						else if ('r' == prom[0] || prom[0] == 'n' || 
							'q' == prom[0] || 'b' == prom[0]) {
							validProm = true;
						}
						else {
							cout << "Invalid promotion" << endl;
						}
					}
					board->place(prom[0], end);
				}
				if(board->isGameOver()){
					break;
				}
				cout << board->sendToDisplay();
			}
			else if (action == "resign") {
				// insert resign method
				if(board->getTurnStatus()){
					board->endGame("white resigns");
				} else {
					board->endGame("black resigns");
				}
				break;
			}
		}
	} 
}

void Controller::players() {
	board->gameOn();
	string p1;
	string p2;
	int ip1;
	int ip2;

	cin >> p1 >> p2;

	// setup Board with humans or computers
	if (p1 == "human") {
		ip1 = 0;
	}

	else if (p1 != "human") {
		char temp = p1[p1.length()-2];
		ip1 = temp - '0';
	}

	if (p2 == "human") {
		ip2 = 0;
	}

	else if (p2 != "human") {
		char temp = p2[p2.length() - 2];
		ip2 = temp - '0';
	}

	if (ip1 != 0 || ip2 != 0) {
		board->newPlayers(ip1,ip2);	
	}
}

