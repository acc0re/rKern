// include/game/game_state/PlayState.h
#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include "GameStateHandler.h"
#include "game/PlayerSpaceship.h"
#include "game/Star.h" // Include the common Star header
#include <vector>

class Game;

class PlayState : public GameState {
public:
    PlayState(Game& game);

    void Init() override;
    void Update(float deltaTime) override;
    void Draw() override;
    void Unload() override;
    void OnExit() override;
    void GenerateTerrain();

private:
    Game& game;
    PlayerSpaceship playerSpaceship;
    std::vector<Star> stars;
    std::vector<float> terrainHeights;

    void InitStars(int count);
    void UpdateStars(float deltaTime);
    void DrawStars();
};

#endif // PLAYSTATE_H