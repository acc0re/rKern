// src/game/PlayerSpaceship.cpp
#include <raylib.h>
#include <cmath>
#include "game/PlayerSpaceship.h"


PlayerSpaceship::PlayerSpaceship(float baseX, float baseY) : Spaceship(baseX, baseY) {}

void PlayerSpaceship::Update(float time) {
    if (IsKeyDown(KEY_RIGHT)) x += 200.0f * time;
    if (IsKeyDown(KEY_LEFT)) x -= 200.0f * time;
    if (IsKeyDown(KEY_UP)) y -= 200.0f * time;
    if (IsKeyDown(KEY_DOWN)) y += 200.0f * time;

    top = {x, y - 30.0f};
    left = {x - 15.0f, y + 15.0f};
    right = {x + 15.0f, y + 15.0f};

    flameLength = 20.0f + sin(time * 10.0f) * 20.0f;
}

void PlayerSpaceship::Draw() const {
    // Draw a simple rectangle
    DrawRectangle(static_cast<int>(x - 15), static_cast<int>(y - 15), 30, 30, LIGHTGRAY);
}