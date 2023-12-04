#include "gamemanager.h"

GameManager::GameManager (Board **board):
	theBoard{board} {}

char GameManager::getTile (int x1, int y1) {
    return (*theBoard)->getTile(x1, y1);
}

Board **GameManager::board () {
    return theBoard;
}

GameManager::~GameManager () {
    delete *theBoard;
}
