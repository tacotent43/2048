#include <sdl/ui-modules/TextRenderer.h>

TextRenderer::TextRenderer(SDL_Renderer *renderer, std::string fontPath, float fontSize) : renderer(renderer) {
    this->font = TTF_OpenFont((std::string(SDL_GetBasePath()) + "../assets/fonts/JetBrainsMono-Thin.ttf").c_str(), fontSize);
    if (!font) {
        SDL_Log("Font load error: %d", SDL_GetError());
        // return SDL_APP_FAILURE;
    }
}

void TextRenderer::setOrigin(Origin origin) {
    this->origin = origin;
}

void TextRenderer::render(const std::string &text, float xPos, float yPos, const SDL_Color &color, const float fontSize = 0) {
    float prevFontSize = TTF_GetFontSize(this->font);

    // setting new font size
    if (fontSize != 0) {
        TTF_SetFontSize(this->font, fontSize);
    }

    // creating surface and texture
    this->surface = TTF_RenderText_Blended(
        this->font, text.c_str(), text.size(), color
    );
    this->texture = SDL_CreateTextureFromSurface(this->renderer, this->surface);

    SDL_GetTextureSize(this->texture, &this->tWidth, &this->tHeight);

    switch (this->origin) {
        case Origin::Center:
            xPos -= this->tWidth / 2.0f;
            yPos -= this->tHeight / 2.0f;
            break;
        case Origin::TopLeft:
            // doing nothing
            break;
        case Origin::TopRight:
            xPos -= this->tWidth;
            break;
        case Origin::BottomLeft:
            yPos -= this->tHeight;
            break;
        case Origin::BottomRight:
            xPos -= this->tWidth;
            yPos -= this->tHeight;
            break;
        default:
            break;
    }

    SDL_FRect dst = {
        xPos, yPos, 
        this->tWidth, this->tHeight
    };

    SDL_RenderTexture(this->renderer, this->texture, nullptr, &dst);

    // setting fontsize back to default if changed for certain text
    if (fontSize != 0) {
        TTF_SetFontSize(this->font, prevFontSize);
    }

    SDL_DestroyTexture(this->texture);
    SDL_DestroySurface(this->surface);
}