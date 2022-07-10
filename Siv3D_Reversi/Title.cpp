#include "Title.hpp"

Title::Title(const InitData& init)
    : IScene{ init }
{
}

void Title::update() {
    ClearPrint();
    Print << U"Title Scene";

    if (MouseL.down()) {
        changeScene(U"Game");
    }
}

void Title::draw() const {
    titleFont(titleText).drawAt(titleTextPos);
}
