#ifndef PLAYERSPACESHIP_H
#define PLAYERSPACESHIP_H

#include "Spaceship.h"
#include "game/Laser.h"
#include <raylib.h>
#include "raymath.h"
#include <cmath>

class PlayerSpaceship : public Spaceship {
public:
    // Constructor and Destructor
    PlayerSpaceship(float baseX, float baseY);
    ~PlayerSpaceship();

    // Update method for game logic
    void Update(float dt) override;

    // Draw method to render the spaceship
    void Draw();

    // Methods for shooting lasers
    void ShootLaser(float angle);
    void ShootLaserStraightDown();   // Shoots the laser straight down
    void DrawLaserLine(Vector2 start, float angle, float endY); // Draws the laser line with start point, angle, and Y endpoint

    // Load and unload game resources
    void LoadContent();
    void UnloadContent();

private:
    // Movement speed of the spaceship
    float moveSpeed = 500.0f;

    // Laser cooldown time and current cooldown state
    float cooldownTime = 0.5f;
    float currentCooldown = 0.0f;

    // Shooting flags and laser instance
    bool isShootingLeft = false;
    bool isShootingRight = false;
    bool isShootingDown = false;
    bool laserActive = false;
    Laser laser;

    // Sound resource for laser shot
    Sound laserSound;

    // Length of the flame effect
    float laserLength;
};

#endif // PLAYERSPACESHIP_H
