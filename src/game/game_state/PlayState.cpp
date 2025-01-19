// src/game/game_state/PlayState.cpp
#include "game/game_state/PlayState.h"
#include "Game.h"
#include "raylib.h"

PlayState::PlayState(Game& game) : game(game) {}

void PlayState::Init() {
    // Initialize game play elements here
}

void PlayState::Update(float deltaTime) {
    // Update game play elements here
}

void PlayState::Draw() {
    ClearBackground(RAYWHITE);
    DrawText("Play State", 10, 10, 20, DARKGRAY);
}

void PlayState::Unload() {
    // Unload game play elements here
}

void PlayState::OnExit() {
    // Handle any cleanup when exiting the state
}

GameStateHandler& Game::GetGameStateHandler() {
    return gameStateHandler;
}