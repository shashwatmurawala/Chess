#include "stack.h"

void Stack::push(std::pair<std::pair<int, int>, std::pair<int, int>> *exp) {
	data.push_back(exp);
}

std::pair<std::pair<int,int>, std::pair<int,int>> *Stack::pop () {
	std::pair<std::pair<int,int>, std::pair<int,int>> *temp = data.back();
	data.pop_back();
	return temp;
}

std::pair<std::pair<int,int>, std::pair<int,int>> *Stack::peek() {
	return data.back();
}

int Stack::length () {
	return data.size();
}

Stack::~Stack () {
    for (auto it : data) {
        delete it;
    }
}
