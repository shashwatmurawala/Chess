#ifndef _QUEEN_H
#define _QUEEN_H

#include "piece.h"

class Queen : public Piece {
    Cell *next;
    int x, y;
    Colour col;
    bool alive = true;
    bool first_move = true;
    public:
        void move (int x1, int y1, int x2, int y2) override;
        Colour getColour (int x1, int y1) override;
        void setDead (int x, int y) override;
        void setAlive (int x, int y) override;
        char getTile (int x, int y) override;
        void setOpening (int x, int y) override;
        bool getOpening (int x, int y) override;
        Queen (Cell *next, int x, int y, Colour col);
	~Queen ();
};

#endif
