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
            field.spawnTile();
            break;
        case 's':
            field.moveDown();
            field.spawnTile();
            break;
        case 'a':
            field.moveLeft();
            field.spawnTile();
            break;
        case 'd':
            field.moveRight();
            field.spawnTile();
            break;
        default:
            return 0;
        }
    }

    return 0;
}