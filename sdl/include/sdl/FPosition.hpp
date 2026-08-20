#pragma once

struct FPosition {
    float x = 0.0f;
    float y = 0.0f;

    FPosition() : x(0.0f), y(0.0f) {}
    explicit FPosition(float x, float y) : x(x), y(y) {}
};
