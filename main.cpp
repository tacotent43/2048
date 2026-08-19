#include <iostream>
#include <stdexcept>
#include <sdl/GameWindow.h>

// using Tile = unsigned long long int;

// // [debug]
// void printVecOfPos(const std::vector<Position> &positions, int fieldSize) {
//     for (int i = 0; i < fieldSize; ++i) {
//         for (int j = 0; j < fieldSize; ++j) {
//             std::cout << (std::find(positions.begin(), positions.end(), Position(i, j)) != positions.end() ? 1 : 0) << ' ';
//         }
//         std::cout << '\n';
//     }
// }
// // [debug]

// int main() {
//     Field field(4);
//     char action;
//     bool canMove = true;

//     field.spawnTile(field.getEmptyTiles());
//     field.spawnTile(field.getEmptyTiles());

//     while (field.hasMoves()) {
//         field.debug();
//         std::cin >> action;
//         switch (action) {
//         case 'w':
//             field.move(Direction::up);
//             field.spawnTile(field.getEmptyTiles());
//             break;
//         case 's':
//             field.move(Direction::down);
//             field.spawnTile(field.getEmptyTiles());
//             break;
//         case 'a':
//             field.move(Direction::left);
//             field.spawnTile(field.getEmptyTiles());
//             break;
//         case 'd':
//             field.move(Direction::right);
//             field.spawnTile(field.getEmptyTiles());
//             break;
//         default:
//             return 0;
//         }
//         field.updateScore();
//     }
//     if (!canMove) {
//         printf("Game Over! Score: %llu", field.getScore());
//     }

//     return 0;
// }

int main() {
    GameWindow window;
    
    SDL_AppResult initialized = window.initialize();
    if (initialized == SDL_APP_FAILURE) {
        throw std::runtime_error("Could not initialize window");
    }

    bool running = true;

    while (running) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            SDL_AppResult eventResult = window.event(&e);
            if (eventResult == SDL_APP_SUCCESS) {
                running = false;
            }
        }
        window.iterate();
    }

    return 0;
}