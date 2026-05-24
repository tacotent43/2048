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
    bool move(Direction direction);
*/

// PRIVATE
Line Field::getRow(size_t rowIndex) const {
    return this->field[rowIndex];
}

Line Field::getColumn(size_t columnIndex) const {
    // from top to bottom
    Line column(this->FieldSize);
    for (size_t i = 0; i < this->FieldSize; ++i) {
        column[i] = this->field[i][columnIndex];
    }
    return column;
}

void Field::setRow(size_t rowIndex, const Line &line) {
    this->field[rowIndex] = line;
}

void Field::setColumn(size_t columnIndex, const Line &line) {
    // from top to bottom (same)
    for (size_t i = 0; i < this->FieldSize; ++i) {
        this->field[i][columnIndex] = line[i];
    }
}

void Field::reset() {
    this->field.resize(this->FieldSize);
    for (size_t i = 0; i < this->FieldSize; ++i) {
        this->field[i] = Line(this->FieldSize);
    }
}

// PUBLIC
Field::Field(size_t fieldSize) : mt(std::random_device{}()), FieldSize(fieldSize) {
    this->reset();
}

void printVector(const Line &arr) {
    for (size_t i = 0; i < arr.size(); ++i) {
        printf("%llu ", arr[i]);
    }
    printf("\n");
}

bool Field::move(Direction direction) {
    auto oldField = this->field;
    Line column(this->FieldSize);
    Line row(this->FieldSize);

    switch (direction) {
    case Direction::up:
        for (size_t i = 0; i < this->FieldSize; ++i) {
            column = getColumn(i);
            column.process();
            setColumn(i, column);
        }
        break;
    case Direction::down:
        for (size_t i = 0; i < this->FieldSize; ++i) {
            column = getColumn(i); 
            std::reverse(column.begin(), column.end());
            column.process();
            std::reverse(column.begin(), column.end());
            setColumn(i, column);
        }
        break;
    case Direction::left:
        for (size_t i = 0; i < this->FieldSize; ++i) {
            row = getRow(i);
            row.process();
            setRow(i, row);
        }
        break;
    case Direction::right:
        for (size_t i = 0; i < this->FieldSize; ++i) {
            row = getRow(i);
            std::reverse(row.begin(), row.end());
            row.process();
            std::reverse(row.begin(), row.end());
            setRow(i, row);
        }
        break;
    default:
        throw std::exception();
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