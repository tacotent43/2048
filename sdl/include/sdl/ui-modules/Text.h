#pragma once

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include <string>

class TextRenderer {
    SDL_Renderer *renderer = nullptr;


public:
    TextRenderer(SDL_Renderer *renderer) : renderer(renderer) {}

    void render(std::string Text, SDL_FRect dst);
};