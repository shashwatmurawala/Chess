#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H
#include "observer.h"
#include "gamemanager.h"
#include <iostream>


class TextDisplay : public Observer {
    GameManager &game;
    int row, col, sidenums;
    char bottomletters = 'a';
    
    std::ostream &out = std::cout;

    public:
    TextDisplay (GameManager &game, int row, int col, int sidenums);
    ~TextDisplay () = default;
    private:
        void display() override;
};


#endif

