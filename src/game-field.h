#pragma once

#include <vector>

enum class Direction {
	LEFT=0, RIGHT, UP, DOWN
};

class GameField {
	int fieldSize;
	std::vector<std::vector<bool>> decks;
public:
	GameField(int _fieldSize=10);
	void addShip(int numberOfDecks, int sx, int sy, Direction dir);
	bool isDeckOfShip(int x, int y);
};
