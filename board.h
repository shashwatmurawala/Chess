#ifndef _BOARD_H
#define _BOARD_H

#include <iostream>

enum class Colour{BLACK, WHITE, NA};

class Cell {
    public:
        virtual void move (int x1, int y1, int x2, int y2) = 0;
        virtual Colour getColour (int x1, int y1) = 0;
        virtual void setDead (int x, int y) = 0;
        virtual void setAlive (int x, int y) = 0; 
        virtual char getTile (int x, int y) = 0;
        virtual void setOpening (int x, int y) = 0;
        virtual bool getOpening (int x, int y) = 0;
        virtual ~Cell () = default;
};

#endif

