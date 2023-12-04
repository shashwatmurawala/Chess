#include "human.h"

std::pair<int, int> Human::getMove () {
    std::string inp;
    std::pair<int, int> res {-1, -1};
    if (in >> inp) {
        if (inp.length() != 2) return res;

        res.first = inp[0] - 'a';
        res.second = inp[1] - '1';

        if (0 > res.first || res.first > 7) res.first = -1;
        if (0 > res.second || res.second > 7) res.second = -1;
    }
    else {
    	std::cout << "Could not interpret " << inp << std::endl;
    }
    return res;
}
