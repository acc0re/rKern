#ifndef GAMESTATEHANDLER_H
#define GAMESTATEHANDLER_H

#include "raylib.h"
#include <vector>
#include <memory>

// Abstrakte Klasse für verschiedene Spielzustände
class GameState {
public:
    virtual ~GameState() = default;

    virtual void Init() = 0;           // Initialisiert den Zustand
    virtual void Update(float deltaTime) = 0; // Logik des Zustands
    virtual void Draw() = 0;           // Zeichnen des Zustands
    virtual void Unload() = 0;         // Ressourcen freigeben, wenn der Zustand verlassen wird
    virtual void OnExit() = 0;         // Aktionen, wenn man den Zustand verlässt
};

// Der GameStateHandler, der die Zustände verwaltet
class GameStateHandler {
public:
    void ChangeState(std::unique_ptr<GameState> newState);
    void PushState(std::unique_ptr<GameState> newState);
    void PopState();

    void Init();
    void Update(float deltaTime);
    void Draw();
    void Unload();

private:
    std::vector<std::unique_ptr<GameState>> stateStack;
};

#endif // GAMESTATEHANDLER_H
