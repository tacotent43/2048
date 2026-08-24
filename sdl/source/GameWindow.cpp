#include <sdl/GameWindow.h>

// private
void GameWindow::quit() {
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
    TTF_CloseFont(this->font);
    TTF_Quit();
    SDL_Quit();
}

void GameWindow::drawTips() {
    std::vector<std::string> logo = {
        "   ___   ____  __ __  ____                              ", 
        "  |__ \\ / __ \\/ // / ( __ )   ____ _____ _____ ___  ___ ",
        "  __/ // / / / // /_/ __  |  / __ `/ __ `/ __ `__ \\/ _ \\",
        " / __// /_/ /__  __/ /_/ /  / /_/ / /_/ / / / / / /  __/", 
        "/____/\\____/  /_/  \\____/   \\__, /\\__,_/_/ /_/ /_/\\___/ ",
        "                           /____/                       ",
    };

    std::vector<std::string> tips = {
        "---------------------------------",
        "[W] | [UpArrow]     - move up    ",
        "[S] | [DownArrow]   - move down  ", 
        "[A] | [LeftArrow]   - move left  ", 
        "[D] | [RightArrow]  - move right ", 
        "[R]                 - reset field",
        "[I]                 - info       ",
        "[P] | [ESC]         - preferences",
        "---------------------------------"
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

void GameWindow::drawScore() {
    std::string scoreText = "score: ";
    std::string score = std::to_string(this->field.getScore());

    float previousFontSize = TTF_GetFontSize(this->font);
    TTF_SetFontSize(this->font, 24);

    float xOffset = 0.05 * this->WindowWidth;
    float yOffset = 0.05 * this->WindowHeight;

    float tWidthText = 0;
    float tHeightText = 0;

    SDL_Surface *surface = TTF_RenderText_Blended(
        this->font, scoreText.c_str(), scoreText.size(), SDL_Color({255, 255, 255})
    );
    SDL_Texture *texture = SDL_CreateTextureFromSurface(this->renderer, surface);

    SDL_GetTextureSize(texture, &tWidthText, &tHeightText);
    SDL_FRect dst = {xOffset, yOffset, tWidthText, tHeightText};

    SDL_RenderTexture(this->renderer, texture, NULL, &dst);

    SDL_DestroyTexture(texture);
    SDL_DestroySurface(surface);

    float tWidthScore = 0;
    float tHeightScore = 0;

    surface = TTF_RenderText_Blended(
        this->font, score.c_str(), score.size(), SDL_Color({255, 123, 23})
    );
    texture = SDL_CreateTextureFromSurface(this->renderer, surface);

    SDL_GetTextureSize(texture, &tWidthScore, &tHeightScore);
    dst = {xOffset + tWidthText, yOffset, tWidthScore, tHeightScore};

    SDL_RenderTexture(this->renderer, texture, NULL, &dst);

    SDL_DestroyTexture(texture);
    SDL_DestroySurface(surface);

    TTF_SetFontSize(this->font, previousFontSize);
}

void GameWindow::drawTile(unsigned long long int number, int x, int y) {
    if (number != 0) {
        std::string text = std::to_string(number);

        float tWidth = 0; 
        float tHeight = 0;

        float prevFontSize = this->fontSize;
        TTF_SetFontSize(this->font, this->fontSize * (1 - 0.15f * text.size()));

        SDL_Surface *surface = TTF_RenderText_Blended(
            this->font, text.c_str(), text.size(), SDL_Color({225, 225, 225})
        );
        SDL_Texture *texture = SDL_CreateTextureFromSurface(this->renderer, surface);

        SDL_GetTextureSize(texture, &tWidth, &tHeight);
        SDL_FRect dst = {static_cast<float>(x) - tWidth / 2.0f, static_cast<float>(y) - tHeight / 2.0f, tWidth, tHeight};

        SDL_RenderTexture(this->renderer, texture, NULL, &dst);

        this->fontSize = prevFontSize;

        SDL_DestroyTexture(texture);
        SDL_DestroySurface(surface);
    }
}

void GameWindow::drawField(const std::vector<Line> &field) {
    std::vector<std::vector<FPosition>> centerPoints {
        static_cast<size_t>(this->gameFieldSize), 
        std::vector<FPosition>{static_cast<size_t>(this->gameFieldSize)}
    };

    for (size_t i = 0; i < this->gameFieldSize; ++i) {
        for (size_t j = 0; j < this->gameFieldSize; ++j) {
            centerPoints[i - 0][j - 0].x = this->WindowWidth * (this->borderOffset + (this->lineOffset / 2.f) + this->lineOffset * j);
            centerPoints[i - 0][j - 0].y = this->WindowHeight * (this->borderOffset + (this->lineOffset / 2.f) + this->lineOffset * i);
        }
    }

    SDL_SetRenderDrawColor(
        this->renderer,
        255, 255, 255, 255
    );

    for (size_t i = 0; i < field.size(); ++i) {
        for (size_t j = 0; j < field[i].size(); ++j) {
            this->drawTile(field[i][j], centerPoints[i][j].x, centerPoints[i][j].y);
        }
    }
}

void GameWindow::drawGrid() {
    SDL_FRect outline;

    outline.x = outline.y = this->WindowWidth * borderOffset;
    outline.w = outline.h = this->WindowWidth * borderLength;

    SDL_SetRenderDrawColor(
        this->renderer,
        255, 255, 255, 255
    );

    SDL_RenderRect(this->renderer, &outline);

    for (size_t i = 0; i < this->gameFieldSize; ++i) {
        SDL_RenderLine(
            this->renderer, 
            this->WindowWidth * (borderOffset + lineOffset * i),
            this->WindowHeight * borderOffset,
            this->WindowWidth * (borderOffset + lineOffset * i), 
            this->WindowHeight * (borderOffset + borderLength)
        );
    }

    for (size_t i = 0; i < this->gameFieldSize; ++i) {
        SDL_RenderLine(
            this->renderer, 
            this->WindowHeight * borderOffset,
            this->WindowWidth * (borderOffset + lineOffset * i),
            this->WindowHeight * (borderOffset + borderLength), 
            this->WindowWidth * (borderOffset + lineOffset * i) 
        );
    }
}

void GameWindow::initializeField(size_t fieldSize) {
    this->cellSize_px = (this->WindowWidth - this->borderOffset * 2) / this->gameFieldSize;
    this->fontSize = static_cast<float>(cellSize_px) * 0.7f;

    this->field = Field(this->gameFieldSize);
    field.spawnTile(field.getEmptyTiles());
    field.spawnTile(field.getEmptyTiles());
}

// public
SDL_AppResult GameWindow::initialize() {
    SDL_SetAppMetadata("2048 game", "0.1", "");

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!SDL_CreateWindowAndRenderer("2048-main-window", this->WindowWidth, this->WindowHeight, SDL_WINDOW_RESIZABLE, &window, &renderer)) {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!TTF_Init()) {
        SDL_Log("Couldn't initialize TTF: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    this->initializeField(this->gameFieldSize);

    const char* currentPath = SDL_GetBasePath();
    this->font = TTF_OpenFont((std::string(currentPath) + "../fonts/JetBrainsMono-Thin.ttf").c_str(), this->fontSize);
    if (!font) {
        SDL_Log("Font load error: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    this->lineOffset = this->borderLength / this->gameFieldSize;

    SDL_SetRenderLogicalPresentation(
        this->renderer,
        this->WindowWidth, this->WindowHeight,
        SDL_LOGICAL_PRESENTATION_LETTERBOX
    );

    return SDL_APP_CONTINUE;
}

SDL_AppResult GameWindow::event(SDL_Event *event) {
    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;
    }

    switch (event->type) {
        case SDL_EVENT_KEY_DOWN:
            switch (event->key.key) {
                case SDLK_W:
                    this->makeMove(Direction::up);
                    break;
                case SDLK_S:
                    this->makeMove(Direction::down);
                    break;
                case SDLK_A:
                    this->makeMove(Direction::left);
                    break;
                case SDLK_D:
                    this->makeMove(Direction::right);
                    break;

                case SDLK_UP:
                    this->makeMove(Direction::up);
                    break;
                case SDLK_DOWN:
                    this->makeMove(Direction::down);
                    break;
                case SDLK_LEFT:
                    this->makeMove(Direction::left);
                    break;
                case SDLK_RIGHT:
                    this->makeMove(Direction::right);
                    break;
                
                case SDLK_R:
                    this->initializeField(this->gameFieldSize);
            }
            break;
    }

    return SDL_APP_CONTINUE;
}

SDL_AppResult GameWindow::iterate() {
    SDL_RenderClear(this->renderer);

    SDL_SetRenderDrawColor(
        this->renderer,
        0, 0, 0, 255
    );

    if (this->showTips) {
        this->drawTips();
    } else {
        this->drawScore();
        this->drawGrid();
        this->drawField(this->field.getField());
    }

    SDL_SetRenderDrawColor(
        this->renderer,
        0, 0, 0, 255
    );

    SDL_RenderPresent(this->renderer);
    return SDL_APP_CONTINUE;
}

void GameWindow::makeMove(Direction direction) {
    field.move(direction);
    field.spawnTile(field.getEmptyTiles());
    field.updateScore();
}