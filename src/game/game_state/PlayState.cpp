#include "game/game_state/PlayState.h"
#include "Game.h"
#include "raylib.h"
#include <cstdlib>

PlayState::PlayState(Game& game)
    : game(game), playerSpaceship(GetScreenWidth() / 2.0f, GetScreenHeight() / 4.0f) // Initialisierung der Position
{
}

void PlayState::Init()
{
    playerSpaceship.LoadContent();
    InitStars(100);
}

void PlayState::Update(float dt)
{
    playerSpaceship.Update(dt);
    UpdateStars(dt);
}

void PlayState::Draw()
{
    ClearBackground(BLACK);


    // Geländegenerierung und Zeichnung nur einmalig beim Start
    if (terrainHeights.empty())
    {
        GenerateTerrain();
    }

    DrawStars();

    // Zeichne das gespeicherte Gelände
    int groundY = GetScreenHeight(); // Unterer Rand des Bildschirms
    for (int x = 0; x < terrainHeights.size(); ++x)
    {
        DrawLine(x, groundY, x, groundY - static_cast<int>(terrainHeights[x]), GRAY);
    }


    playerSpaceship.Draw();

    DrawText("Play State", 10, 10, 20, DARKGRAY);
}

void PlayState::Unload()
{
    playerSpaceship.UnloadContent();
}

void PlayState::OnExit()
{
}

void PlayState::InitStars(int count)
{
    stars.clear();
    for (int i = 0; i < count; ++i)
    {
        Star star;
        star.x = static_cast<float>(rand() % GetScreenWidth());
        star.y = static_cast<float>(rand() % GetScreenHeight());
        star.speed = static_cast<float>((rand() % 100) / 10.0f + 1.0f);
        stars.push_back(star);
    }
}

void PlayState::UpdateStars(float dt)
{
    for (auto& star : stars)
    {
        star.y -= star.speed * dt * 100;
        if (star.y < 0)
        {
            star.x = static_cast<float>(rand() % GetScreenWidth());
            star.y = static_cast<float>(GetScreenHeight());
            star.speed = static_cast<float>((rand() % 100) / 10.0f + 1.0f);
        }
    }
}

void PlayState::DrawStars()
{
    for (const auto& star : stars)
    {
        DrawPixel(static_cast<int>(star.x), static_cast<int>(star.y), WHITE);
    }
}

void PlayState::GenerateTerrain()
{
    int terrainMaxHeight = static_cast<int>(GetScreenHeight() * 0.15f);
    // Maximalhöhe des Geländes (15% des Bildschirms)
    int groundY = GetScreenHeight(); // Unterer Rand des Bildschirms (unterster Punkt)

    terrainHeights.clear(); // Lösche alte Höhenwerte

    float lastHeight = 30.0f; // Startwert auf mindestens 30 setzen
    terrainHeights.push_back(lastHeight); // Setze den ersten Punkt auf den minimalen Wert

    // Erzeuge das Gelände von links nach rechts
    for (int x = 1; x < GetScreenWidth(); ++x)
    {
        // Zufällige Höhenvariation für ein gleichmäßigeres Gelände
        float variation = (rand() % 10 - 5) * 0.3f; // Kleinere Variation zwischen -1.5 und 1.5

        // Berechne die neue Höhe des Geländes
        float newHeight = lastHeight + variation;

        // Stelle sicher, dass die neue Höhe nicht unter dem Minimalwert von 30 fällt
        if (newHeight < 30.0f)
        {
            newHeight = 30.0f;
        }
        else if (newHeight > terrainMaxHeight)
        {
            newHeight = terrainMaxHeight;
        }

        lastHeight = newHeight;
        terrainHeights.push_back(newHeight); // Speichere die Höhe
    }
}
