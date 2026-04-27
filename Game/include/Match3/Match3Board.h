#pragma once

#include <vector>

enum class CandyType
{
    Red,
    Blue,
    Green,
    Yellow,
    Purple,
    Empty
};

struct Match3Tile
{
    CandyType type = CandyType::Empty;
    bool marked = false;
};

class Match3Board
{
public:
    void Init(int width, int height);

    bool Swap(int x1, int y1, int x2, int y2);

    bool FindMatches();
    void ResolveMatches();

    void RemoveMatches();
    void ApplyGravity();
    void Refill();

    CandyType GetCandy(int x, int y) const;
    bool IsMarked(int x, int y) const;

    int GetWidth() const;
    int GetHeight() const;
    int GetScore() const;

private:
    int m_width = 8;
    int m_height = 8;
    int m_score = 0;

    std::vector<std::vector<Match3Tile>> m_grid;

private:
    bool IsInside(int x, int y) const;
    bool AreNeighbors(int x1, int y1, int x2, int y2) const;

    CandyType RandomCandy() const;
    void ClearMarks();
};