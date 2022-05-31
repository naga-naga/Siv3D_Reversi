﻿#pragma once
#include "Common.h"

class GameBoard {
public:
    static constexpr int32 CellSize = 50;

    void draw() const;

private:
    ColorF lineColor = ColorF{ 0.2 };

    void drawGridLine() const;
};
