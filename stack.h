#ifndef STACK_H
#define STACK_H

#include <vector>

class Stack {
	public:
		std::vector<std::pair<std::pair<int, int>, std::pair<int, int>> *> data;
        ~Stack ();
		void push (std::pair<std::pair<int,int>, std::pair<int,int>> *exp);
		std::pair<std::pair<int,int>, std::pair<int,int>> *pop ();
		std::pair<std::pair<int,int>, std::pair<int,int>> *peek ();
		int length ();
};

#endif