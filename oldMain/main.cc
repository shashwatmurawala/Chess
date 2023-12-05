#include <iostream>
#include <sstream>
#include <string>
#include "board.h"
using namespace std;

bool requiresDefaultSetup = true;
GraphicsDisplay *g = nullptr;

void setup(Board *b){
	requiresDefaultSetup = false;
	if(!g){
	g = new GraphicsDisplay();
	b->setgd(g);
	}
	b->clearBoard();
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
				b->place(piece, coord);
				cout << b->sendToDisplay();
			}
		}

		// setting whose turn is next
		else if (action[0] == '=') {
			cin >> colour;
			b->setTurn(colour);
		}

		// removing a piece
		else if (action[0] == '-') {
			cin >> coord;
			if (coord[0] >= 'a' && coord[0] <= 'h' &&
				coord[1] >= '1' && coord[1] <= '8') {
				// insert remove method
				b->place('e',coord);
				cout << b->sendToDisplay();
		}
	}

		// complete setup mode
		else if (action == "done" && b->validBoard()) {
			// check for valid board before exiting
			b->gameOn();	
			break;
		}
		else if (action == "done" && !b->validBoard()) {
			// check for valid board before exiting
			cout << "Invalid board. Continue placing pieces." << endl;
		}
	}
}

void game(Board *b){
	string action;
	string start;
	string end;
	if(requiresDefaultSetup){
		if(!g){
		g = new GraphicsDisplay();
		b->setgd(g);
		}
		b->normalSetup();
	}
	cout << b->sendToDisplay();
	if(b->isP1computer() && b->isP2computer()){
		while(!b->isGameOver()){
			b->makeCompMove();
			cout << b->sendToDisplay();
		}
	} else if(b->isP1computer()){
		while(true){
			if(b->getTurnStatus()){
				b->makeCompMove();
			} else {
				cin >> action;
				if (action == "move") {
					cin >> start >> end;
					// insert move method
					if(start.length() != 2 || end.length() != 2){
						cout << "Invalid move. Try again." << endl;
						continue;
					}
					b->move(start,end);
					if (b->canPawnPromote()) { // requires input from the user in the case of pawn promotion
						cout << "Your pawn has been promoted. Select a piece" << endl;
						string prom;
						cin >> prom;
						while (!('r' == prom[0] || prom[0] == 'n' || 'q' == prom[0] || 'b' == prom[0])){
							cout << "Invalid promotion" << endl;
							if(!(cin >> prom)){
								return;
							}
						}
						b->place(prom[0], end);
					}
					if(b->isGameOver()){
						break;
					}
					cout << b->sendToDisplay();
				}	
				else if (action == "resign") {
						b->endGame("black resigns");
						break;
				}
			}
		}
	} else if(b->isP2computer()){
		while(true){
			if(!b->getTurnStatus()){
				b->makeCompMove();
			} else {
				cin >> action;
				if (action == "move") {
					cin >> start >> end;
					// insert move method
					if(start.length() != 2 || end.length() != 2){
						cout << "Invalid move. Try again." << endl;
						continue;
					}
					b->move(start,end);
					if (b->canPawnPromote()) { // requires input from the user in the case of pawn promotion
						cout << "Your pawn has been promoted. Select a piece" << endl;
						string prom;
						cin >> prom;
						while (!('R' == prom[0] || prom[0] == 'N' || 'Q' == prom[0] || 'B' == prom[0])){
							cout << "Invalid promotion" << endl;
							if(!(cin >> prom)){
								return;
							}
						}
						b->place(prom[0], end);
					}
					cout << b->sendToDisplay();
				}	
				else if (action == "resign") {
						b->endGame("white resigns");
						break;
				}
			}
			if(b->isGameOver()){
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
				b->move(start,end);
				if (b->canPawnPromote()) { // requires input from the user in the case of pawn promotion
					cout << "Your pawn has been promoted. Select a piece" << endl;
					string prom;
					bool validProm = false;
					while(!validProm){
						if(!(cin >> prom)){
								return;
						}
						if (!b->getTurnStatus() && 
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
					b->place(prom[0], end);
				}
				if(b->isGameOver()){
					break;
				}
				cout << b->sendToDisplay();
			}
			else if (action == "resign") {
				// insert resign method
				if(b->getTurnStatus()){
					b->endGame("white resigns");
				} else {
					b->endGame("black resigns");
				}
				break;
			}
		}
	} 
}

void players(Board *b){
	b->gameOn();
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
		b->newPlayers(ip1,ip2);	
	}
}

int main () {
	Board *b = new Board(0,0);
	string command;

	while (cin >> cmd) {

		// setup command
		if (cmd == "setup") {
			controller.setup(b);
		}

		// game is now running
		else if (cmd == "game") {
			controller.players(b);
			controller.game(b);
		}
	}
	gm.getBoard()->printScore();
}
