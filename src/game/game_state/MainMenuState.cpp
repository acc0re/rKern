// src/game/game_state/MainMenuState.cpp
#include "game/game_state/MainMenuState.h"
#include "game/game_state/PlayState.h"
#include "Game.h"
#include "raylib.h"
#include <vector>
#include <cstdlib>
#include <cmath>

MainMenuState::MainMenuState(Game& game) : game(game), spaceshipBaseX(GetScreenWidth() / 2.0f)
{
    paused = false;
    selectedOption = 0;
    InitAudioDevice();
    backgroundMusic = LoadMusicStream("sfx/battle.wav");
    switchSound = LoadSound("sfx/switch.mp3");
}

void MainMenuState::Init()
{
    InitStars(100);
    PlayMusicStream(backgroundMusic);
    CalculatePositionsAndValues(GetTime());
}


void MainMenuState::Update(float deltaTime)
{
    if (paused) return;

    static int previousOption = selectedOption;

    if (IsKeyPressed(KEY_DOWN)) selectedOption++;
    if (IsKeyPressed(KEY_UP)) selectedOption--;

    if (selectedOption < 0) selectedOption = 0;
    if (selectedOption > 2) selectedOption = 2;

    if (selectedOption != previousOption)
    {
        PlaySound(switchSound); // Play the switch sound
        previousOption = selectedOption;
    }

    if (IsKeyPressed(KEY_SPACE))
    {
        if (selectedOption == 0)
        {
            StopMusicStream(backgroundMusic);
            game.GetGameStateHandler().ChangeState(std::make_unique<PlayState>(game));
            return; // Return because it crashes with Visual Studio Compiler wtf?
        }
        else if (selectedOption == 2)
        {
            game.Shutdown();
        }
    }

    UpdateStars(deltaTime);
    UpdateMusicStream(backgroundMusic);

    // Update positions and values
    CalculatePositionsAndValues(GetTime());
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

void MainMenuState::UpdateStars(float deltaTime)
{
    for (auto& star : stars)
    {
        star.y -= star.speed * deltaTime * 100;
        if (star.y < 0)
        {
            star.x = static_cast<float>(rand() % GetScreenWidth());
            star.y = static_cast<float>(GetScreenHeight());
            star.speed = static_cast<float>((rand() % 100) / 10.0f + 1.0f);
        }
    }
}

void MainMenuState::Draw()
{
    ClearBackground(BLACK);
    DrawStars();

    // Draw spaceship
    DrawTriangleLines(shipTop, shipLeft, shipRight, LIGHTGRAY);

    int numFlames = 3;
    for (int i = 0; i < numFlames; ++i)
    {
        float angleOffset = (i - numFlames / 2.0f) * 0.2f; // Change angle of flames

        // Left flame
        float leftAngle = (PI / 0.75f) - angleOffset; // Angle for left flame pointing to the top left
        Vector2 flameEnd = CalculateFlameEnd(shipLeft, leftAngle, flameLength);
        Color leftFlameColor = CalculateFlameColor(i, numFlames, GetTime(), true);
        DrawLineEx(shipLeft, flameEnd, 2.0f, leftFlameColor);

        // Right flame
        float rightAngle = (PI / 0.6f) + angleOffset; // Angle for right flame pointing to the top right
        flameEnd = CalculateFlameEnd(shipRight, rightAngle, flameLength);
        Color rightFlameColor = CalculateFlameColor(i, numFlames, GetTime(), false);
        DrawLineEx(shipRight, flameEnd, 2.0f, rightFlameColor);
    }

    // Draw menu options with pulsing effect for the selected option
    float time = GetTime();
    Color selectedColor = {0, 0, 255, static_cast<unsigned char>(127 * (1 + sin(time * 5.0f)))};

    DrawText("rKern", titleX, titleY, 80, LIGHTGRAY);
    DrawText("Start Game", startGameX, startGameY, 40, (selectedOption == 0) ? selectedColor : DARKGRAY);
    DrawText("Options", optionsX, optionsY, 40, (selectedOption == 1) ? selectedColor : DARKGRAY);
    DrawText("Exit", exitX, exitY, 40, (selectedOption == 2) ? selectedColor : DARKGRAY);

    // Draw copyright text at the bottom right
    const char* copyrightText = "(c) 2025 Alexander Chabowski";
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    int textWidth = MeasureText(copyrightText, 20);
    int textX = screenWidth - textWidth - 10;
    int textY = screenHeight - 30;
    DrawText(copyrightText, textX, textY, 20, LIGHTGRAY);
}

void MainMenuState::DrawStars()
{
    for (const auto& star : stars)
    {
        DrawPixel(static_cast<int>(star.x), static_cast<int>(star.y), WHITE);
    }
}

void MainMenuState::Unload()
{
    UnloadMusicStream(backgroundMusic);
    CloseAudioDevice();
}

void MainMenuState::OnExit()
{
}

void MainMenuState::CalculatePositionsAndValues(float time)
{
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    // Pre-calculate menu option positions
    int startGameWidth = MeasureText("Start Game", 40);
    int optionsWidth = MeasureText("Options", 40);
    int exitWidth = MeasureText("Exit", 40);

    startGameX = (screenWidth - startGameWidth) / 2;
    optionsX = (screenWidth - optionsWidth) / 2;
    exitX = (screenWidth - exitWidth) / 2;

    titleX = (screenWidth - MeasureText("rKern", 80)) / 2;
    titleY = screenHeight / 3;

    startGameY = titleY + 120;
    optionsY = startGameY + 60;
    exitY = optionsY + 60;

    spaceshipX = spaceshipBaseX + 120.0f * sin(time * 2.0f);
    spaceshipY = 100.0f; // Position the spaceship at the top of the screen

    // Adjust the ship vertices to point downwards
    shipTop = {spaceshipX, spaceshipY + 60.0f};
    shipLeft = {spaceshipX - 30.0f, spaceshipY + 20.0f};
    shipRight = {spaceshipX + 30.0f, spaceshipY + 20.0f};

    flameLength = 20.0f + sin(time * 10.0f) * 20.0f;
}

Vector2 MainMenuState::CalculateFlameEnd(Vector2 start, float angle, float length)
{
    return {static_cast<float>(start.x + cos(angle) * length), static_cast<float>(start.y + sin(angle) * length)};
}

Color MainMenuState::CalculateFlameColor(int flameIndex, int numFlames, float time, bool isLeft)
{
    unsigned char pulse = static_cast<unsigned char>(127 * (1 + sin(time * (isLeft ? 10.0f : 20.0f))));
    unsigned char gradient = static_cast<unsigned char>(69 + 186 * (flameIndex / static_cast<float>(numFlames)));
    return Color{0, gradient, 255, pulse};
}

void MainMenuState::TogglePause()
{
    paused = !paused;
}