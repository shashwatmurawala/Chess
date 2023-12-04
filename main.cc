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

#include <utility>
#include <memory>
#include <iostream>
#include <string>

using namespace std;

int main () {
    bool setup = false;
    int white_score = 0;
    int black_score = 0;
    string inp;
    Board *head = nullptr;
    GameManager *gm = nullptr;
    Game *game = nullptr;
    Observer *txt = nullptr;
    Observer *graph = nullptr;

    cout << "Welcome to CS 246's Chess" << endl;
    cout << "You are able to use the command list at any point in time view your current options" << endl;
    while (cin >> inp) {
        if (inp == "game") {
            if (!setup) {
                cout << "The game must be setup before continuing." << endl;
            }
            else {
                game->playGame();
                white_score += game->getWhite();
                black_score += game->getBlack();
                delete game;
                setup = false;
                cout << "To continue playing setup another game" << endl;
            }
        }
        else if (inp == "setup") {
            head = new Blank{};
            gm = new GameManager{&head};
            game = new Game {&head, gm, nullptr, nullptr};
            game->setPlayer1(new Human{});
            game->setPlayer2(new Human{});
            txt = new TextDisplay {*gm, 8, 8, 8};
            gm->attach(txt);
            graph = new GraphicDisplay {*gm, 8, 8};
            gm->attach(graph);

	        cin >> inp;
            if (inp == "custom") {
                game->customSetup();
                setup = true;
            }
            else if (inp == "default") {
                game->defaultSetup();
                setup = true;
            }
            else {
                cout << "Invalid command " << inp << " use list for more options" << endl;
            }	
        }
        else if (inp == "list") {
            cout << "Commands:" << endl;
            cout << "- game" << endl;
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
