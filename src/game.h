#pragma once

#include "game-field.h"

class Game {
public:
	GameField playerField, aiField;
	Game();
	void startNewGame();
};
