#include "knight.h"

Knight::Knight (Cell *next, int x, int y, Colour team):
    next{next}, x{x}, y{y}, team{team}, alive{true} {}

Knight::~Knight () {
    delete next;
}

void Knight::move (int x1, int y1, int x2, int y2) {
    if (x == x1 && y == y1 && alive) {
        x = x2;
        y = y2;
    }
    else return next->move(x1, y1, x2, y2);
}
Colour Knight::getTeam (int x1, int y1) {
    if (x == x1 && y == y1 && alive) return team;
    else return next->getTeam(x1, y1);
}
void Knight::setDead (int x1, int y1) {
    if (x1 == x && y1 == y && alive) alive = false;
    else { next->setDead(x1, y1); }
}
void Knight::setAlive (int x1, int y1) {
    if (x1 == x && y1 == y) alive = true;
    else { next->setAlive(x1, y1); }
}
char Knight::getTile (int x1, int y1) {
    if (x1 == x && y1 == y && team == Colour::WHITE && alive) return 'n';
    else if (x1 == x && y1 == y && alive) return 'N';
    else return next->getTile(x1, y1);
}
void Knight::setFirstMove (int x1, int y1) {
    if (x == x1 && y == y1 && alive) {
        first_move = false;
    }
    else {
        return next->setFirstMove(x1, y1);
    }
}
bool Knight::getFirstMove (int x1, int y1) {
    if (x == x1 && y == y1 && alive) {
        return first_move;
    }
    else {
        return next->getFirstMove(x1, y1);
    }
}