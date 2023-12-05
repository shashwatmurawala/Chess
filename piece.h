#ifndef ___PIECE___
#define ___PIECE___
#include <string>

class Board;

int getPos(const std::string &cmd); 
std::string getCor(int index); 
class Piece {
	int pos;
	bool white;

	public:
		Piece(int pos, bool white);
		virtual bool validMove(const std::string &start, const std::string &end, Piece ** b) const=0;  
		bool isWhite() const;
		virtual bool isEmpty() const=0;
		int squarelocation() const;
		void changePos(int posn);
		bool ColH() const;
		bool ColA() const;
		bool Row8() const;
		bool Row1() const;
		virtual void moved();
		virtual bool first() const;
		virtual char Type() const=0;
		virtual ~Piece()=0;
};

#endif 
