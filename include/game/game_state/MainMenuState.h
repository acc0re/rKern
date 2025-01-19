#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "GameStateHandler.h"
#include "raylib.h"
#include <vector>

struct Star {
    float x, y, speed;
};

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
    float spaceshipBaseX;
    Music backgroundMusic;
    Sound switchSound;

    int titleX, titleY;
    int startGameX, startGameY;
    int optionsX, optionsY;
    int exitX, exitY;
    float spaceshipX, spaceshipY;
    float flameLength;
    Vector2 shipTop, shipLeft, shipRight;

    void InitStars(int count);
    void UpdateStars(float deltaTime);
    void DrawStars();
    void CalculatePositionsAndValues(float time);
    void TogglePause();
    Vector2 CalculateFlameEnd(Vector2 start, float angle, float length);
    Color CalculateFlameColor(int flameIndex, int numFlames, float time, bool isLeft);
};

#endif // MAINMENUSTATE_H