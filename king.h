#ifndef _KING_H
#define _KING_H

#include "piece.h"

class King : public Piece {
    Board *next;
    int x, y;
    char team;
    bool alive = true;
    bool first_move = true;
    public:
        void move (int x1, int y1, int x2, int y2) override;
        char getTeam (int x1, int y1) override;
        void setDead (int x, int y) override;
        void setAlive (int x, int y) override;
        char getTile (int x, int y) override;
        void setFirstMove (int x, int y) override;
        bool getFirstMove (int x, int y) override;
        King (Board *next, int x, int y, char team);
        ~King ();
};

#endif
