#include <iostream>
#include <vector>
#include <algorithm>
#include "field.h"

using Tile = unsigned long long int;

int main() {
    Field field(4);
    char action;

    while (true) {
        field.debug();
        std::cin >> action;
        switch (action)
        {
        case 'w':
            field.moveUp();
            field.spawnTile(field.getEmptyTiles());
            break;
        case 's':
            field.moveDown();
            field.spawnTile(field.getEmptyTiles());
            break;
        case 'a':
            field.moveLeft();
            field.spawnTile(field.getEmptyTiles());
            break;
        case 'd':
            field.moveRight();
            field.spawnTile(field.getEmptyTiles());
            break;
        default:
            return 0;
        }
    }

    return 0;
}