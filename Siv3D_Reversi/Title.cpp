#include "Title.hpp"

Title::Title(const InitData& init)
    : IScene{ init }
{
}

void Title::update() {
    if (SimpleGUI::ButtonAt(startButtonText, startButtonPos)) {
        changeScene(U"Game");
    }
}

void Title::draw() const {
    titleFont(titleText).drawAt(titleTextPos);
}
