#pragma once

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_ttf/SDL_ttf.h>

#include <sdl/ui-modules/Origin.hpp>

#include <string>

class TextRenderer {
    SDL_Renderer *renderer = nullptr;
    Origin origin = Origin::TopLeft;

    TTF_Font *font = nullptr;

    SDL_Surface *surface = nullptr;
    SDL_Texture *texture = nullptr;

    float xOffset = 0;
    float yOffset = 0;

public:
    TextRenderer(SDL_Renderer *renderer, std::string fontPath, float fontSize);

    void setOrigin(Origin origin);

    void render(std::string text, SDL_FRect dst, float size);

    ~TextRenderer() = default;
};