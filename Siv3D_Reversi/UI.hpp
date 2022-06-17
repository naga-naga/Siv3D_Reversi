#pragma once
#include "Common.hpp"
#include "GameBoard.hpp"

class UI {
public:
    UI(GameBoard& board);

    void draw();

private:
    GameBoard& gameBoard;

    const Font numberOfStonesFont{ 30 };

    const Array<Texture> emojiStones = {
        Texture{ U"⚫"_emoji },
        Texture{ U"⚪"_emoji },
    };

    void drawResetButton();

    void drawNumberOfStones();

    void drawNumberOfStonesText(Vec2 penPos, String text);

    void drawPlayerFrame(Vec2 pos);
};
