#include <game/Field.h>

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

void Field::updateScore() {
    Score currentScore = 0;
    for (size_t i = 0; i < this->FieldSize; ++i) {
        currentScore += this->field[i].score;
    }
    this->score = currentScore;
}

Score Field::getScore() {
    return this->score;
}

bool Field::hasMoves() const {
    if (!this->getEmptyTiles().empty()) {
        return true;
    }

    for (size_t x = 0; x < this->field.size(); ++x) {
        for (size_t y = 0; y < this->field.size(); ++y) {
            if (this->field[x][y] == this->field[x + 1][y] || 
                this->field[x][y] == this->field[x][y + 1] ) {
                return true;
            }
        }
    }
    return false;
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

std::vector<Line> Field::getField() const {
    return this->field;
}


void Field::debug() const {
    for (size_t i = 0; i < this->FieldSize; ++i) {
        for (size_t j = 0; j < this->FieldSize; ++j) {
            printf("%3llu ", this->field[i][j]);
        }
        printf("\n");
    }
    printf("Current score: %llu", this->score);
}