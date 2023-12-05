#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

#include "gamemanager.h"

class Controller {
		
	GameManager& gm;	
	GraphicsDisplay *graphicView;
	bool requiresDefaultSetup = true;

	Board* board;

	public:
		Controller(GameManager& gm);
		void setup();
		void game();
		void players();
		void showCommands() const;

};



#endif
