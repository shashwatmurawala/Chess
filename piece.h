#ifndef ___PIECE___
#define ___PIECE___
#include <string>

class Board;


class Piece {
	int pos;
	bool white;

	public:
		Piece(int pos, bool white);
		virtual bool canMove(const std::string &start, const std::string &end, Piece ** b) const=0;  
		bool isWhite() const;
		virtual bool isEmpty() const=0;
		int posn() const;
		void changePos(int posn);
		bool onRightEdge() const;
		bool onLeftEdge() const;
		bool onTopEdge() const;
		bool onBottomEdge() const;
		virtual void moved();
		virtual bool first() const;
		virtual char Type() const=0;
		virtual ~Piece()=0;
};

int getPos(const std::string &cmd); // converts a coordinate in the form of letter-number
// into the corresponding index in Board

std::string getCor(int index); // converts an index from Board into the 
// corresponding coordinate in the form letter-number

#endif 
