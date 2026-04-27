#pragma once

namespace BulletHell {

    struct BHGameState
    {
        static BHGameState& Get()
        {
            static BHGameState instance;
            return instance;
        }

        int   score = 0;
        int   lives = 3;
        int   wave = 1;
        bool  gameOver = false;
        bool  victory = false;

        void Reset()
        {
            score = 0;
            lives = 3;
            wave = 1;
            gameOver = false;
            victory = false;
        }
    };

}