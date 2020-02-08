#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include "../game.h"
#include "../game-field.h"

class App {
	SDL_Renderer* renderer;
	TTF_Font* font;
	SDL_Window* window;
	Game game;
public:
	App();
	void clear();
	void init();
	void run();
	SDL_Surface* makeTextSurface(char* text, SDL_Color color);
	SDL_Rect drawText(char* text, SDL_Color color, int x, int y);
};
