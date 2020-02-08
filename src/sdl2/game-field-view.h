#pragma once

#include "../game-field.h"

class GameFieldView {
	GameField gameField;
public:
	GameFieldView(GameField _gameField);
	void draw(int x, int y);
};
