#include <sdl/GameWindow.h>

// private
void GameWindow::quit() {
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
    TTF_Quit();
    SDL_Quit();
}

FPosition GameWindow::drawTile(unsigned long long int number, int x, int y) {
    std::string text = std::to_string(number);

    SDL_Surface *surface = TTF_RenderText_Blended(
        font, text.c_str(), text.size(), SDL_Color({225, 225, 225})
    );
    SDL_Texture *texture = SDL_CreateTextureFromSurface(this->renderer, surface);

    float tWidth = 0; 
    float tHeight = 0;

    SDL_GetTextureSize(texture, &tWidth, &tHeight);
    SDL_FRect dst = {x, y, tWidth, tHeight};

    SDL_RenderTexture(renderer, texture, NULL, &dst);

    SDL_DestroyTexture(texture);
    SDL_DestroySurface(surface);

    return FPosition(tWidth, tHeight);
}

void GameWindow::drawField(const std::vector<Line> &field) {
    std::vector<std::vector<FPosition>> centerPoints{this->gameFieldSize, std::vector<FPosition>{this->gameFieldSize}};

    for (int i = 0; i < this->gameFieldSize; ++i) {
        for (int j = 0; j < this->gameFieldSize; ++j) {
            centerPoints[i - 0][j - 0].x = this->WindowWidth * (0.125f + 0.09375f + 0.1875 * i);
            centerPoints[i - 0][j - 0].y = this->WindowHeight * (0.125f + 0.09375f + 0.1875 * j);
        }
    }

    SDL_SetRenderDrawColor(
        this->renderer,
        255, 255, 255, 255
    );

    for (int i = 0; i < field.size(); ++i) {
        for (int j = 0; j < field[i].size(); ++j) {
            this->drawTile(field[i][j], centerPoints[i][j].x, centerPoints[i][j].y);
        }
    }
}

void GameWindow::drawGrid() {
    const float borderOffset = 0.125f;
    const float borderLength = 0.75f;
    const float lineOffset   = 0.1875f; // hard-coded value

    SDL_FRect outline;

    outline.x = outline.y = this->WindowWidth * borderOffset;
    outline.w = outline.h = this->WindowWidth * borderLength;

    SDL_SetRenderDrawColor(
        this->renderer,
        255, 255, 255, 255
    );

    SDL_RenderRect(this->renderer, &outline);

    for (int i = 0; i < this->gameFieldSize; ++i) {
        SDL_RenderLine(
            this->renderer, 
            this->WindowWidth * (borderOffset + lineOffset * i),
            this->WindowHeight * borderOffset,
            this->WindowWidth * (borderOffset + lineOffset * i), 
            this->WindowHeight * (borderOffset + borderLength)
        );
    }

    for (int i = 0; i < this->gameFieldSize; ++i) {
        SDL_RenderLine(
            this->renderer, 
            this->WindowHeight * borderOffset,
            this->WindowWidth * (borderOffset + lineOffset * i),
            this->WindowHeight * (borderOffset + borderLength), 
            this->WindowWidth * (borderOffset + lineOffset * i) 
        );
    }
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

    this->font = TTF_OpenFont("fonts/JetBrainsMono-Thin.ttf", 96);
    if (!font) {
        SDL_Log("Font load error: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    SDL_SetRenderLogicalPresentation(
        this->renderer,
        this->WindowWidth, this->WindowHeight,
        SDL_LOGICAL_PRESENTATION_LETTERBOX
    );

    this->field = Field(this->gameFieldSize);
    field.spawnTile(field.getEmptyTiles());

    return SDL_APP_CONTINUE;
}

SDL_AppResult GameWindow::event(SDL_Event *event) {
    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;
    }
    return SDL_APP_CONTINUE;
}

SDL_AppResult GameWindow::iterate() {
    SDL_RenderClear(this->renderer);

    SDL_SetRenderDrawColor(
        this->renderer,
        0, 0, 0, 255
    );

    this->drawGrid();
    this->drawField(this->field.getField());
    
    SDL_SetRenderDrawColor(
        this->renderer,
        0, 0, 0, 255
    );

    SDL_RenderPresent(this->renderer);
    return SDL_APP_CONTINUE;
}

