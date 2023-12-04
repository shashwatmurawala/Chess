#include "king.h"

King::King (Cell *next, int x, int y, Colour col):
    next{next}, x{x}, y{y}, col{col}, alive{true} {}

King::~King () {
    delete next;
}
void King::move (int x1, int y1, int x2, int y2) {
    if (x == x1 && y == y1 && alive) {
        x = x2;
        y = y2;
    }
    else return next->move(x1, y1, x2, y2);
}

Colour King::getColour (int x1, int y1) {
    if (x == x1 && y == y1 && alive) return col;
    else return next->getColour(x1, y1);
}
void King::setDead (int x1, int y1) {
    if (x1 == x && y1 == y && alive) alive = false;
    else { next->setDead(x1, y1); }
}
void King::setAlive (int x1, int y1) {
    if (x1 == x && y1 == y) alive = true;
    else { next->setAlive(x1, y1); }
}
char King::getTile (int x1, int y1) {
    if (x1 == x && y1 == y && col == Colour::WHITE && alive) return 'k';
    else if (x1 == x && y1 == y && alive) return 'K';
    else return next->getTile(x1, y1);
}
void King::setFirstMove (int x1, int y1) {
    if (x == x1 && y == y1 && alive) {
        first_move = false;
    }
    else {
        return next->setFirstMove(x1, y1);
    }
}
bool King::getFirstMove (int x1, int y1) {
    if (x == x1 && y == y1 && alive) {
        return first_move;
    }
    else {
        return next->getFirstMove(x1, y1);
    }
}
