// include/game/MenuSpaceship.h
#ifndef MENUSPACESHIP_H
#define MENUSPACESHIP_H

#include "Spaceship.h"

class MenuSpaceship : public Spaceship {
public:
    MenuSpaceship(float baseX, float baseY);

    void Update(float time) override;
};

#endif // MENUSPACESHIP_H