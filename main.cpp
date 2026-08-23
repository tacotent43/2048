#include <iostream>
#include <stdexcept>
#include <sdl/GameWindow.h>

int main() {
    GameWindow window;
    
    SDL_AppResult initialized = window.initialize();
    if (initialized == SDL_APP_FAILURE) {
        throw std::runtime_error("Could not initialize window");
    }

    bool running = true;

    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            SDL_AppResult eventResult = window.event(&event);
            if (eventResult == SDL_APP_SUCCESS) {
                running = false;
            }
        }

        const bool* keyState = SDL_GetKeyboardState(NULL);

        window.showTips = keyState[SDL_SCANCODE_I];

        window.iterate();
    }

    return 0;
}