#pragma once
#include "Common.hpp"

class Title : public App::Scene {
public:
    Title(const InitData& init);

    void update() override;

    void draw() const override;

private:
    const String titleText = U"リバーシ";

    const Font titleFont{ 40, Typeface::Regular, FontStyle::Bold };

    const Vec2 titleTextPos{ Scene::Center().x, Scene::Center().y - 150 };
};
