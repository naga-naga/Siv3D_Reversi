#include "UI.hpp"
#include "GameBoard.hpp"

UI::UI(GameBoard& board)
    : gameBoard(board)
{
}

void UI::draw() {
    drawResetButton();
}

void UI::drawResetButton() {
    if (SimpleGUI::Button(U"reset", Vec2{ 500, 10 })) {
        gameBoard.reset();
    }
}
