#pragma once
#include "Common.hpp"
#include "GameBoard.hpp"

class UI {
public:
    UI(GameBoard& board);

    void draw();

private:
    GameBoard& gameBoard;

    void drawResetButton();
};
