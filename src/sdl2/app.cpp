#include "app.h"
#include "draw-context.h"
#include "grid-of-chars.h"

App::App() 
    : font(nullptr), window(nullptr), renderer(nullptr)
{}

void App::free() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
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
    GridOfChars grid(5, 5, '#');
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
        getDrawContext().drawText("Hello, World!", SDL_Color{255, 0, 255}, 0, 0);
        grid.draw(getDrawContext(), 50, 50);
        SDL_RenderPresent(renderer);
    }
}

DrawContext App::getDrawContext()
{
    return DrawContext(this);
}
