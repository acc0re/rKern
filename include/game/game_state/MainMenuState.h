// include/game/game_state/MainMenuState.h
#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "GameStateHandler.h"
#include "game/MenuSpaceship.h"
#include "raylib.h"
#include "game/Star.h" // Include the common Star header
#include <vector>

class Game;

class MainMenuState : public GameState {
public:
    MainMenuState(Game& game);

    void Init() override;
    void Update(float deltaTime) override;
    void Draw() override;
    void Unload() override;
    void OnExit() override;

private:
    Game& game;
    bool paused;
    int selectedOption;
    std::vector<Star> stars;
    MenuSpaceship spaceship;
    Music backgroundMusic;
    Sound switchSound;

    int titleX, titleY;
    int startGameX, startGameY;
    int optionsX, optionsY;
    int exitX, exitY;

    void InitStars(int count);
    void UpdateStars(float dt);
    void DrawStars();
    void CalculatePositionsAndValues(float time);
    void TogglePause();
};

#endif // MAINMENUSTATE_H