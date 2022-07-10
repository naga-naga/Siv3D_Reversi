#include "Title.hpp"

Title::Title(const InitData& init)
    : IScene{ init }
{
}

void Title::update() {
    ClearPrint();
    Print << U"Title Scene";

    if (SimpleGUI::ButtonAt(startButtonText, startButtonPos)) {
        changeScene(U"Game");
    }
}

void Title::draw() const {
    titleFont(titleText).drawAt(titleTextPos);
}
