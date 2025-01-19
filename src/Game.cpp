#include "Game.h"

Game::Game() {
    Init();
}

Game::~Game() {
    Shutdown();
}

void Game::Init() {
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(1280, 720, "rKern");
    SetTargetFPS(60);

    rlImGuiSetup(true);

    guiManager.AddView([this]() {
        ImGui::Text("Main menu");
        if (ImGui::Button("Play")) {
        }

        if (ImGui::Button("Exit")) {
            //Close the game
            this->Shutdown();
        }
    });
}

void Game::Update(float deltaTime) {
}

void Game::Render() {
    BeginDrawing();
    ClearBackground(BLACK);

    guiManager.Render();

    EndDrawing();
}

void Game::Shutdown() {
    rlImGuiShutdown();
    CloseWindow();
}

void Game::Run() {
    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();
        Update(deltaTime);
        Render();
    }
}