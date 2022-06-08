#include "GameBoard.hpp"

GameBoard::GameBoard() {
    this->reset();
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

void GameBoard::reset() {
    stones.fill(0);
    stones[4][5] = Black;
    stones[5][4] = Black;
    stones[4][4] = White;
    stones[5][5] = White;
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

    // 石を置けるセルを探す
    const Array<Point> cellsCanPlaceStone = findCellsCanPlaceStone();

    // 石を置けるセルを強調する
    for (auto c : cellsCanPlaceStone) {
        // 強調するセル
        const Rect colorCell{ (c.x * CellSize), (c.y * CellSize), CellSize };

        // 半透明の白を描く
        colorCell.stretched(-2).draw(ColorF{ 1.0, 0.6 });

        if (colorCell.mouseOver()) {
            // カーソルを手のアイコンにする
            Cursor::RequestStyle(CursorStyle::Hand);
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

// 石を置けるセルを探す
// 返り値: 石を置けるセルを格納した Array
Array<Point> GameBoard::findCellsCanPlaceStone() const {
    Array<Point> cellsCanPlaceStone;

    // 全てのセルを見る
    for (int32 x = 1; x <= 8; x++) {
        for (int32 y = 1; y <= 8; y++) {
            // すでに石が置かれていれば次のマスを見る
            if (stones[y][x] != 0) {
                continue;
            }

            Array<Point> flippableCells;

            // 8方向確認する
            for (auto i : { -1, 0, 1 }) {
                for (auto j : { -1, 0, 1 }) {
                    // (x, y) に石を置いたときにひっくり返せるセル
                    flippableCells.append(findFlippableCells(Point{ x, y }, Point{ i, j }));
                }
            }

            // (x, y) に石を置いたときに返せるセルがある場合
            if (not flippableCells.isEmpty()) {
                // ここに石を置ける
                cellsCanPlaceStone.push_back(Point{ x, y });
            }
        }
    }

    return cellsCanPlaceStone;
}

// ひっくり返せるセルを探す
// placedPos: 石を置いたセル
// direction: 探す方向
// 返り値: 返せるセルを格納した Array
Array<Point> GameBoard::findFlippableCells(Point placedPos, Point direction) const {
    Point pos = placedPos + direction;

    // 自分と反対の色の間 direction の方向を見ていく
    while (stones[pos.y][pos.x] == -currentPlayer) {
        pos += direction;
    }

    // 挟めていなかった場合はここで終了
    if (stones[pos.y][pos.x] != currentPlayer) {
        return Array<Point>{};
    }

    Array<Point> flippableCells;

    // 挟めていた場合はひっくり返せる
    pos -= direction;
    while (pos != placedPos) {
        // pos はひっくり返せるセル
        flippableCells.push_back(pos);
        pos -= direction;
    }

    return flippableCells;
}
