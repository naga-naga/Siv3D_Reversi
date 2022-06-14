#pragma once
#include "Common.hpp"

class GameBoard {
public:
    static constexpr int32 CellSize = 50;

    static constexpr int32 Black = 1;

    static constexpr int32 White = -1;

    GameBoard();

    void update();

    void draw() const;

    void reset();

    int32 getNumberOfBlackStones();

    int32 getNumberOfWhiteStones();

private:
    // 置かれた石を表す
    // 角での計算を楽にするため，上下左右1マスずつ大きくとる
    // 実際には 1 ~ 8 を使う
    Grid<int32> stones = Grid<int32>(10, 10);

    int32 currentPlayer = Black;

    ColorF lineColor = ColorF{ 0.2 };

    void updateStones();

    void drawGridLine() const;

    void drawCells() const;

    int32 flipStones(Point cell);

    int32 flipLine(Point cell, Point direction);

    Array<Point> findCellsCanPlaceStone() const;

    Array<Point> findFlippableCells(Point placedPos, Point direction) const;

    void changePlayer();

    bool canPlaceStone();
};
