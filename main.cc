/*
    main entry point for program, holds main game loop
*/
#include "subject.h"
#include "piece.h"
#include "gamemanager.h"
#include "blank.h"
#include "pawn.h"
#include "bishop.h"
#include "rook.h"
#include "knight.h"
#include "queen.h"
#include "king.h"
#include "observer.h"
#include "graphicdisplay.h"
#include "textdisplay.h"
#include "player.h"
#include "human.h"
#include "game.h"
#include "controller.h"

#include <utility>
#include <memory>
#include <iostream>
#include <string>

using namespace std;

int main () {
    bool setup = false;
    int white_score = 0;
    int black_score = 0;
    Cell *board = nullptr;
    GameManager *gm = nullptr;
    Game *game = nullptr;
    Observer *td = nullptr;
    Observer *gd = nullptr;
    Controller controller {gm, td, gd};

    cout << "Welcome to CS 246's Chess" << endl;
    cout << "You are able to use the command list at any point in time view your current options" << endl;

    string command;
    while (cin >> command) {
        if (command == "game") {
//	    controller.beginGame();
	    // Code from here moved to controller.cc, Controller::beginGame()
	}
        else if (command == "setup") {
            head = new Blank{};
            gm = new GameManager{&head};
            game = new Game {&head, gm, nullptr, nullptr};
            game->setPlayer1(new Human{});
            game->setPlayer2(new Human{});
            td = new TextDisplay {*gm, 8, 8, 8};
            gm->attach(td);
            gd = new GraphicDisplay {*gm, 8, 8};
            gm->attach(gd);

            
	    string arg;
            cin >> arg;
	    if (arg == "custom") {
                game->customSetup();
                setup = true;
            }
            else if (arg == "default") {
                game->defaultSetup();
                setup = true;
            }
            else {
                cout << "Invalid command " << command << " use list for more options" << endl;
            }	
        }
        else if (command == "list") {
	    // Put all this into a 'showCommandList()' function
            cout << "Commands:" << endl;
            cout << " - game" << endl;
            cout << " - setup" << endl;
            cout << "\t followed by either <default> or <custom>" << endl;
        }
        else {
            cout << "Invalid Input " << inp << " use list to display options" << endl;;
        }
    }
    cout << "Final Score:" << endl;
    cout << "White: " << white_score << endl;
    cout << "Black: " << black_score << endl;
    return 0;
}
