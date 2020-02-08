#include "game.h"

Game::Game()
	: playerField(), aiField()
{
}

void Game::startNewGame()
{
	playerField = GameField();
	aiField = GameField();
}
