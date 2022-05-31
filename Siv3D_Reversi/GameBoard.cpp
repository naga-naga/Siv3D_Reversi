#include "GameBoard.hpp"

GameBoard::GameBoard() {
    stones[4][5] = Black;
    stones[5][4] = Black;
    stones[4][4] = White;
    stones[5][5] = White;
}

void GameBoard::update() {
    for (int32 i = 1; i <= 8; i++) {
        for (int32 j = 1; j <= 8; j++) {
            // セル
            const Rect cell{ (i * CellSize), (j * CellSize), CellSize };

            // セルの石
            const int32 stone = stones[j][i];

            // 空白セルをクリックした場合
            if ((stone == 0) && cell.leftClicked()) {
                // 置かれた場所
                const Point placedPos = cell.tl() / CellSize;

                // 置けるか判定する
                // (1, 1) ~ (8, 8) に変換する
                const int32 numberOfFlipped = flipStones(placedPos);

                if (numberOfFlipped == 0) {
                    // 返せなかった場合は何もしない
                    continue;
                } else {
                    // 石を置く
                    stones[placedPos.y][placedPos.x] = currentPlayer;

                    // 手番交代
                    currentPlayer *= -1;
                }
            }
        }
    }
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

// 8方向の石をひっくり返す
// cell: 置いた場所
// 返り値: ひっくり返した数
int32 GameBoard::flipStones(Point cell) {
    int32 numberOfFlipped = 0;

    // 8方向ひっくり返す
    for (auto i : { -1, 0, 1 }) {
        for (auto j : { -1, 0, 1 }) {
            numberOfFlipped += flipLine(cell, Point{ i, j });
        }
    }

    return numberOfFlipped;
}

// ある方向の石をひっくり返す
// cell: 置いた場所
// direction: 方向．{[-1 | 0 | 1], [-1 | 0 | 1]}
// 返り値: ひっくり返した数
int32 GameBoard::flipLine(Point placedPos, Point direction) {
    Point pos = placedPos + direction;

    // 自分と反対の色の間 direction の方向を見ていく
    while (stones[pos.y][pos.x] == -currentPlayer) {
        pos += direction;
    }

    // 挟めていなかった場合はここで終了
    if (stones[pos.y][pos.x] != currentPlayer) {
        return 0;
    }

    int32 numberOfFlipped = 0;

    // 挟めていた場合はひっくり返す
    pos -= direction;
    while (pos != placedPos) {
        stones[pos.y][pos.x] = currentPlayer;
        pos -= direction;
        numberOfFlipped++;
    }

    return numberOfFlipped;
}
