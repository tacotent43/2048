#include <iostream>
#include <vector>
#include <algorithm>
#include "field.h"


using Tile = unsigned long long int;

int main() {
    Field field(4);
    char action;

    field.spawnTile(field.getEmptyTiles());
    field.spawnTile(field.getEmptyTiles());

    while (true) {
        field.debug();
        std::cin >> action;
        switch (action)
        {
        case 'w':
            field.move(Direction::up);
            field.spawnTile(field.getEmptyTiles());
            break;
        case 's':
            field.move(Direction::down);
            field.spawnTile(field.getEmptyTiles());
            break;
        case 'a':
            field.move(Direction::left);
            field.spawnTile(field.getEmptyTiles());
            break;
        case 'd':
            field.move(Direction::right);
            field.spawnTile(field.getEmptyTiles());
            break;
        default:
            return 0;
        }
    }

    return 0;
}