#pragma once

#include <vector>
#include <string>

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_ttf/SDL_ttf.h>

#include <game/field.h>
#include <sdl/FPosition.hpp>
#include <sdl/TextRenderer.h>

class GameWindow {
    size_t gameFieldSize = 5;
    std::string fontString = "JetBrainsMono-Thin.ttf";
    TextRenderer textRenderer;
    float fontSize = 0;

    float WindowWidth = 800;
    float WindowHeight = 800;

    const float borderOffset = 0.125f;
    const float borderLength = 0.75f;
    float lineOffset = 0.0f;
    int cellSize_px = 0.0f;

    bool openSettings = false;

    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;

    void quit();

    void drawSettingsWindow();

    void drawTips();
    
    void drawScore();
    void drawTile(unsigned long long int number, int w, int h);
    void drawField(const std::vector<Line> &field);
    void drawGrid();
    
    Field field{4};
    void initializeField(size_t fieldSize);
    
public:
    GameWindow() {}
    explicit GameWindow(int screenWidth) : WindowWidth(screenWidth), WindowHeight(screenWidth) {}
    
    bool showTips = false;

    SDL_AppResult initialize();
    SDL_AppResult event(SDL_Event *event);
    SDL_AppResult iterate();

    void makeMove(Direction direction);

    ~GameWindow() {
        quit();
    }
};