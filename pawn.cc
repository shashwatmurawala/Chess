#include "pawn.h"
#include <iostream>

Pawn::Pawn (Cell *next, int x, int y, Colour col):
    next{next}, x{x}, y{y}, col{col}, alive{true} {}

Pawn::~Pawn () {
    delete next;
}

void Pawn::move (int x1, int y1, int x2, int y2) {
    if (x == x1 && y == y1 && alive) {
        this->x = x2;
        this->y = y2;
	return;
    }
    else {
	 return next->move(x1, y1, x2, y2);
    }
}

Colour Pawn::getColour (int x1, int y1) {
    if (x == x1 && y == y1 && alive) return col;
    else return next->getColour(x1, y1);
}
void Pawn::setDead (int x1, int y1) {
    if (x1 == x && y1 == y) alive = false;
    else { next->setDead(x1, y1); }
}
void Pawn::setAlive (int x1, int y1) {
    if (x1 == x && y1 == y && alive) alive = true;
    else { next->setAlive(x1, y1); }
}
char Pawn::getTile (int x1, int y1) {
    if (x1 == x && y1 == y && col == Colour::WHITE && alive) return 'p';
    else if (x1 == x && y1 == y && alive) return 'P';
    else return next->getTile(x1, y1);
}
void Pawn::setOpening (int x1, int y1) {
    if (x == x1 && y == y1 && alive) {
        first_move = false;
    }
    else {
        return next->setOpening(x1, y1);
    }
}
bool Pawn::getOpening (int x1, int y1) {
    if (x == x1 && y == y1 && alive) {
        return first_move;
    }
    else {
        return next->getOpening(x1, y1);
    }
}
