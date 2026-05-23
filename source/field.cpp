#include "field.h"

/*
Fields:
    std::vector<std::vector<int>> field;

Private methods: 
    std::vector<Tile> processLine(const std::vector<Tile> &sourceLine);

    std::vector<Tile> getRow(size_t idx);
    std::vector<Tile> getColumn(size_t idx);
    void setRow(size_t idx);
    void setColumn(size_t idx);

Public methods: 
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
*/

// PRIVATE
std::vector<Tile> Field::processLine(const std::vector<Tile>& sourceLine, Score &score) {
    std::vector<Tile> result;
    Tile pending = 0;
    bool hasPending = false;
    
    for (Tile element : sourceLine) {
        if (element == 0) continue;
        
        if (!hasPending) {
            pending = element;
            hasPending = true;
            continue;
        }
        
        if (element == pending) {
            result.push_back(pending * 2);
            score += pending * 2;
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

Line Field::getRow(size_t rowIndex) const {
    return this->field[rowIndex];
}

std::vector<Tile> Field::getColumn(size_t columnIndex) const {
    // from top to bottom
    std::vector<Tile> column;
    for (size_t i = 0; i < this->FieldSize; ++i) {
        column.push_back(this->field[i][columnIndex]);
    }
    return column;
}

void Field::setRow(size_t rowIndex, const std::vector<Tile> &line) {
    this->field[rowIndex] = line;
}

void Field::setColumn(size_t columnIndex, const std::vector<Tile> &line) {
    // from top to bottom (same)
    for (size_t i = 0; i < this->FieldSize; ++i) {
        this->field[i][columnIndex] = line[i];
    }
}

void Field::reset() {
    this->field.resize(this->FieldSize, std::vector<Tile>(this->FieldSize, 0));
}

// PUBLIC
Field::Field(size_t fieldSize) : mt(std::random_device{}()), FieldSize(fieldSize) {
    this->reset();
}

void printVector(const std::vector<Tile> &arr) {
    for (size_t i = 0; i < arr.size(); ++i) {
        printf("%llu ", arr[i]);
    }
    printf("\n");
}

bool Field::moveUp() {
    auto oldField = this->field;
    for (size_t i = 0; i < this->FieldSize; ++i) {
        std::vector<Tile> column;
        column = getColumn(i);
        column = processLine(column, this->score);
        setColumn(i, column);
    }
    return this->field != oldField;
}

bool Field::moveDown() {
    auto oldField = this->field;
    for (size_t i = 0; i < this->FieldSize; ++i) {
        std::vector<Tile> column;
        column = getColumn(i);
        std::reverse(column.begin(), column.end());
        column = processLine(column, this->score);
        std::reverse(column.begin(), column.end());
        setColumn(i, column);
    }
    return this->field != oldField; 
}

bool Field::moveLeft() {
    auto oldField = this->field;
    std::vector<Tile> row;
    for (size_t i = 0; i < this->FieldSize; ++i) {
        row = getRow(i);
        row = processLine(row, this->score);
        setRow(i, row);
    }
    return this->field != oldField;
}

bool Field::moveRight() {
    auto oldField = this->field;
    std::vector<Tile> row;
    for (size_t i = 0; i < this->FieldSize; ++i) {
        row = getRow(i);
        std::reverse(row.begin(), row.end());
        row = processLine(row, this->score);
        std::reverse(row.begin(), row.end());
        setRow(i, row);
    }
    return this->field != oldField;
}


std::vector<Position> Field::getEmptyTiles() const {
    std::vector<Position> empty;
    for (size_t i = 0; i < this->FieldSize; ++i) {
        for (size_t j = 0; j < this->FieldSize; ++j) {
            if (this->field[i][j] == 0) {
                empty.push_back(Position(i, j));
            }
        }
    }
    return empty;
}

bool Field::spawnTile(const std::vector<Position> &empty) {
    if (!empty.empty()) {
        std::uniform_int_distribution<> dist(0, static_cast<int>(empty.size() - 1));
        std::uniform_int_distribution<> chance(1, 10);
        int choice = dist(this->mt);
        Position spawnPoint = empty[choice];
        this->field[spawnPoint.x][spawnPoint.y] = ((chance(this->mt) == 10) ? 4 : 2);
        return true;
    }
    return false;
}


void Field::debug() const {
    for (size_t i = 0; i < this->FieldSize; ++i) {
        for (size_t j = 0; j < this->FieldSize; ++j) {
            printf("%5llu ", this->field[i][j]);
        }
        printf("\n");
    }
}