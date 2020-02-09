#pragma once

#include "../app.h"
#include "../game-field-view.h"
#include "../../game-field.h"
#include "screen.h"

class FieldMakerScreen : public Screen {
	App* app;
	GameField gameField;
	gameField gameFieldView;
	int currentShipSize = 4;
	int currentNumberOfShips = 1;
public:
	FieldMakerScreen(App* _app, GameField gameField);
	virtual void onEvent(SDL_Event e);
	virtual void update(int dt = 0);
	virtual void draw();
	GameField getMakedGameField();
};
