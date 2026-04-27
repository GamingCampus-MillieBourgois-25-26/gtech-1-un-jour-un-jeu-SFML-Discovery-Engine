#include "SpawnFlusher.h"
#include "SpawnQueue.h"

namespace TowerDefence {
    void SpawnFlusher::Present()
    {
        SpawnQueue::Get().Flush();
    }
}
