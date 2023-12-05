#include <sstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "computer.h"
#include "player.h"
#include "piece.h"
#include "board.h"

static std::string convert(int index){
	std::string s;
	std::ostringstream oss;
	char row = '0' + (8 - (index / 8)); 
	char col = 'a' + (index % 8);
	oss << col;
	oss << row;
	s = oss.str();
	return s;
}

Comp::Comp(int level, bool white): Player{white}, level{level} {}

void Comp::generateMove(Board *b, std::string &first, std::string &last){
	if(1 == level){
		genMove1(b,first, last);
	} else if(2 == level){
		genMove1(b,first, last);
	} else if(3 == level){
		genMove1(b,first, last);
	} else if(4 == level){
		genMove1(b,first, last);
	} else{
		genMove1(b,first, last);
	}
}

void Comp::genMove1(Board *b, std::string &first, std::string &last){
	std::vector <Piece *> myTeam; 
	for(int i=0; i<64; ++i){
		if(!b->getBoard()[i]->isEmpty() && b->getBoard()[i]->isWhite() == isPlayerWhite()){
			myTeam.push_back(b->getBoard()[i]);
		}
	}
	std::srand(std::time(nullptr));
	int start = std::rand()/((RAND_MAX + 1u)/myTeam.size());
	Piece *p = myTeam[start];
	int end = -1;
	if(isPlayerWhite()){
		while(true){	
			for(int j=63; j>-1; --j){
				if(b->testMove(convert(p->squarelocation()),convert(j))){
					end = j;
					break; 
				}
			}
			if(end != -1){
				break;
			}
			start = std::rand()/((RAND_MAX + 1u)/myTeam.size());
			p = myTeam[start];
		}
	} else {
		while(true){	
			for(int k=0; k<64; ++k){
				if(b->testMove(convert(p->squarelocation()),convert(k))){
					end = k;
					break; 
				}
			}
			if(end != -1){
				break;
			}
			start = std::rand()/((RAND_MAX + 1u)/myTeam.size());
			p = myTeam[start];
		}
	}
	first = convert(p->squarelocation());
	last = convert(end);
	return;
}

bool Comp::isComputer() const{
	return true;
}
