#ifndef _GRAPHICDISPLAY_H
#define _GRAPHICDISPLAY_H

#include "window.h"
#include "observer.h"
#include "gamemanager.h"
#include <string>

class GraphicDisplay : public Observer {
    GameManager &game;
    Xwindow win;
    const int width;
    const int height;
    public:
        GraphicDisplay (GameManager &game, int width, int height);
        ~GraphicDisplay () = default;
    private:
	    void display () override;
};

#endif
