#pragma once

#include "tilePosition.h"
#include "line.h"
#include "types.h"

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

    std::vector<Tile> processLine(const std::vector<Tile> &sourceLine, Score &score);

    Line getRow(size_t rowIndex) const;
    std::vector<Tile> getColumn(size_t columnIndex) const;
    void setRow(size_t rowIndex, const std::vector<Tile> &line);
    void setColumn(size_t columnIndex, const std::vector<Tile> &line);

    void reset();
    void setSize(size_t size);

public:
    Field(size_t fieldSize);

    bool canMove() const;
    bool moveUp();
    bool moveDown();
    bool moveLeft();
    bool moveRight();

    std::vector<Position> getEmptyTiles() const;
    bool spawnTile(const std::vector<Position> &empty);

    void debug() const;
};