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
    drawNumberOfStonesText(Vec2{ 100, 500 }, U"$0 {}"_fmt(gameBoard.getNumberOfBlackStones()));
    drawNumberOfStonesText(Vec2{ 300, 500 }, U"$1 {}"_fmt(gameBoard.getNumberOfWhiteStones()));
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
