#include "GameBoard.hpp"

GameBoard::GameBoard() {
    stones[4][5] = Black;
    stones[5][4] = Black;
    stones[4][4] = White;
    stones[5][5] = White;
}

void GameBoard::draw() const {
    drawGridLine();
    drawCells();
}

// 格子を描く
void GameBoard::drawGridLine() const {
    for (int32 i = 1; i <= 9; i++) {
        // 縦線
        Line{ (i * CellSize), CellSize, (i * CellSize), (9 * CellSize) }.draw(4, lineColor);

        // 横線
        Line{ CellSize, (i * CellSize), (9 * CellSize), (i * CellSize) }.draw(4, lineColor);

    }

    // 黒点
    for (auto i : { 3, 7 }) {
        for (auto j : { 3, 7 }) {
            Circle{ i * CellSize, j * CellSize, 7 }.draw(lineColor);
        }
    }
}

void GameBoard::drawCells() const {
    // 各セルを見ていき，石を描画する．
    for (int32 i = 1; i <= 8; i++) {
        for (int32 j = 1; j <= 8; j++) {
            // セル
            const Rect cell{ (i * CellSize), (j * CellSize), CellSize };

            // セルの石
            const int32 stone = stones[j][i];

            // 石を描画
            if (stone == Black) {
                Circle{ cell.center(), CellSize * 0.4 }.draw(ColorF{ Palette::Black });
                continue;
            } else if (stone == White) {
                Circle{ cell.center(), CellSize * 0.4 }.draw(ColorF{ Palette::White });
                continue;
            }
        }
    }
}
