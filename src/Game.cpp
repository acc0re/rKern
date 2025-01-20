#include "Game.h"

Game::Game() {
    Init();
}

Game::~Game() {
    Shutdown();
}

void Game::Init() {
    SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_FULLSCREEN_MODE);
    InitWindow(1920, 1080, "rKern");
    SetTargetFPS(60);

    rlImGuiSetup(true);

    gameStateHandler.ChangeState(std::make_unique<MainMenuState>(*this));
}

void Game::Update(float deltaTime) {
    gameStateHandler.Update(deltaTime);
}

void Game::Render() {
    BeginDrawing();
    ClearBackground(BLACK);

    guiManager.Render();

    gameStateHandler.Draw();

    EndDrawing();
}

void Game::Shutdown() {
    rlImGuiShutdown();
    CloseWindow();
}

void Game::Run() {
    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();
      //  stateManager.HandleInput(this);
        Update(deltaTime);
        Render();
    }
}

GameStateHandler& Game::GetGameStateHandler() {
    return gameStateHandler;
}