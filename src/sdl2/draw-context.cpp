#include "draw-context.h"
#include "app.h"

DrawContext::DrawContext(App* _app)
	: app(_app), renderer(app->renderer), font(app->font)
{
}

SDL_Surface* DrawContext::makeTextSurface(char* text, SDL_Color color)
{
	if (!app->font) {
		throw "No font for make text surface.";
	}
	if (!text) {
		throw "No text for make text surface.";
	}
	SDL_Surface* surfaceMessage = TTF_RenderText_Blended(app->font, text, color);
	if (!surfaceMessage) {
		throw "Surface message creation failed";
	}
	return surfaceMessage;
}

SDL_Texture* DrawContext::createTextureFromSurface(SDL_Surface* surface)
{
	if (!surface) {
		throw "No surface for making texture";
	}
	SDL_Texture* texture = SDL_CreateTextureFromSurface(app->renderer, surface);
	if (!texture) {
		throw "Texture creation failed";
	}
	return texture;
}

SDL_Rect DrawContext::drawText(char* text, SDL_Color color, int x, int y)
{
	SDL_Surface* surfaceMessage = makeTextSurface(text, color);
	SDL_Texture* Message = createTextureFromSurface(surfaceMessage);

	SDL_Rect Message_rect;
	Message_rect.x = x;
	Message_rect.y = y;
	Message_rect.w = surfaceMessage->w;
	Message_rect.h = surfaceMessage->h;


	SDL_RenderCopy(app->renderer, Message, NULL, &Message_rect);

	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(Message);

	return Message_rect;
}
