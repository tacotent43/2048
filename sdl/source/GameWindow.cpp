#include <sdl/GameWindow.h>

// private
void GameWindow::quit() {
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
    TTF_Quit();
    SDL_Quit();
}

// void GameWindow::drawSettingsWindow() {
//     float previousFontSize = TTF_GetFontSize(this->font);
//     TTF_SetFontSize(this->font, 0.1f * this->WindowWidth);

//     float tWidth = 0;
//     float tHeight = 0;

//     SDL_Surface *surface = nullptr;
//     SDL_Texture *texture = nullptr;

//     surface = TTF_RenderText_Blended(this->font, "settings", 8, {255, 255, 255});
//     texture = SDL_CreateTextureFromSurface(this->renderer, surface);

//     SDL_GetTextureSize(texture, &tWidth, &tHeight);
//     SDL_FRect dst = {
//         (static_cast<float>(this->WindowWidth) - tWidth) / 2.0f,
//         tHeight / 2.0f,
//         tWidth, tHeight
//     };

//     SDL_RenderTexture(
//         this->renderer, texture, 
//         nullptr, &dst
//     );

//     SDL_DestroySurface(surface);
//     SDL_DestroyTexture(texture);

//     TTF_SetFontSize(this->font, previousFontSize);
// }

void GameWindow::drawTips() {
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

    float menuTextSize = 0.03f * this->WindowHeight;
    float linePositionOffset = 0;

    this->textRenderer.setOrigin(Origin::TopMiddle);

    for (const std::string &line : logo) {
        this->textRenderer.render(
            line, 
            this->WindowWidth / 2.0f, linePositionOffset, 
            SDL_Color{255, 0, 0}, 
            menuTextSize
        );

        linePositionOffset += this->textRenderer.getRenderedTextureHeight();
    }
    
    linePositionOffset += this->textRenderer.getRenderedTextureHeight();

    // game info
    std::string caption = "game information";
    this->textRenderer.render(
        "game info",
        this->WindowWidth / 2.0f, linePositionOffset,
        SDL_Color{0, 255, 255},
        menuTextSize
    );

    linePositionOffset += this->textRenderer.getRenderedTextureHeight() * 2;

    for (const std::string &line : tips) {
        this->textRenderer.render(
            line, 
            this->WindowWidth / 2.0f, linePositionOffset,
            SDL_Color{255, 255, 255},
            menuTextSize
        );
        linePositionOffset += this->textRenderer.getRenderedTextureHeight();
    }
}

void GameWindow::drawScore() {
    // float xOffset = 0.05 * this->WindowWidth;
    // float yOffset = 0.05 * this->WindowHeight;

    this->textRenderer.render(
        "score: ", 
        0.05 * this->WindowWidth,
        0.05 * this->WindowHeight, 
        SDL_Color{255, 255, 255}
    );

    this->textRenderer.render(
        std::to_string(this->field.getScore()),
        0.05 * this->WindowWidth + this->textRenderer.getRenderedTextureWidth(), 
        0.05 * this->WindowHeight,
        SDL_Color{255, 123, 23}
    );
}

void GameWindow::drawTile(unsigned long long int number, int x, int y) {
    if (number != 0) {
        this->textRenderer.render(
            std::to_string(number),
            static_cast<float>(x), 
            static_cast<float>(y),
            SDL_Color{255, 255, 255}
        );
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

    if (!SDL_CreateWindowAndRenderer("2048", this->WindowWidth, this->WindowHeight, SDL_WINDOW_RESIZABLE, &window, &renderer)) {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!TTF_Init()) {
        SDL_Log("Couldn't initialize TTF: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    this->initializeField(this->gameFieldSize);

    TextRenderer(this->renderer, "../assets/fonts/", "JetBrainsMono-Thin.ttf", this->fontSize);

    std::string currentPath = SDL_GetBasePath();

    SDL_Surface *icon = SDL_LoadPNG((std::string(currentPath) + "../assets/logo.png").c_str());
    if (!SDL_SetWindowIcon(this->window, icon)) {
        SDL_Log("Unable to set icon at %s", (std::string(currentPath) + "../assets/logo.png").c_str());
    }
    SDL_DestroySurface(icon);

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
                case SDLK_UP:
                    this->makeMove(Direction::up);
                    break;
                case SDLK_S:
                case SDLK_DOWN:
                    this->makeMove(Direction::down);
                    break;
                case SDLK_A:
                case SDLK_LEFT:
                    this->makeMove(Direction::left);
                    break;
                case SDLK_D:
                case SDLK_RIGHT:
                    this->makeMove(Direction::right);
                    break;

                case SDLK_R:
                    this->initializeField(this->gameFieldSize);
                    break;
                
                case SDLK_P:
                case SDLK_ESCAPE:
                    this->openSettings = !this->openSettings;
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

    if (this->openSettings) {
        // this->drawSettingsWindow();
    } else if (this->showTips) {
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
    if (field.move(direction)) {
        field.spawnTile(field.getEmptyTiles());
    }
    field.updateScore();
}