#ifndef _PLAYER_H
#define _PLAYER_H

#include <utility>

class Player {
    public:
        virtual ~Player () = default;
        virtual std::pair<int, int> getMove () = 0;
};

#endif
