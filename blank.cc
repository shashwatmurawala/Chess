#include "blank.h"

Blank::Blank () {
    return;
}
Blank::~Blank () {
    return;
}
char Blank::getTile (int x, int y) {
    if ((x + y) % 2 == 1) return '_';
    return ' ';
}
void Blank::move (int x1, int y1, int x2, int y2){
	return;
}
Colour Blank::getColour (int x1, int y1) {
    return Colour::NA; 
}
void Blank::setDead (int x, int y) {
    return;
}
void Blank::setAlive (int x, int y) {
    return;
}
void Blank::setFirstMove (int x, int y) {
    return;
}
bool Blank::getFirstMove (int x, int y) {
    return false;
}
