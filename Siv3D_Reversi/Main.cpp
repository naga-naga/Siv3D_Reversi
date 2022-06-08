#include "Common.hpp"
#include "GameBoard.hpp"

void Main() {
    Scene::SetBackground(ColorF{ Palette::Mediumseagreen });

    GameBoard gameBoard;

    while (System::Update()) {
        gameBoard.draw();
        gameBoard.update();

        if (SimpleGUI::Button(U"reset", Vec2{ 500, 10 })) {
            gameBoard.reset();
        }
    }
}
