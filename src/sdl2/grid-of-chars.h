
#pragma once

#include <vector>
#include "app.h"
#include "draw-context.h"

class GridOfChars {
	int w, h;
	int cellSize = 0;
	std::vector<std::vector<char>> chars;
	std::vector<std::vector<char>> renderedChars;
	std::vector<std::vector<SDL_Surface*>> surfaces;
	std::vector<std::vector<SDL_Texture*>> textures;
	void makeSurfaces(DrawContext dc);
public:
	GridOfChars(int w, int h, char fillCh = ' ');
	~GridOfChars();
	void setChar(int x, int y, char ch);
	void free();
	void draw(DrawContext dc, int x, int y);
};
