#include "grid-of-chars.h"
#include "draw-context.h"
#include <algorithm>

GridOfChars::GridOfChars(int _w, int _h, char fillCh)
	: w(_w), h(_h)
	, chars(std::vector< std::vector<char>>(h, std::vector<char>(w, fillCh)))
	, renderedChars(std::vector< std::vector<char>>(h, std::vector<char>(w, 0)))
	, surfaces(std::vector< std::vector<SDL_Surface*>>(h, std::vector<SDL_Surface*>(w, nullptr)))
	, textures(std::vector< std::vector<SDL_Texture*>>(h, std::vector<SDL_Texture*>(w, nullptr)))
{
}

GridOfChars::~GridOfChars()
{
	free();
}

void GridOfChars::setChar(int x, int y, char ch)
{
	chars[y][x] = ch;
}

void GridOfChars::free()
{
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			if (surfaces[y][x]) {
				SDL_FreeSurface(surfaces[y][x]);
				surfaces[y][x] = nullptr;
			}
			if (textures[y][x]) {
				SDL_DestroyTexture(textures[y][x]);
				textures[y][x] = nullptr;
			}
		}
	}
}

void GridOfChars::draw(DrawContext dc, int sx, int sy)
{
	makeSurfaces(dc);
	int maxW = 0, maxH = 0;
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			maxW = std::max(maxW, surfaces[y][x] ? surfaces[y][x]->w : 0);
			maxH = std::max(maxH, surfaces[y][x] ? surfaces[y][x]->h : 0);
		}
	}
	cellSize = std::max(maxW, maxH);
	viewRect.x = sx;
	viewRect.y = sy;
	viewRect.w = cellSize * w;
	viewRect.h = cellSize * h;
	SDL_SetRenderDrawColor(dc.renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	for (int y = 0; y <= h; y++) {
		SDL_RenderDrawLine(dc.renderer, sx, sy + cellSize*y, sx + cellSize * w, sy + cellSize * y);
	}
	for (int x = 0; x <= w; x++) {
		SDL_RenderDrawLine(dc.renderer, sx + cellSize * x, sy, sx + cellSize * x, sy + cellSize * h);
	}
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			SDL_Rect cellRect = { sx + cellSize * x, sy + cellSize * y, cellSize, cellSize };
			int cx = cellRect.x + cellRect.w / 2;
			int cy = cellRect.y + cellRect.h / 2;
			int sw = surfaces[y][x]->w;
			int sh = surfaces[y][x]->h;
			SDL_Rect drawRect = { cx - sw/2, cy-sh/2, sw, sh };
			SDL_RenderCopy(dc.renderer, textures[y][x], NULL, &drawRect);
		}
	}
}

SDL_Rect GridOfChars::getViewRect()
{
	return viewRect;
}

void GridOfChars::makeSurfaces(DrawContext dc)
{
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			char buf[] = { chars[y][x], '\0' };
			if (renderedChars[y][x] == chars[y][x]) {
				continue;
			}
			if (surfaces[y][x]) {
				SDL_FreeSurface(surfaces[y][x]);
				surfaces[y][x] = nullptr;
			}
			if (textures[y][x]) {
				SDL_DestroyTexture(textures[y][x]);
				textures[y][x] = nullptr;
			}
			surfaces[y][x] = dc.makeTextSurface(buf, SDL_Color{ 255, 255,255 });
			textures[y][x] = dc.createTextureFromSurface(surfaces[y][x]);
			renderedChars[y][x] = chars[y][x];
		}
	}
}
