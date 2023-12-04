#ifndef _GAMEMANAGER_H
#define _GAMEMANAGER_H


#include "board.h"
#include "subject.h"

class GameManager : public Subject {
    Cell **theBoard;

    public:
        explicit GameManager(Cell **board);
        char getTile(int x1, int y1) const;
        Cell **getBoard() const;
        ~GameManager ();
};

#endif
