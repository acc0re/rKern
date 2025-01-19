#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "GameStateHandler.h"
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
    int selectedOption;
    std::vector<Star> stars;
    float spaceshipBaseX;
    Music backgroundMusic; // New member variable for the music stream
    void InitStars(int count);
    void UpdateStars(float deltaTime);
    void DrawStars();
};

#endif // MAINMENUSTATE_H