#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include "../game.h"
#include "../game-field.h"
#include "screens/screen.h"
#include "screens/field-maker-screen.h"

class DrawContext;


class App {
	friend DrawContext;
	SDL_Renderer* renderer;
	TTF_Font* font;
	SDL_Window* window;
	Screen* screen;
public:
	Game game;
	FieldMakerScreen fieldMakerScreen;
	App();
	void free();
	void init();
	void run();
	void setScreen(Screen* screen);
	DrawContext getDrawContext();
};
