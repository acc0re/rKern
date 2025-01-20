// src/game/MenuSpaceship.cpp
#include "game/MenuSpaceship.h"
#include <cmath>

MenuSpaceship::MenuSpaceship(float baseX, float baseY) : Spaceship(baseX, baseY) {}

void MenuSpaceship::Update(float time)
{
    x = baseX + 120.0f * sin(time * 2.0f);
    y = baseY;

    top = {x, y + 60.0f};
    left = {x - 30.0f, y + 20.0f};
    right = {x + 30.0f, y + 20.0f};

    flameLength = 20.0f + sin(time * 10.0f) * 20.0f;
}