#include "app.h"

App::App() 
    : font(nullptr), window(nullptr), renderer(nullptr)
{}

void App::clear() {
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void App::init() {
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    //font = TTF_OpenFont("assets/Open_Sans/OpenSans-Regular.ttf", 24);
    font = TTF_OpenFont("assets/Source_Code_Pro/SourceCodePro-Regular.ttf", 24);

    window = SDL_CreateWindow(
        "Battleship game",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        640,
        480,
        SDL_WINDOW_RESIZABLE
    );

    if (!window) {
        throw "Window creation failed";
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);

    if (!renderer) {
        throw "Renderer creation failed";
    }
}

void App::run() {
    while (true)
    {
        SDL_Event event;
        if (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                break;
            }
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);
        drawText("Hello, World!", SDL_Color{255, 0, 255}, 0, 0);
        SDL_RenderPresent(renderer);
    }
}

SDL_Surface* App::makeTextSurface(char* text, SDL_Color color) {
    if (!font) {
        throw "No font for make text surface.";
    }
    SDL_Surface* surfaceMessage = TTF_RenderText_Blended(font, text, color);
    if (!surfaceMessage) {
        throw "Surface message creation failed";
    }
    return surfaceMessage;
}

SDL_Rect App::drawText(char* text, SDL_Color color, int x, int y) {
    SDL_Surface* surfaceMessage = makeTextSurface(text, color);
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
