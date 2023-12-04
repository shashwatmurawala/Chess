void Controller::beginGame() {
	if (!setup) {
		cout << "The game must be setup before continuing." << endl;
	} else {
		game->playGame();
		white_score += game->getWhite();
		black_score += game->getBlack();
		delete game;
		setup = false;
		cout << "To continue playing setup another game" << endl;
	}

}
