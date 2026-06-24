#pragma once

#include "line.h"
#include "types.hpp"

#include <stdio.h>
#include <vector>
#include <algorithm>

#include <random>

class Field {
private:
    std::mt19937 mt;

    Score score = 0;

    size_t FieldSize = 4;
    std::vector<Line> field;

    Line getRow(size_t rowIndex) const;
    Line getColumn(size_t columnIndex) const;
    void setRow(size_t rowIndex, const Line &line);
    void setColumn(size_t columnIndex, const Line &line);

    void reset();
    void setSize(size_t size);

public:
    Field(size_t fieldSize);

    void updateScore();
    Score getScore();
    
    bool hasMoves() const;
    bool move(Direction direction);

    std::vector<Position> getEmptyTiles() const;
    bool spawnTile(const std::vector<Position> &empty);

    void debug() const;
};