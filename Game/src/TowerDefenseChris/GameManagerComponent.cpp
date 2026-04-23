#include "TowerDefenseChris/GameManagerComponent.h"

#include <iostream>

int GameManagerComponent::baseHP = 3;
int GameManagerComponent::enemiesKilled = 0;
int GameManagerComponent::enemiesEscaped = 0;
bool GameManagerComponent::gameOver = false;
bool GameManagerComponent::victory = false;

void GameManagerComponent::OnGUI()
{
    static int lastBaseHP = -1;
    static int lastKilled = -1;
    static int lastEscaped = -1;
    static bool lastGameOver = false;
    static bool lastVictory = false;

    if (baseHP != lastBaseHP || enemiesKilled != lastKilled || enemiesEscaped != lastEscaped
        || gameOver != lastGameOver || victory != lastVictory)
    {
        std::cout << "Base HP: " << baseHP
            << " | Kills: " << enemiesKilled
            << " | Escaped: " << enemiesEscaped << "\n";

        if (gameOver)
            std::cout << "DEFAITE\n";

        if (victory)
            std::cout << "VICTOIRE\n";

        lastBaseHP = baseHP;
        lastKilled = enemiesKilled;
        lastEscaped = enemiesEscaped;
        lastGameOver = gameOver;
        lastVictory = victory;
    }
}