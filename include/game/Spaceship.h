// include/game/Spaceship.h
#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "raylib.h"

class Spaceship {
public:
    Spaceship(float baseX, float baseY);

    virtual void Update(float time) = 0;
    void Draw() const;

protected:
    float baseX, baseY;
    float x, y;
    float flameLength;
    Vector2 top, left, right;

    Vector2 CalculateFlameEnd(Vector2 start, float angle, float length) const;
    Color CalculateFlameColor(int flameIndex, int numFlames, float time, bool isLeft) const;
};

#endif // SPACESHIP_H