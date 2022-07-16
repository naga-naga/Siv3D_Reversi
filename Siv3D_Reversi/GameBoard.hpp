#pragma once
#include "Common.hpp"

class GameBoard : public App::Scene {
public:
    GameBoard(const InitData& init);

    void update();

    void draw() const;

    void reset();

    bool isGameOver() const;

    void setGameOverFlag(bool flag);

    int32 getNumberOfBlackStones() const;

    int32 getNumberOfWhiteStones() const;

    int32 getCurrentPlayer() const;

    void setCurrentPlayer(int32 player);

private:
    static constexpr int32 CellSize = 50;

    static constexpr int32 Black = 1;

    static constexpr int32 White = -1;

    // 置かれた石を表す
    // 角での計算を楽にするため，上下左右1マスずつ大きくとる
    // 実際には 1 ~ 8 を使う
    Grid<int32> stones = Grid<int32>(10, 10);

    int32 currentPlayer = Black;

    ColorF lineColor = ColorF{ 0.2 };

    bool gameOver = false;

    const Font numberOfStonesFont{ 30 };

    const Array<Texture> emojiStones = {
        Texture{ U"⚫"_emoji },
        Texture{ U"⚪"_emoji },
    };

    void updateStones();

    void drawGridLine() const;

    void drawCells() const;

    void drawNumberOfStones() const;

    void drawNumberOfStonesText(Vec2 penPos, String text) const;

    void drawPlayerFrame(Vec2 pos) const;

    int32 flipStones(Point cell);

    int32 flipLine(Point cell, Point direction);

    Array<Point> findCellsCanPlaceStone() const;

    Array<Point> findFlippableCells(Point placedPos, Point direction) const;

    void changePlayer();

    bool canPlaceStone() const;
};
