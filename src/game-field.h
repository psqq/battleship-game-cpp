#pragma once

enum class Direction {
	LEFT=0, RIGHT, UP, DOWN
};

class GameField {
public:
	char field[12][12];
	GameField();
	void addShip(int numberOfDecks, int sx, int sy, Direction dir);
	bool isDeckOfShip(int x, int y);
};
