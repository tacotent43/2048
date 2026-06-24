#include <iostream>
#include <vector>
#include <algorithm>
#include "field.h"

using Tile = unsigned long long int;

// [debug]
void printVecOfPos(const std::vector<Position> &positions, int fieldSize) {
    for (int i = 0; i < fieldSize; ++i) {
        for (int j = 0; j < fieldSize; ++j) {
            std::cout << (std::find(positions.begin(), positions.end(), Position(i, j)) != positions.end() ? 1 : 0) << ' ';
        }
        std::cout << '\n';
    }
}
// [debug]

int main() {
    Field field(4);
    char action;
    bool canMove = true;

    field.spawnTile(field.getEmptyTiles());
    field.spawnTile(field.getEmptyTiles());

    while (field.hasMoves()) {
        field.debug();
        std::cin >> action;
        switch (action) {
        case 'w':
            field.move(Direction::up);
            printf("EMPTY POSITIONS");
            printVecOfPos(field.getEmptyTiles());
            field.spawnTile(field.getEmptyTiles());
            break;
        case 's':
            field.move(Direction::down);
            printf("EMPTY POSITIONS");
            printVecOfPos(field.getEmptyTiles());
            field.spawnTile(field.getEmptyTiles());
            break;
        case 'a':
            field.move(Direction::left);
            printf("EMPTY POSITIONS");
            printVecOfPos(field.getEmptyTiles());
            field.spawnTile(field.getEmptyTiles());
            break;
        case 'd':
            field.move(Direction::right);
            printf("EMPTY POSITIONS");
            printVecOfPos(field.getEmptyTiles());
            field.spawnTile(field.getEmptyTiles());
            break;
        default:
            return 0;
        }
        field.updateScore();
    }
    if (!canMove) {
        printf("Game Over! Score: %llu", field.getScore());
    }

    return 0;
}