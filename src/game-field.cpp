#include "game-field.h"
#include <cstring>

GameField::GameField()
{
	for (int i = 0; i < 10; i++) {
		strcpy(field[i], "..........");
	}
}

void GameField::addShip(int numberOfDecks, int sx, int sy, Direction dir)
{
	int dx[] = {-1, 1, 0, 0};
	int dy[] = {0, 0, -1, 1};
	for (int i = 0; i < numberOfDecks; i++) {
		field[sx + dx[dir] * i][sy + dy[dir] * i] = '#';
	}
}

void GameField::isDeckOfShip(int x, int y)
{
	return field[x][y] == '#';
}
