#include "rook.h"

Rook::Rook (Cell *next, int x, int y, char team):
    next{next}, x{x}, y{y}, team{team}, alive{true} {}

Rook::~Rook () {
    delete next;
}

void Rook::move (int x1, int y1, int x2, int y2) {
    if (x == x1 && y == y1 && alive) {
        x = x2;
        y = y2;
    }
    else return next->move(x1, y1, x2, y2);
}
char Rook::getTeam (int x1, int y1) {
    if (x == x1 && y == y1 && alive) return team;
    else return next->getTeam(x1, y1);
}
void Rook::setDead (int x1, int y1) {
    if (x1 == x && y1 == y && alive) alive = false;
    else { next->setDead(x1, y1); }
}
void Rook::setAlive (int x1, int y1) {
    if (x1 == x && y1 == y && alive) alive = true;
    else { next->setAlive(x1, y1); }
}
char Rook::getTile (int x1, int y1) {
    if (x1 == x && y1 == y && team == 'w' && alive) return 'r';
    else if (x1 == x && y1 == y) return 'R';
    else return next->getTile(x1, y1);
}
void Rook::setFirstMove (int x1, int y1) {
    if (x == x1 && y == y1 && alive) {
        first_move = false;
    }
    else {
        return next->setFirstMove(x1, y1);
    }
}
bool Rook::getFirstMove (int x1, int y1) {
    if (x == x1 && y == y1 && alive) {
        return first_move;
    }
    else {
        return next->getFirstMove(x1, y1);
    }
}