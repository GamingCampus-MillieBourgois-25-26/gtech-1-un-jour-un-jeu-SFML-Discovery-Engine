#pragma once
#include <functional>
#include <vector>

namespace TowerDefence {

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
            auto toExecute = std::move(pending);
            pending.clear();
            for (auto& fn : toExecute)
                fn();
        }

    private:
        std::vector<std::function<void()>> pending;
    };

}

inline void FlushGlobalSpawnQueue()
{
    TowerDefence::SpawnQueue::Get().Flush();
}