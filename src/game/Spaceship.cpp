#include "game/Spaceship.h"
#include <cmath>

Spaceship::Spaceship(float baseX, float baseY) : baseX(baseX), baseY(baseY) {}

void Spaceship::Update(float dt)
{
    x = baseX + 120.0f * sin(dt * 2.0f);
    y = baseY;

    top = {x, y + 60.0f};
    left = {x - 30.0f, y + 20.0f};
    right = {x + 30.0f, y + 20.0f};

    flameLength = 20.0f + sin(dt * 10.0f) * 20.0f;
}

void Spaceship::Draw() const
{
    DrawTriangleLines(top, left, right, LIGHTGRAY);

    int numFlames = 3;
    for (int i = 0; i < numFlames; ++i)
    {
        float angleOffset = (i - numFlames / 2.0f) * 0.2f;

        float leftAngle = (PI / 0.75f) - angleOffset;
        Vector2 flameEnd = CalculateFlameEnd(left, leftAngle, flameLength);
        Color leftFlameColor = CalculateFlameColor(i, numFlames, GetTime(), true);
        DrawLineEx(left, flameEnd, 2.0f, leftFlameColor);

        float rightAngle = (PI / 0.6f) + angleOffset;
        flameEnd = CalculateFlameEnd(right, rightAngle, flameLength);
        Color rightFlameColor = CalculateFlameColor(i, numFlames, GetTime(), false);
        DrawLineEx(right, flameEnd, 2.0f, rightFlameColor);
    }
}

Vector2 Spaceship::CalculateFlameEnd(Vector2 start, float angle, float length) const
{
    return {static_cast<float>(start.x + cos(angle) * length), static_cast<float>(start.y + sin(angle) * length)};
}

Color Spaceship::CalculateFlameColor(int flameIndex, int numFlames, float time, bool isLeft) const
{
    unsigned char pulse = static_cast<unsigned char>(127 * (1 + sin(time * (isLeft ? 10.0f : 20.0f))));
    unsigned char gradient = static_cast<unsigned char>(69 + 186 * (flameIndex / static_cast<float>(numFlames)));
    return Color{0, gradient, 255, pulse};
}