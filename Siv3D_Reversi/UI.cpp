#include "UI.hpp"
#include "GameBoard.hpp"

UI::UI(GameBoard& board)
    : gameBoard(board)
{
}

void UI::draw() {
    drawResetButton();
    drawNumberOfStones();
}

void UI::drawResetButton() {
    if (SimpleGUI::Button(U"reset", Vec2{ 500, 10 })) {
        gameBoard.reset();
    }
}

void UI::drawNumberOfStones() {
    Vec2 blackStonesTextPos{ 100, 500 };
    Vec2 whiteStonesTextPos{ 300, 500 };

    if (gameBoard.getCurrentPlayer() == gameBoard.Black) {
        drawPlayerFrame(blackStonesTextPos);
    } else {
        drawPlayerFrame(whiteStonesTextPos);
    }

    drawNumberOfStonesText(blackStonesTextPos, U"$0 {}"_fmt(gameBoard.getNumberOfBlackStones()));
    drawNumberOfStonesText(whiteStonesTextPos, U"$1 {}"_fmt(gameBoard.getNumberOfWhiteStones()));
}

void UI::drawNumberOfStonesText(Vec2 penPos, String text) {
    bool onTag = false;

    for (const auto& glyph : numberOfStonesFont.getGlyphs(text)) {
        if (onTag) {
            emojiStones[(glyph.codePoint - U'0')].resized(40).draw(penPos);
            penPos.x += 30;
            onTag = false;
            continue;
        }

        if (glyph.codePoint == U'$') {
            onTag = true;
            continue;
        }

        onTag = false;
        glyph.texture.draw(penPos + glyph.getOffset());
        penPos.x += glyph.xAdvance;
    }
}

// 現在の手番の色のテキストを囲む
void UI::drawPlayerFrame(Vec2 pos) {
    Rect{ (int32)pos.x, (int32)pos.y, 100, 40 }.drawFrame(0, 5, Palette::Crimson);
}
