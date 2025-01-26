#ifndef LASER_H
#define LASER_H

#include <raylib.h>
#include <cmath>

struct Laser
{
    Vector2 position;
    Vector2 direction;
    float speed;
    bool active;

    // Draw method for rendering the laser line
    void DrawLaserLine(Vector2 start, float angle, float endY) {
        // Calculate the direction based on the angle
        Vector2 direction = {cos(angle), sin(angle)};

        // Calculate the distance the laser needs to travel vertically to reach the target Y
        float deltaY = endY - start.y;

        // Calculate the laser length to reach the target Y position
        float laserLength = deltaY / direction.y;

        // Calculate the horizontal distance (deltaX) for the laser line
        float deltaX = laserLength * direction.x;

        // Determine the endpoint of the laser
        Vector2 end = {start.x + deltaX, endY};

        // Create a back-and-forth effect based on time (half second period)
        float time = GetTime();  // Get the current time
        float intensity = (sin(time * 3.14159f) * 0.5f + 0.5f); // Sinus function oscillates between 0 and 1

        // Set the red color to oscillate between 150 and 255 (slightly less than full intensity)
        int redIntensity = (int)(150 + intensity * 105);  // 150 to 255 range

        // Create the laser color (pure red with oscillating intensity)
        Color laserColor = Color{(unsigned char)redIntensity, 0, 0, 255}; // Red color with varying intensity

        // Draw the laser line from the start to the calculated end point with the dynamic color
        DrawLineEx(start, end, 3.0f, laserColor);
    }

};

#endif // LASER_H
