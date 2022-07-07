#include "Common.hpp"
#include "GameBoard.hpp"
#include "Title.hpp"

void Main() {
    App manager;

    manager.add<Title>(U"Title");
    manager.add<GameBoard>(U"Game");

    Scene::SetBackground(ColorF{ Palette::Mediumseagreen });

    while (System::Update()) {
        if (not manager.update()) {
            break;
        }
    }
}
