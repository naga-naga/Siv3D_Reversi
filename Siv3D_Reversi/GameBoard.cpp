#include "GameBoard.hpp"

void GameBoard::draw() const {
    drawGridLine();
}

// 格子を描く
void GameBoard::drawGridLine() const {
    for (auto i : step(9)) {
        // 縦線
        Line{ (i * CellSize), 0, (i * CellSize), (8 * CellSize) }.draw(4, lineColor);

        // 横線
        Line{ 0, (i * CellSize), (8 * CellSize), (i * CellSize) }.draw(4, lineColor);

    }

    // 黒点
    for (auto i : { 2, 6 }) {
        for (auto j : { 2, 6 }) {
            Circle{ i * CellSize, j * CellSize, 7 }.draw(lineColor);
        }
    }
}
