#include "Common.hpp"
#include "GameBoard.hpp"
#include "UI.hpp"

void Main() {
    Scene::SetBackground(ColorF{ Palette::Mediumseagreen });

    GameBoard gameBoard;
    UI ui{ gameBoard };

    while (System::Update()) {
        gameBoard.draw();
        gameBoard.update();

        ui.draw();
    }
}
