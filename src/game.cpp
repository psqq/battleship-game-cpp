#include "game.h"

Game::Game()
	: playerField(10, 10)
	, aiField(10, 10)
{
}

void Game::startNewGame()
{
	playerField = GameField(10, 10);
	aiField = GameField(10, 10);
}
