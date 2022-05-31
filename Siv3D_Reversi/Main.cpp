#include "Common.hpp"
#include "GameBoard.hpp"

void Main() {
    Scene::SetBackground(ColorF{ Palette::Mediumseagreen });

    GameBoard gameBoard;

    while (System::Update()) {
        gameBoard.draw();
    }
}
