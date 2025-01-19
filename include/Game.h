#ifndef GAME_HPP
#define GAME_HPP

#include <raylib.h>
#include <rlImGui.h>
#include <imgui.h>
#include "engine/gui/manager/GuiManager.h"

class Game {
public:
    Game();
    ~Game();

    void Run();

private:
    void Init();
    void Update(float deltaTime);
    void Render();
    void Shutdown();

    GuiManager guiManager;
};

#endif // GAME_HPP