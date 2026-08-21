#pragma once

#include <vector>
#include <string>

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_ttf/SDL_ttf.h>

#include <game/field.h>
#include <sdl/FPosition.hpp>

class GameWindow {
    int gameFieldSize = 4;
    std::string fontString = "Consolas.ttf";
    TTF_Font *font = nullptr;

    int WindowWidth = 640;
    int WindowHeight = 640;

    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;

    void quit();

    void drawScore();
    void drawTile(unsigned long long int number, int w, int h);
    void drawField(const std::vector<Line> &field);
    void drawGrid();

    Field field{4};

public:
    GameWindow() {}
    explicit GameWindow(int screenWidth) : WindowWidth(screenWidth), WindowHeight(screenWidth) {}

    SDL_AppResult initialize();
    SDL_AppResult event(SDL_Event *event);
    SDL_AppResult iterate();

    void makeMove(Direction direction);

    ~GameWindow() {
        quit();
    }
};