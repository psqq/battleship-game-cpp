#include "game-field.h"
#include <cstring>

GameField::GameField(int _w, int _h)
	: w(_w)
	, h(_h)
	, decks(std::vector< std::vector<bool>>(h, std::vector<bool>(w, false)))
{
}

void GameField::addShip(int numberOfDecks, int sx, int sy, Direction dir)
{
	int dx[] = {-1, 1, 0, 0};
	int dy[] = {0, 0, -1, 1};
	if ((int)dir < 0 || (int)dir > 3) {
		throw "Unknow dir for ship adding";
	}
	for (int i = 0; i < numberOfDecks; i++) {
		int x = sx + dx[(int)dir] * i;
		int y = sx + dx[(int)dir] * i;
		if (x < 0 || x >= w || y < 0 || y >= h) {
			throw "Unknow position for ship adding";
		}
		decks[y][x] = true;
	}
}

bool GameField::isDeckOfShip(int x, int y)
{
	if (x < 0 || x >= w || y < 0 || y >= h) {
		throw "Unknow position for deck checking";
	}
	return decks[y][x];
}

int GameField::getWidth() const
{
	return w;
}

int GameField::getHeight() const
{
	return h;
}
