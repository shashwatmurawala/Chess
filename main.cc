#include <iostream>
#include <string>
#include "controller.h"
using namespace std;

int main() {

	GameManager gm {};
	Controller controller {gm};

	string cmd;

	while (cin >> cmd) {

		if (cmd == "setup") {
			controller.setup();
		}else if (cmd == "game") {
			controller.players();
			controller.game();
		}
	}
	gm.printScore();	
}
