#include <iostream>
#include <vector>
#include <algorithm>
#include "field.h"

using Tile = unsigned long long int;

void printVecOfPos(const std::vector<Position> &positions) {
    for (const auto &pos : positions) {
        std::cout << pos.x << ' ' << pos.y << '\n';
    }
}

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