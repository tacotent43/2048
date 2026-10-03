#pragma once

#include <game/Types.hpp>

#include <vector>

class Line : public std::vector<Tile> {
public:
    using std::vector<Tile>::vector;

    Score score = 0;
    void process();
};