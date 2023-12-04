#ifndef _PIECE_H
#define _PIECE_H

#include "board.h"

class Piece : public Cell {
    public:
        Piece ();
        ~Piece () = default;
};

#endif
