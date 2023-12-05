#include "gamemanager.h"

GameManager::GameManager() {
	chessboard = std::make_unique<Board>(0, 0);
}

Board* GameManager::getBoard() const {
	return chessboard.get();
}

void GameManager::printScore() const {
	chessboard->printScore();
}
