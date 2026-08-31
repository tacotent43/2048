#include <sdl/TextRenderer.h>

TextRenderer::TextRenderer(SDL_Renderer *renderer, const std::string &fontPath, const std::string &fontName, float fontSize) : renderer(renderer) {
    this->font = TTF_OpenFont((std::string(SDL_GetBasePath()) + fontPath + fontName).c_str(), fontSize);
    std::cout << std::string(SDL_GetBasePath()) << fontPath << fontName << '\n';
    if (!font) {
        throw std::runtime_error("Font load error");
        // std::cout << "Font load error: %s" << SDL_GetError() << '\n';
        // SDL_Log("Font load error: %s", SDL_GetError());
        // return SDL_APP_FAILURE;
    }
}

void TextRenderer::setOrigin(Origin origin) {
    this->origin = origin;
}

void TextRenderer::render(const std::string &text, float xPos, float yPos, const SDL_Color &color, const float fontSize) {
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

        case Origin::TopMiddle:
            xPos -= this->tWidth / 2;
            break;

        case Origin::BottomMiddle:
            xPos -= this->tWidth / 2;
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

float TextRenderer::getRenderedTextureWidth() const {
    return this->tWidth;
}

float TextRenderer::getRenderedTextureHeight() const {
    return this->tHeight;
}

TextRenderer::~TextRenderer() {
    TTF_CloseFont(this->font);
}