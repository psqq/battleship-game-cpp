#pragma once

#include <vector>

enum class Direction {
	LEFT=0, RIGHT, UP, DOWN
};

class GameField {
	int w, h;
	std::vector<std::vector<bool>> decks;
public:
	GameField(int _w, int _h);
	void addShip(int numberOfDecks, int sx, int sy, Direction dir);
	bool isDeckOfShip(int x, int y);
	int getWidth() const;
	int getHeight() const;
};
