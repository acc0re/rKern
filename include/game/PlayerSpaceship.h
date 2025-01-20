// include/game/PlayerSpaceship.h
#ifndef PLAYERSPACESHIP_H
#define PLAYERSPACESHIP_H

#include "Spaceship.h"

class PlayerSpaceship : public Spaceship {
public:
    PlayerSpaceship(float baseX, float baseY);
    void Update(float dt) override;
    void Draw() const;
};

#endif // PLAYERSPACESHIP_H