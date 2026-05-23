#include "line.h"

Line::Line() {
    this->line.clear();
    this->line.reserve(4);
}

Line::Line(size_t length) {
    this->line.clear();
    this->line.reserve(length);
}

void Line::processLine() {
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
    
    while (result.size() < sourceLine.size()) {
        result.push_back(0);
    }
    
    return result;
}