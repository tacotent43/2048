#include "types.h"

#include <vector>

struct Line {
    std::vector<Tile> line;
    Score score = 0;

    explicit Line();
    Line(size_t length);

    void process();

    void push_back(Tile tile);
    size_t size();
    size_t size() const;

    Tile& operator[](size_t index);
    const Tile& operator[](size_t index) const;
    bool operator==(const Line &other) const;
    bool operator!=(const Line &other) const;

    std::vector<Tile>::iterator begin();
    std::vector<Tile>::iterator end();
    std::vector<Tile>::const_iterator begin() const;
    std::vector<Tile>::const_iterator end() const;
};