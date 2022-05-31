#include "Common.h"
#include "GameBoard.h"

void Main() {
    Scene::SetBackground(ColorF{ Palette::Mediumseagreen });

    GameBoard gameBoard;

    while (System::Update()) {
        gameBoard.draw();
    }
}
