#include "app.h"
#include "draw-context.h"
#include "grid-of-chars.h"

App::App() 
    : font(nullptr)
    , window(nullptr)
    , renderer(nullptr)
    , screen(nullptr)
    , game()
    , fieldMakerScreen(this, game.playerField)
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

    setScreen(&fieldMakerScreen);
}

void App::run() {
    while (true)
    {
        SDL_Event event;
        if (SDL_PollEvent(&event))
        {
            screen->onEvent(event);
            if (event.type == SDL_QUIT)
            {
                break;
            }
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);
        screen->update();
        screen->draw();
        SDL_RenderPresent(renderer);
    }
}

void App::setScreen(Screen* _screen)
{
    screen = _screen;
}

DrawContext App::getDrawContext()
{
    return DrawContext(this);
}
