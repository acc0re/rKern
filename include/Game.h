#ifndef GAME_HPP
#define GAME_HPP

#include <raylib.h>
#include <rlImGui.h>
#include <imgui.h>
#include "game/game_state/GameStateHandler.h"
#include "engine/gui/manager/GuiManager.h"
#include "game/game_state/MainMenuState.h"

class Game {
public:
    Game();
    ~Game();

    void Run();
    static void Shutdown();
    GameStateHandler& GetGameStateHandler();

private:
    void Init();
    void Update(float deltaTime);
    void Render();

    GameStateHandler gameStateHandler;
    GuiManager guiManager;
};

#endif // GAME_HPP