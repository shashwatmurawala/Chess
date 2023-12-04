#ifndef _BLANK_H
#define _BLANK_H

#include "board.h"

class Blank : public Board {
    public:
        Blank ();
        ~Blank ();
        void move (int x1, int y1, int x2, int y2) override;
        char getTeam (int x1, int y1) override;
        void setAlive (int x, int y) override;
        void setDead (int x, int y) override;
        char getTile (int x, int y) override;
        void setFirstMove (int x, int y) override;
        bool getFirstMove (int x, int y) override;
};

#endif
