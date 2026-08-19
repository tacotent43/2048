#include <sdl/GameWindow.h>

// private
void GameWindow::quit() {
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
    SDL_Quit();
}

void GameWindow::drawTile(int number, int w, int h, int x, int y) {
    // something like point with dimensions. 
    // here we need x, y, width and height.
    // also edit signature here

    
}

void GameWindow::drawGrid(int gridSize) {
    // std::vector<SDL_FRect> outline{gridSize};
    SDL_FRect outline;

    outline.x = outline.y = this->WindowWidth * 0.125f;
    outline.w = outline.h = this->WindowWidth * 0.75f;

    SDL_SetRenderDrawColor(
        this->renderer,
        255, 255, 255, 255
    );
    SDL_RenderRect(this->renderer, &outline);

    
}

// public
SDL_AppResult GameWindow::initialize() {
    SDL_SetAppMetadata("2048 game", "0.1", "");

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    // If adding ability to resize the window, add window_flags SDL_WINDOW_RESIZABLE
    // if (!SDL_CreateWindowAndRenderer("2048-main-window", this->WindowWidth, this->WindowHeight, SDL_WINDOW_BORDERLESS, &window, &renderer)) {
    if (!SDL_CreateWindowAndRenderer("2048-main-window", this->WindowWidth, this->WindowHeight, SDL_WINDOW_RESIZABLE, &window, &renderer)) {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    SDL_SetRenderLogicalPresentation(
        this->renderer,
        this->WindowWidth, this->WindowHeight,
        SDL_LOGICAL_PRESENTATION_LETTERBOX
    );

    return SDL_APP_CONTINUE;
}

SDL_AppResult GameWindow::event(SDL_Event *event) {
    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;
    }
    return SDL_APP_CONTINUE;
}

SDL_AppResult GameWindow::iterate() {
    SDL_RenderClear(this->renderer);

    SDL_SetRenderDrawColor(
        this->renderer,
        0, 0, 0, 255
    );
    
    this->drawGrid(4);
    
    SDL_SetRenderDrawColor(
        this->renderer,
        0, 0, 0, 255
    );

    SDL_RenderPresent(this->renderer);
    return SDL_APP_CONTINUE;
}

