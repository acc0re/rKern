#include "game/game_state/MainMenuState.h"
#include "Game.h"
#include "raylib.h"
#include <vector>
#include <cstdlib>
#include <cmath>

MainMenuState::MainMenuState(Game& game) : game(game), spaceshipBaseX(GetScreenWidth() / 2.0f)
{
    selectedOption = 0;
    InitAudioDevice();
    backgroundMusic = LoadMusicStream("sfx/space_adventure.mp3");
}

void MainMenuState::Init()
{
    InitStars(100);
    PlayMusicStream(backgroundMusic);
}

void MainMenuState::InitStars(int count)
{
    stars.clear();
    for (int i = 0; i < count; ++i)
    {
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
    UpdateMusicStream(backgroundMusic);
}

void MainMenuState::UpdateStars(float deltaTime)
{
    for (auto& star : stars)
    {
        star.y += star.speed * deltaTime * 100;
        if (star.y > GetScreenHeight())
        {
            star.x = static_cast<float>(rand() % GetScreenWidth());
            star.y = 0;
            star.speed = static_cast<float>((rand() % 100) / 10.0f + 1.0f);
        }
    }
}

void MainMenuState::Draw()
{
    ClearBackground(BLACK);
    DrawStars();

    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    float scaleFactor = screenHeight / 720.0f;

    const char* menuTitle = "Laser Blast";
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

    float time = GetTime();
    unsigned char pulse = static_cast<unsigned char>(127 * (1 + sin(time * 5.0f))); // Pulsing effect

    // Update spaceship position
    float spaceshipX = spaceshipBaseX + 120.0f * sin(time * 2.0f); // Oscillate around base position

    // Adjust the Y position of the spaceship
    float spaceshipY = screenHeight - 100.0f; // Move the spaceship higher

    Vector2 shipTop = {spaceshipX, spaceshipY - 60.0f};
    Vector2 shipLeft = {spaceshipX - 30.0f, spaceshipY - 20.0f};
    Vector2 shipRight = {spaceshipX + 30.0f, spaceshipY - 20.0f};

    // Draw ship
    DrawTriangleLines(shipTop, shipLeft, shipRight, LIGHTGRAY);

    int numFlames = 2;
    float flameLength = 50.0f + sin(time * 10.0f) * 20.0f; // Flame length

    for (int i = 0; i < numFlames; ++i)
    {
        float angleOffset = (i - numFlames / 2.0f) * 0.2f; // Change angle of flames

        // Left flame
        float leftAngle = (PI / 1.6f) - angleOffset; // Inverted angle for left flame
        Vector2 flameStart = shipLeft; // Flame left position on ship
        Vector2 flameEnd = {
            flameStart.x + static_cast<float>(cos(leftAngle) * flameLength),
            flameStart.y + static_cast<float>(sin(leftAngle) * flameLength)
        };
        DrawLineEx(flameStart, flameEnd, 2.0f, Color{255, 69, 0, pulse}); // Red pulsing flames

        // Right flame
        float rightAngle = (PI / 2.4f) + angleOffset; // Original angle for right flame
        flameStart = shipRight;
        flameEnd = {
            flameStart.x + static_cast<float>(cos(rightAngle) * flameLength),
            flameStart.y + static_cast<float>(sin(rightAngle) * flameLength)
        };
        DrawLineEx(flameStart, flameEnd, 5.0f, Color{255, 69, 0, pulse});
    }

    // Draw menu options
    DrawText(menuTitle, titleX, titleY, titleFontSize, LIGHTGRAY);
    DrawText(startGame, startGameX, startGameY, optionFontSize,
             (selectedOption == 0) ? Color{0, 0, 255, pulse} : DARKGRAY);
    DrawText(options, optionsX, optionsY, optionFontSize, (selectedOption == 1) ? Color{0, 0, 255, pulse} : DARKGRAY);
    DrawText(exit, exitX, exitY, optionFontSize, (selectedOption == 2) ? Color{0, 0, 255, pulse} : DARKGRAY);
}

void MainMenuState::DrawStars()
{
    for (const auto& star : stars)
    {
        DrawPixel(static_cast<int>(star.x), static_cast<int>(star.y), WHITE);
    }
}

void MainMenuState::Unload() {
    UnloadMusicStream(backgroundMusic);
    CloseAudioDevice();
}

void MainMenuState::OnExit()
{
}
