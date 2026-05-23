#include "types.h"

#include <vector>

struct Line {
    std::vector<Tile> line;
    Score score;

    explicit Line();
    Line(size_t length);

    void process();
};