#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include "../game.h"
#include "../game-field.h"

class DrawContext;


class App {
	SDL_Renderer* renderer;
	TTF_Font* font;
	SDL_Window* window;
	Game game;
public:
	friend DrawContext;
	App();
	void clear();
	void init();
	void run();
	DrawContext getDrawContext();
};
