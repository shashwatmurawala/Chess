#include "bishop.h"

Bishop::Bishop (Cell *next, int x, int y, Colour col):
    next{next}, x{x}, y{y}, col{col}, alive{true} {}

Bishop::~Bishop () {
    delete next;
}

void Bishop::move (int x1, int y1, int x2, int y2) {
    if (x == x1 && y == y1 && alive) {
        x = x2;
        y = y2;
    }
    else return next->move(x1, y1, x2, y2);
}

Colour Bishop::getColour (int x1, int y1) {
    if (x == x1 && y == y1 && alive) return col;
    else return next->getColour(x1, y1);
}
void Bishop::setDead (int x1, int y1) {
    if (x1 == x && y1 == y && alive) alive = false;
    else { next->setDead(x1, y1); }
}
void Bishop::setAlive (int x1, int y1) {
    if (x1 == x && y1 == y) alive = true;
    else { next->setAlive(x1, y1); }
}
char Bishop::getTile (int x1, int y1) {
    if (x1 == x && y1 == y && col == Colour::WHITE && alive) return 'b';
    else if (x1 == x && y1 == y && alive) return 'B';
    else return next->getTile(x1, y1);
}
void Bishop::setOpening (int x1, int y1) {
    if (x == x1 && y == y1 && alive) {
        first_move = false;
    }
    else {
        return next->setOpening(x1, y1);
    }
}
bool Bishop::getOpening (int x1, int y1) {
    if (x == x1 && y == y1 && alive) {
        return first_move;
    }
    else {
        return next->getOpening(x1, y1);
    }
}
