#pragma once

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

class Button {
private:
    SDL_FRect rectangle;
    SDL_Texture *texture = nullptr;
    SDL_Surface *surface = nullptr;


public:
    explicit Button(float xPos, float yPos, float buttonHeight, float buttonWidth) : rectangle(SDL_FRect{xPos, yPos, buttonWidth, buttonHeight}) {}

    void handleEvent(SDL_Event &event) {
        
    }

    void render(SDL_Renderer *renderer) {
        SDL_FRect();


    }

    ~Button() {
        SDL_DestroySurface(this->surface);
        SDL_DestroyTexture(this->texture);
    }
};