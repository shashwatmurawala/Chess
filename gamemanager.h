#ifndef __GAME_MANAGER_H__
#define __GAME_MANAGER_H__

#include <memory>
#include "board.h"

class GameManager {
	
	std::unique_ptr<Board> chessboard;

	public:
		GameManager();
		~GameManager() = default;

		Board* getBoard() const;
		void printScore() const;

};


#endif
