#include <sdl/Renderer.h>

void Renderer::drawSettingsWindow() {
    float previousFontSize = TTF_GetFontSize(this->font);
    TTF_SetFontSize(this->font, 0.1f * this->WindowWidth);

    float tWidth = 0;
    float tHeight = 0;

    SDL_Surface *surface = nullptr;
    SDL_Texture *texture = nullptr;

    surface = TTF_RenderText_Blended(this->font, "settings", 8, {255, 255, 255});
    texture = SDL_CreateTextureFromSurface(this->renderer, surface);

    SDL_GetTextureSize(texture, &tWidth, &tHeight);
    SDL_FRect dst = {
        (static_cast<float>(this->WindowWidth) - tWidth) / 2.0f,
        tHeight / 2.0f,
        tWidth, tHeight
    };

    SDL_RenderTexture(
        this->renderer, texture, 
        nullptr, &dst
    );



    SDL_DestroySurface(surface);
    SDL_DestroyTexture(texture);

    TTF_SetFontSize(this->font, previousFontSize);
}

void Renderer::drawTips() {
    const std::vector<std::string> logo = {
        "   ___   ____  __ __  ____  ", 
        "  |__ \\ / __ \\/ // / ( __ ) ",
        "  __/ // / / / // /_/ __  | ",
        " / __// /_/ /__  __/ /_/ /  ", 
        "/____/\\____/  /_/  \\____/   ",
    };

    const std::vector<std::string> tips = {
        "+-----------------------------------+",
        "| [W] | [UpArrow]     - move up     |",
        "| [S] | [DownArrow]   - move down   |",
        "| [A] | [LeftArrow]   - move left   |",
        "| [D] | [RightArrow]  - move right  |",
        "| [R]                 - reset field |",
        "| [I]                 - info        |",
        "| [P] | [ESC]         - preferences |",
        "+-----------------------------------+"
    };

    float previousFontSize = TTF_GetFontSize(this->font);
    TTF_SetFontSize(this->font, 0.03f * this->WindowHeight);

    float tWidth = 0;
    float tHeight = 0;

    float linePositionOffset = 0;

    SDL_Surface *surface = nullptr;
    SDL_Texture *texture = nullptr;
    SDL_FRect dst;

    for (const std::string &line : logo) {
        surface = TTF_RenderText_Blended(
            this->font, line.c_str(), line.size(), SDL_Color({255, 0, 0})
        );
        texture = SDL_CreateTextureFromSurface(this->renderer, surface);

        SDL_GetTextureSize(texture, &tWidth, &tHeight);
        dst = {
            (static_cast<float>(this->WindowWidth) - tWidth) / 2.0f,
            linePositionOffset,
            tWidth, tHeight
        };

        linePositionOffset += tHeight;

        SDL_RenderTexture(this->renderer, texture, NULL, &dst);

        SDL_DestroyTexture(texture);
        SDL_DestroySurface(surface);
    }
    
    linePositionOffset += tHeight;

    // game info
    std::string caption = "game information";
    surface = TTF_RenderText_Blended(
        this->font, caption.c_str(), caption.size(), SDL_Color({255, 255, 255})
    );
    texture = SDL_CreateTextureFromSurface(this->renderer, surface);

    SDL_GetTextureSize(texture, &tWidth, &tHeight);
    dst = {
        (static_cast<float>(this->WindowWidth) - tWidth) / 2.0f,
        linePositionOffset,
        tWidth, tHeight
    };

    SDL_RenderTexture(this->renderer, texture, nullptr, &dst);
    
    SDL_DestroyTexture(texture);
    SDL_DestroySurface(surface);

    linePositionOffset += tHeight * 2;

    for (const std::string &line : tips) {
        surface = TTF_RenderText_Blended(
            this->font, line.c_str(), line.size(), SDL_Color({255, 255, 255})
        );
        texture = SDL_CreateTextureFromSurface(this->renderer, surface);

        SDL_GetTextureSize(texture, &tWidth, &tHeight);
        dst = {
            (static_cast<float>(this->WindowWidth) - tWidth) / 2.0f,
            linePositionOffset,
            tWidth, tHeight
        };
        
        SDL_RenderTexture(this->renderer, texture, nullptr, &dst);

        linePositionOffset += tHeight;

        SDL_DestroyTexture(texture);
        SDL_DestroySurface(surface);
    }
    
    TTF_SetFontSize(this->font, previousFontSize);
}

