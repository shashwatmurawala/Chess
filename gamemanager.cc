#include "gamemanager.h"

GameManager::GameManager (Cell **board):
	theBoard{board} {};

char GameManager::getTile (int x1, int y1) const {
    return (*theBoard)->getTile(x1, y1);
}

Cell** GameManager::getBoard () const {
    return theBoard;
}

GameManager::~GameManager () {
    delete *theBoard;
}
