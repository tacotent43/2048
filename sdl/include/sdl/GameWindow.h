#pragma once

#include <vector>
#include <SDL3/SDL.h>

class GameWindow {
    int WindowWidth = 640;
    int WindowHeight = 640;

    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;

    void quit();

    // edit signature here
    void drawTile(int number, int w, int h, int x, int y);
    void drawGrid(int gridSize);

public:
    GameWindow() {}
    explicit GameWindow(int width) : WindowWidth(width), WindowHeight(width) {}

    SDL_AppResult initialize();
    SDL_AppResult event(SDL_Event *event);
    SDL_AppResult iterate();

    ~GameWindow() {
        quit();
    }
};