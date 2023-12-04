#ifndef _BOARD_H
#define _BOARD_H

#include <iostream>

class Board {
    public:
        virtual void move (int x1, int y1, int x2, int y2) = 0;
        virtual char getTeam (int x1, int y1) = 0;
        virtual void setDead (int x, int y) = 0;
        virtual void setAlive (int x, int y) = 0; 
        virtual char getTile (int x, int y) = 0;
        virtual void setFirstMove (int x, int y) = 0;
        virtual bool getFirstMove (int x, int y) = 0;
        virtual ~Board () = default;
};

#endif

