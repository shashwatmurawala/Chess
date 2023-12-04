#ifndef _GAMEMANAGER_H
#define _GAMEMANAGER_H


#include "board.h"
#include "subject.h"

class GameManager : public Subject {
    Board **theBoard;
    public:
        explicit GameManager (Board **board);
        char getTile(int x1, int y1);
        Board **board();
        ~GameManager ();
};

#endif
