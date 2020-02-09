#pragma once

#include "../game-field.h"
#include "grid-of-chars.h"
#include "draw-context.h"

class GameFieldView {
	GameField *gameField;
	GridOfChars grid;
public:
	GameFieldView(GameField *_gameField);
	void draw(DrawContext dc, int x, int y);
};
