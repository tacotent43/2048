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

void TextRenderer::render(std::string text, float xPos, float yPos, SDL_Color color, float fontSize = 0) {
    if (fontSize != 0) {
        float prevFontSize = TTF_GetFontSize(this->font);
        TTF_SetFontSize(this->font, fontSize);
    }

    this->surface = TTF_RenderText_Blended(
        this->font, text.c_str(), text.size(), color
    );
    this->texture = SDL_CreateTextureFromSurface(this->renderer, this->surface);

    SDL_GetTextureSize(this->texture, &this->tWidth, &this->tHeight);
    SDL_FRect dst = {
        xPos, yPos, 
        this->tWidth, this->tHeight
    };

    switch (this->origin) {
        case Origin::Center:
            this->dst = {
                xPos - this->tWidth / 2.0f,
                yPos - this->tHeight / 2.0f,
                this->tWidth, this->tHeight
            };
            break;
        case Origin::TopLeft:
            this->dst = {
                xPos, 
                yPos, 
                this->tWidth, this->tHeight
            };
            break;
        case Origin::TopRight:
            this->dst = {
                xPos - this->tWidth,
                yPos,
                this->tWidth, this->tHeight
            };
            break;
        case Origin::BottomLeft:
            this->dst = {
                xPos,
                yPos - this->tHeight,
                this->tWidth, this->tHeight
            };
            break;
        case Origin::BottomRight:
            this->dst = {
                xPos - this->tWidth,
                yPos - this->tHeight,
                this->tWidth, this->tHeight
            };
            break;
        default:
            break;
    }

    SDL_RenderTexture(this->renderer, this->texture, nullptr, &dst);

    SDL_DestroyTexture(this->texture);
    SDL_DestroySurface(this->surface);
}