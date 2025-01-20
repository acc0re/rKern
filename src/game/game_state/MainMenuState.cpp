// src/game/game_state/MainMenuState.cpp
#include "game/game_state/MainMenuState.h"
#include "game/game_state/PlayState.h"
#include "Game.h"
#include "raylib.h"
#include <vector>
#include <cstdlib>
#include <cmath>

MainMenuState::MainMenuState(Game& game) : game(game), spaceship(GetScreenWidth() / 2.0f, 100.0f)
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
        PlaySound(switchSound);
        previousOption = selectedOption;
    }

    if (IsKeyPressed(KEY_SPACE))
    {
        if (selectedOption == 0)
        {
            StopMusicStream(backgroundMusic);
            game.GetGameStateHandler().ChangeState(std::make_unique<PlayState>(game));
            return;
        }
        else if (selectedOption == 2)
        {
            game.Shutdown();
        }
    }

    UpdateStars(deltaTime);
    UpdateMusicStream(backgroundMusic);

    spaceship.Update(GetTime());
    CalculatePositionsAndValues(GetTime());
}

void MainMenuState::Draw()
{
    ClearBackground(BLACK);
    DrawStars();

    spaceship.Draw();

    float time = GetTime();
    Color selectedColor = {0, 0, 255, static_cast<unsigned char>(127 * (1 + sin(time * 5.0f)))};

    DrawText("rKern", titleX, titleY, 80, LIGHTGRAY);
    DrawText("Start Game", startGameX, startGameY, 40, (selectedOption == 0) ? selectedColor : DARKGRAY);
    DrawText("Options", optionsX, optionsY, 40, (selectedOption == 1) ? selectedColor : DARKGRAY);
    DrawText("Exit", exitX, exitY, 40, (selectedOption == 2) ? selectedColor : DARKGRAY);

    const char* copyrightText = "(c) 2025 Alexander Chabowski";
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    int textWidth = MeasureText(copyrightText, 20);
    int textX = screenWidth - textWidth - 10;
    int textY = screenHeight - 30;
    DrawText(copyrightText, textX, textY, 20, LIGHTGRAY);
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

void MainMenuState::UpdateStars(float dt)
{
    for (auto& star : stars)
    {
        star.y -= star.speed * dt * 100;
        if (star.y < 0)
        {
            star.x = static_cast<float>(rand() % GetScreenWidth());
            star.y = static_cast<float>(GetScreenHeight());
            star.speed = static_cast<float>((rand() % 100) / 10.0f + 1.0f);
        }
    }
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
}

void MainMenuState::TogglePause()
{
    paused = !paused;
}