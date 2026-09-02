#pragma once

#include <game/types.hpp>

#include <vector>

// struct Line {
//     std::vector<Tile> line;
//     Score score = 0;

//     explicit Line();
//     Line(size_t length);

//     void process();

//     void push_back(Tile tile);
//     size_t size() const;

//     Tile& operator[](size_t index);
//     const Tile& operator[](size_t index) const;
//     bool operator==(const Line &other) const;
//     bool operator!=(const Line &other) const;
// };

class Line : public std::vector<Tile> {
public:
    using std::vector<Tile>::vector;

    Score score = 0;
    void process();
};