#pragma once

#include <game/types.hpp>

#include <vector>

class Line : public std::vector<Tile> {
public:
    using std::vector<Tile>::vector;

    Score score = 0;
    void process();
};