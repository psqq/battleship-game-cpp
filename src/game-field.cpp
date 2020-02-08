#include "game-field.h"
#include <cstring>

GameField::GameField()
{
	for (int y = 0; y < 10; y++) {
		strcpy(field[y], "..........");
	}
}

void GameField::addShip(int numberOfDecks, int sx, int sy, Direction dir)
{
	int dx[] = {-1, 1, 0, 0};
	int dy[] = {0, 0, -1, 1};
	for (int i = 0; i < numberOfDecks; i++) {
		field[sy + dy[(int)dir] * i][sx + dx[(int)dir] * i] = '#';
	}
}

bool GameField::isDeckOfShip(int x, int y)
{
	return field[y][x] == '#';
}
