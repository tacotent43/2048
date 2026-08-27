#include <sdl/ui-modules/TextRenderer.h>

TextRenderer::TextRenderer(SDL_Renderer *renderer, std::string fontPath, float fontSize) : renderer(renderer) {
    this->font = TTF_OpenFont((std::string(SDL_GetBasePath()) + "../assets/fonts/JetBrainsMono-Thin.ttf").c_str(), fontSize);
}

void TextRenderer::setOrigin(Origin origin) {
    this->origin = origin;
}

void TextRenderer::render(std::string text, SDL_FRect dst, float size) {

    switch (this->origin) {
        case Origin::Center:

        case Origin::TopLeft:

        case Origin::TopRight:

        case Origin::BottomLeft:

        case Origin::BottomRight:

    }
}