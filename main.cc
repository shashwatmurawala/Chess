#include <iostream>
#include <string>
#include "controller.h"
using namespace std;

int main() {

	GameManager gm {};
	Controller controller {gm};

	string cmd;

	while (cin >> cmd) {

		// setup command
		if (cmd == "setup") {
			controller.setup();
		}

		// game is now running
		else if (cmd == "game") {
			controller.players();
			controller.game();
		}
	}
	gm.printScore();	
}
