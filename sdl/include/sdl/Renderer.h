#pragma once

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_ttf/SDL_ttf.h>

#include <vector>
#include <string>

class Renderer {
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    TTF_Font *font = nullptr;

    int WindowWidth = 0;
    int WindowHeight = 0;

    SDL_Surface *surface = nullptr;
    SDL_Texture *texture = nullptr;

public:
    explicit Renderer(
        SDL_Window *window, SDL_Renderer *renderer,
        TTF_Font *font
    ) : window(window), renderer(renderer), font(font) {
        SDL_GetWindowSizeInPixels(this->window, &WindowWidth, &WindowHeight);
    }

    void drawSettingsWindow();

    void drawTips();
};