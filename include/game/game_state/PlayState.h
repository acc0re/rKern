// include/game/game_state/PlayState.h
#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include "GameStateHandler.h"

class Game;

class PlayState : public GameState {
public:
    PlayState(Game& game);

    void Init() override;
    void Update(float deltaTime) override;
    void Draw() override;
    void Unload() override;
    void OnExit() override;

private:
    Game& game;
};

#endif // PLAYSTATE_H