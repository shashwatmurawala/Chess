#include <string>
#include "player.h"

Player::Player(bool white): isWhite{white}{}

void Player::generateMove(Board *b, std::string &first, std::string &last){}

bool Player::isComputer() const{
	return false;
}

bool Player::isPlayerWhite(){
	return isWhite;
}
