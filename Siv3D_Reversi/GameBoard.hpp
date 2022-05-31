#pragma once
#include "Common.hpp"

class GameBoard {
public:
    static constexpr int32 CellSize = 50;

    static constexpr int32 Black = 1;

    static constexpr int32 White = -1;

	GameBoard();

    void draw() const;

private:
    // 置かれた石を表す
    // 角での計算を楽にするため，上下左右1マスずつ大きくとる
    // 実際には 1 ~ 8 を使う
    Grid<int32> stones = Grid<int32>(10, 10);

    ColorF lineColor = ColorF{ 0.2 };

    void drawGridLine() const;

    void drawCells() const;
};
