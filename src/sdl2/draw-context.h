
#pragma once

#include "app.h"

class DrawContext {
	App* app;
public:
	SDL_Renderer* renderer;
	TTF_Font* font;
	DrawContext(App* _app);
	SDL_Surface* makeTextSurface(char* text, SDL_Color color);
	SDL_Texture* createTextureFromSurface(SDL_Surface* surface);
	SDL_Rect drawText(char* text, SDL_Color color, int x, int y);
};
