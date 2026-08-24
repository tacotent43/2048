#include <game/line.h>

Line::Line() = default;

Line::Line(size_t length) : line(length) {}

void Line::process() {
    std::vector<Tile> result;
    Tile pending = 0;
    bool hasPending = false;
    
    for (Tile element : this->line) {
        if (element == 0) continue;
        
        if (!hasPending) {
            pending = element;
            hasPending = true;
            continue;
        }
        
        if (element == pending) {
            result.push_back(pending * 2);
            this->score += pending * 2;
            hasPending = false;
            pending = 0;
        } else {
            result.push_back(pending);
            pending = element;
        }
    }
    
    if (hasPending) {
        result.push_back(pending);
    }
    
    while (result.size() < this->line.size()) {
        result.push_back(0);
    }
    
    this->line = result;
}

// base methods
void Line::push_back(Tile tile) {
    this->line.push_back(tile);
}

size_t Line::size() const {
    return this->line.size();
}

// overloadings
Tile& Line::operator[](size_t index) {
    return this->line[index];
}

const Tile& Line::operator[](size_t index) const {
    return this->line[index];
}

bool Line::operator==(const Line &other) const {
    return this->line == other.line && this->score == other.score;
}

bool Line::operator!=(const Line &other) const {
    return !(*this == other);
}

// iterators
std::vector<Tile>::iterator Line::begin() {
    return this->line.begin();
}

std::vector<Tile>::iterator Line::end() {
    return this->line.end();
}

std::vector<Tile>::const_iterator Line::begin() const {
    return this->line.begin();
}

std::vector<Tile>::const_iterator Line::end() const {
    return this->line.end();
}