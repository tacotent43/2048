#include <iostream>
#include <vector>
#include <algorithm>
#include "field.h"


using Tile = unsigned long long int;

int main() {
    Field field(4);
    char action;
    bool canMove = true;

    field.spawnTile(field.getEmptyTiles());
    field.spawnTile(field.getEmptyTiles());

    while (canMove) {
        field.debug();
        std::cin >> action;
        switch (action) {
        case 'w':
            canMove = field.move(Direction::up);
            field.spawnTile(field.getEmptyTiles());
            break;
        case 's':
            canMove = field.move(Direction::down);
            field.spawnTile(field.getEmptyTiles());
            break;
        case 'a':
            canMove = field.move(Direction::left);
            field.spawnTile(field.getEmptyTiles());
            break;
        case 'd':
            canMove = field.move(Direction::right);
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