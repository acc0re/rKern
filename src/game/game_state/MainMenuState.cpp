#include "game/game_state/MainMenuState.h"
#include "Game.h"
#include "raylib.h"
#include <vector>
#include <cstdlib>

MainMenuState::MainMenuState(Game& game) : game(game) {
    selectedOption = 0;
}

void MainMenuState::Init() {
    InitStars(100); // Initialize 100 stars
}

void MainMenuState::InitStars(int count) {
    stars.clear();
    for (int i = 0; i < count; ++i) {
        Star star;
        star.x = static_cast<float>(rand() % GetScreenWidth());
        star.y = static_cast<float>(rand() % GetScreenHeight());
        star.speed = static_cast<float>((rand() % 100) / 10.0f + 1.0f);
        stars.push_back(star);
    }
}

void MainMenuState::Update(float deltaTime) {
    if (IsKeyPressed(KEY_DOWN)) selectedOption++;
    if (IsKeyPressed(KEY_UP)) selectedOption--;

    if (selectedOption < 0) selectedOption = 0;
    if (selectedOption > 2) selectedOption = 2;

    if (IsKeyPressed(KEY_ENTER) && selectedOption == 2) {
        game.Shutdown();
    }

    UpdateStars(deltaTime);
}

void MainMenuState::UpdateStars(float deltaTime) {
    for (auto& star : stars) {
        star.y += star.speed * deltaTime * 100;
        if (star.y > GetScreenHeight()) {
            star.x = static_cast<float>(rand() % GetScreenWidth());
            star.y = 0;
            star.speed = static_cast<float>((rand() % 100) / 10.0f + 1.0f);
        }
    }
}

void MainMenuState::Draw() {
    ClearBackground(BLACK);
    DrawStars();

    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    float scaleFactor = screenHeight / 720.0f;

    const char* menuTitle = "rKern";
    const char* startGame = "Start Game";
    const char* options = "Options";
    const char* exit = "Exit";

    int titleFontSize = static_cast<int>(80 * scaleFactor);
    int optionFontSize = static_cast<int>(40 * scaleFactor);

    int titleWidth = MeasureText(menuTitle, titleFontSize);
    int startGameWidth = MeasureText(startGame, optionFontSize);
    int optionsWidth = MeasureText(options, optionFontSize);
    int exitWidth = MeasureText(exit, optionFontSize);

    int titleX = (screenWidth - titleWidth) / 2;
    int startGameX = (screenWidth - startGameWidth) / 2;
    int optionsX = (screenWidth - optionsWidth) / 2;
    int exitX = (screenWidth - exitWidth) / 2;

    int titleY = static_cast<int>(screenHeight / 4);
    int startGameY = titleY + static_cast<int>(90 * scaleFactor);
    int optionsY = startGameY + static_cast<int>(60 * scaleFactor);
    int exitY = optionsY + static_cast<int>(60 * scaleFactor);

    DrawText(menuTitle, titleX, titleY, titleFontSize, LIGHTGRAY);
    DrawText(startGame, startGameX, startGameY, optionFontSize, (selectedOption == 0) ? BLUE : DARKGRAY);
    DrawText(options, optionsX, optionsY, optionFontSize, (selectedOption == 1) ? BLUE : DARKGRAY);
    DrawText(exit, exitX, exitY, optionFontSize, (selectedOption == 2) ? BLUE : DARKGRAY);
}

void MainMenuState::DrawStars() {
    for (const auto& star : stars) {
        DrawPixel(static_cast<int>(star.x), static_cast<int>(star.y), WHITE);
    }
}

void MainMenuState::Unload() {
}

void MainMenuState::OnExit() {
}