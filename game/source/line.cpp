#include <game/line.h>

void Line::process() {
    Line result;
    Tile pending = 0;
    bool hasPending = false;
    
    for (Tile element : *this) {
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
    
    while (result.size() < this->size()) {
        result.push_back(0);
    }
    
    *this = result;
}
