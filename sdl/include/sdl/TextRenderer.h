#pragma once

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_ttf/SDL_ttf.h>

#include <sdl/Origin.hpp>

#include <iostream>
#include <string>

class TextRenderer {
    SDL_Renderer *renderer = nullptr;
    Origin origin = Origin::TopLeft;

    TTF_Font *font = nullptr;

    // shared surface and texture
    SDL_Surface *surface = nullptr;
    SDL_Texture *texture = nullptr;

    // shared dst rectangle
    SDL_FRect dst = {};

    // shared offset points for origin
    float xOffset = 0;
    float yOffset = 0;

    // shared texture height and width
    float tWidth = 0;
    float tHeight = 0;

public:
    TextRenderer(SDL_Renderer *renderer, const std::string &fontPath, const std::string &fontName, float fontSize);

    TextRenderer(const TextRenderer&) = delete;
    TextRenderer& operator=(const TextRenderer&) = delete;

    TextRenderer(TextRenderer&& other) noexcept
        : renderer(other.renderer),
        font(other.font),
        origin(other.origin),
        surface(other.surface),
        texture(other.texture),
        tWidth(other.tWidth),
        tHeight(other.tHeight)
    {
        other.font = nullptr;
        other.surface = nullptr;
        other.texture = nullptr;
    }

    TextRenderer& operator=(TextRenderer &&other) noexcept;

    void setOrigin(Origin origin);

    void render(const std::string &text, float xPos, float yPos, const SDL_Color &color, const float fontSize = 0);

    float getRenderedTextureWidth() const;
    float getRenderedTextureHeight() const;

    ~TextRenderer();
};