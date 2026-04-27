#pragma once

namespace TowerDefence {

    struct GameState
    {
        static GameState& Get()
        {
            static GameState instance;
            return instance;
        }

        int   playerHP = 20;
        int   money = 150;
        int   currentWave = 1;
        int   maxWaves = 3;
        bool  gameOver = false;
        bool  victory = false;

        void Reset()
        {
            playerHP = 20;
            money = 150;
            currentWave = 1;
            gameOver = false;
            victory = false;
        }
    };

}
