#pragma once
#include <functional>
#include <vector>

namespace TowerDefence {

    // File d'attente de créations à exécuter hors de toute itération
    class SpawnQueue
    {
    public:
        static SpawnQueue& Get()
        {
            static SpawnQueue instance;
            return instance;
        }

        void Push(std::function<void()> fn)
        {
            pending.push_back(std::move(fn));
        }

        void Flush()
        {
            // Copie locale pour éviter les re-entrances
            auto toExecute = std::move(pending);
            pending.clear();
            for (auto& fn : toExecute)
                fn();
        }

    private:
        std::vector<std::function<void()>> pending;
    };

}