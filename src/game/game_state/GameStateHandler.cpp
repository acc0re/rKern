#include "game/game_state/GameStateHandler.h"

// Wechseln zu einem neuen Zustand und entfernen des alten
void GameStateHandler::ChangeState(std::unique_ptr<GameState> newState) {
    if (!stateStack.empty()) {
        stateStack.back()->OnExit(); // Wenn es einen Zustand gibt, verlasse diesen
        stateStack.pop_back();
    }

    stateStack.push_back(std::move(newState));
    stateStack.back()->Init();
}

// Einen Zustand auf den Stack legen
void GameStateHandler::PushState(std::unique_ptr<GameState> newState) {
    if (!stateStack.empty()) {
        stateStack.back()->OnExit(); // Verlasse den aktuellen Zustand
    }

    stateStack.push_back(std::move(newState));
    stateStack.back()->Init();
}

// Den obersten Zustand vom Stack entfernen
void GameStateHandler::PopState() {
    if (!stateStack.empty()) {
        stateStack.back()->Unload();  // Ressourcen des aktuellen Zustands freigeben
        stateStack.pop_back();        // Entfernen des Zustands
    }

    if (!stateStack.empty()) {
        stateStack.back()->Init();   // Den vorherigen Zustand wieder initialisieren
    }
}

// Initialisiere den ersten Zustand (wird in `main` aufgerufen)
void GameStateHandler::Init() {
    if (!stateStack.empty()) {
        stateStack.back()->Init();
    }
}

// Update des aktuellen Zustands
void GameStateHandler::Update(float dt) {
    if (!stateStack.empty()) {
        stateStack.back()->Update(dt);
    }
}

// Zeichnen des aktuellen Zustands
void GameStateHandler::Draw() {
    if (!stateStack.empty()) {
        stateStack.back()->Draw();
    }
}

// Ressourcen freigeben, wenn der Handler entladen wird
void GameStateHandler::Unload() {
    if (!stateStack.empty()) {
        stateStack.back()->Unload();
    }
}
