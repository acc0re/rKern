#include "game/PlayerSpaceship.h"

// Constructor initializes the spaceship position and laser state
PlayerSpaceship::PlayerSpaceship(float baseX, float baseY) : Spaceship(baseX, baseY)
{
    x = baseX;
    y = baseY;
    laser.active = false; // Laser is initially inactive
}

// Destructor to unload resources when the object is destroyed
PlayerSpaceship::~PlayerSpaceship()
{
    UnloadContent();
}

// Load sound and other resources for the spaceship
void PlayerSpaceship::LoadContent()
{
    laserSound = LoadSound("sfx/lazer.wav"); // Load laser sound
}

// Unload sound and clean up resources
void PlayerSpaceship::UnloadContent()
{
    UnloadSound(laserSound); // Unload laser sound
    CloseAudioDevice(); // Close audio device to release resources
}

// Update method for handling the spaceship's movement and shooting logic
void PlayerSpaceship::Update(float dt)
{
    // Update spaceship movement if not currently shooting
    if (!isShootingDown && !isShootingLeft && !isShootingRight)
    {
        float diagonalFactor = 1.0f;
        if (IsKeyDown(KEY_RIGHT) && IsKeyDown(KEY_UP) || IsKeyDown(KEY_RIGHT) && IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_LEFT) && IsKeyDown(KEY_UP) || IsKeyDown(KEY_LEFT) && IsKeyDown(KEY_DOWN)) {
            diagonalFactor = 0.7071f; // Normalisieren für diagonale Bewegung (1/sqrt(2))
        }

        if (IsKeyDown(KEY_RIGHT)) x += moveSpeed * dt * diagonalFactor; // Move right
        if (IsKeyDown(KEY_LEFT)) x -= moveSpeed * dt * diagonalFactor; // Move left
        if (IsKeyDown(KEY_UP)) y -= moveSpeed * dt * diagonalFactor; // Move up
        if (IsKeyDown(KEY_DOWN)) y += moveSpeed * dt * diagonalFactor; // Move down

        // Keep the spaceship within the screen bounds
        if (x < 0) x = 0;
        if (x > GetScreenWidth()) x = static_cast<float>(GetScreenWidth());
        if (y < 0) y = 0;
        if (y > GetScreenHeight()) y = static_cast<float>(GetScreenHeight());
    }

    // Update the spaceship's top and sides for drawing
    top = {x, y - 30.0f};
    left = {x - 15.0f, y + 15.0f};
    right = {x + 15.0f, y + 15.0f};

    // Update the flame length for the spaceship's thrust effect
    flameLength = 20.0f + sin(dt * 10.0f) * 20.0f;

    // Handle laser cooldown and deactivation
    if (isShootingDown || isShootingLeft || isShootingRight)
    {
        currentCooldown -= dt;
        if (currentCooldown <= 0.0f)
        {
            isShootingDown = false;
            isShootingLeft = false;
            isShootingRight = false;
            laserActive = false;
            laser.active = false; // Deactivate laser
        }
    }

    // Handle laser shooting based on player input
    if ((IsKeyPressed(KEY_S) || IsKeyPressed(KEY_A) || IsKeyPressed(KEY_D)) && !isShootingDown && !isShootingLeft && !
        isShootingRight)
    {
        if (IsKeyPressed(KEY_S))
            isShootingDown = true; // Shoot straight down
        else if (IsKeyPressed(KEY_A))
            isShootingRight = true;// Shoot down-left
        else if (IsKeyPressed(KEY_D))
            isShootingLeft = true; // Shoot down-right

        laserActive = true;
        currentCooldown = cooldownTime;

        // Play laser sound effect
        PlaySound(laserSound);
    }
}

// Draw the spaceship and its flame effects
void PlayerSpaceship::Draw()
{
    if (isShootingDown)
        laser.DrawLaserLine({x, y + 40}, PI / 2, GetScreenHeight() * 0.7f); // Shoot straight down

    if (isShootingRight)
        laser.DrawLaserLine({x, y + 40}, PI / 1.5f, GetScreenHeight() * 0.7f); // Shoot right with a narrower angle

    if (isShootingLeft)
        laser.DrawLaserLine({x, y + 40}, PI / 3.0f, GetScreenHeight() * 0.7f); // Shoot left with a narrower angle
    // Define spaceship's triangle vertices
    Vector2 p1 = {static_cast<float>(x), static_cast<float>(y + 40)};
    Vector2 p2 = {static_cast<float>(x - 15), static_cast<float>(y + 10)};
    Vector2 p3 = {static_cast<float>(x + 15), static_cast<float>(y + 10)};

    // Draw spaceship triangle outline
    DrawTriangleLines(p1, p2, p3, LIGHTGRAY);

    // Draw the flames as lines behind the spaceship
    int numFlames = 3;
    for (int i = 0; i < numFlames; ++i)
    {
        // Offset the flame angles based on its position
        float angleOffset = (i - numFlames / 2.0f) * 0.2f;

        // Draw the left flame with color variations
        float leftAngle = (PI / 0.75f) - angleOffset;
        Vector2 flameEnd = CalculateFlameEnd(p2, leftAngle, flameLength);
        Color leftFlameColor = CalculateFlameColor(i, numFlames, GetTime(), true);
        DrawLineEx(p2, flameEnd, 2.0f, leftFlameColor);

        // Draw the right flame with color variations
        float rightAngle = (PI / 0.6f) + angleOffset;
        flameEnd = CalculateFlameEnd(p3, rightAngle, flameLength);
        Color rightFlameColor = CalculateFlameColor(i, numFlames, GetTime(), false);
        DrawLineEx(p3, flameEnd, 2.0f, rightFlameColor);
    }
}

