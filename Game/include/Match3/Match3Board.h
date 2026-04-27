#pragma once

#include <vector>
#include <cmath>


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

    CandyType GetCandy(int x, int y) const;

    int GetWidth() const;
    int GetHeight() const;
    int GetScore() const;

    bool Swap(int x1, int y1, int x2, int y2);
    bool FindMatches();
    void ClearMarks();
    void RemoveMatches();
    void ApplyGravity();
    void Refill();
    void ResolveMatches();

private:
    int m_width = 8;
    int m_height = 8;
    int m_score = 0;

    bool AreNeighbors(int x1, int y1, int x2, int y2) const;

    std::vector<std::vector<Match3Tile>> m_grid;


private:
    bool IsInside(int x, int y) const;
    CandyType RandomCandy() const;
};