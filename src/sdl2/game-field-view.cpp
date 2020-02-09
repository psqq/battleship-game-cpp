#include "game-field-view.h"

GameFieldView::GameFieldView(GameField* _gameField)
	: gameField(_gameField)
	, grid(gameField->getWidth(), gameField->getHeight(), ' ')
{}

void GameFieldView::draw(DrawContext dc, int x, int y)
{
	int w = gameField->getWidth();
	int h = gameField->getHeight();
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			if (gameField->isDeckOfShip(x, y)) {
				grid.setChar('#');
			}
		}
	}
	grid.draw(dc, x, y);
}
