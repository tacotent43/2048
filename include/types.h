#pragma once

using Tile = unsigned long long int;
using Score = unsigned long long int;

enum class Direction {
    up,
    down,
    left,
    right
};

struct Position {
    int x;
    int y;

    Position() : x(0), y(0) {}
    Position(int x, int y) : x(x), y(y) {}
};