// src/game/game_state/PlayState.cpp
#include "game/game_state/PlayState.h"
#include "Game.h"
#include "raylib.h"
#include <cstdlib>

PlayState::PlayState(Game& game)
    : game(game), playerSpaceship(GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f) {}

void PlayState::Init() {
    InitStars(100);
}

void PlayState::Update(float dt) {
    playerSpaceship.Update(dt);
    UpdateStars(dt);
    // Update other game play elements here
}

void PlayState::Draw() {
    ClearBackground(BLACK);

    playerSpaceship.Draw();
    DrawStars();
    DrawText("Play State", 10, 10, 20, DARKGRAY);
}

void PlayState::Unload() {
    // Unload game play elements here
}

void PlayState::OnExit() {
    // Handle any cleanup when exiting the state
}

void PlayState::InitStars(int count) {
    stars.clear();
    for (int i = 0; i < count; ++i) {
        Star star;
        star.x = static_cast<float>(rand() % GetScreenWidth());
        star.y = static_cast<float>(rand() % GetScreenHeight());
        star.speed = static_cast<float>((rand() % 100) / 10.0f + 1.0f);
        stars.push_back(star);
    }
}

void PlayState::UpdateStars(float dt) {
    for (auto& star : stars) {
        star.y -= star.speed * dt * 100;
        if (star.y < 0) {
            star.x = static_cast<float>(rand() % GetScreenWidth());
            star.y = static_cast<float>(GetScreenHeight());
            star.speed = static_cast<float>((rand() % 100) / 10.0f + 1.0f);
        }
    }
}

void PlayState::DrawStars() {
    for (const auto& star : stars) {
        DrawPixel(static_cast<int>(star.x), static_cast<int>(star.y), WHITE);
    }
}