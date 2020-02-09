#include "field-maker-screen.h"

FieldMakerScreen::FieldMakerScreen(App* _app, GameField _gameField)
	: app(_app)
	, gameField(_gameField)
{
}

void FieldMakerScreen::onEvent(SDL_Event e)
{
}

void FieldMakerScreen::update(int dt)
{
}

void FieldMakerScreen::draw()
{
}

GameField FieldMakerScreen::getMakedGameField()
{
	return gameField;
}
