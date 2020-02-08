#pragma once

#include "game-field.h"

class Game {
	GameField playerField, aiField;
public:
	void startNewGame();
};
