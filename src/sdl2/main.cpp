#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include "../game.h"
#include "../game-field.h"

Game game;

SDL_Renderer* renderer;
TTF_Font* font;

SDL_Rect drawText(char *text, int x, int y) {
    if (!font) {
        std::cout << "No font!" << std::endl;
        return SDL_Rect{ -1, -1, -1, -1 };
    }

    SDL_Color White = { 255, 255, 255 };
    SDL_Surface* surfaceMessage = TTF_RenderText_Blended(font, text, White);
    SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

    SDL_Rect Message_rect;
    Message_rect.x = x;
    Message_rect.y = y;
    Message_rect.w = surfaceMessage->w;
    Message_rect.h = surfaceMessage->h;

    SDL_RenderCopy(renderer, Message, NULL, &Message_rect);

    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(Message);

    return Message_rect;
}

void showGameField(GameField f) {
    int x = 50, y = 50;
    for (int i = 0; i < 10; i++) {
        SDL_Rect r = drawText(f.field[i], x, y);
        y += r.h;
    }
}

int main(int argc, char* argv[])
{
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    
    //font = TTF_OpenFont("assets/Open_Sans/OpenSans-Regular.ttf", 24);
    font = TTF_OpenFont("assets/Source_Code_Pro/SourceCodePro-Regular.ttf", 24);

    SDL_Window* window = SDL_CreateWindow(
        "Battleship game",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        640,
        480,
        0
    );

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

    game.playerField.addShip(3, 2, 2, DOWN);

    while (true)
    {
        // Get the next event
        SDL_Event event;
        if (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                // Break out of the loop on quit
                break;
            }
        }
        SDL_RenderClear(renderer);
        drawText("Hello, World!", 0, 0);
        showGameField(game.playerField);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
