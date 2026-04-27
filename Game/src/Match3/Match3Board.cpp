#include "Match3/Match3Board.h"

#include <cstdlib>
#include <cmath>

void Match3Board::Init(int width, int height)
{
    m_width = width;
    m_height = height;
    m_score = 0;

    m_grid.clear();
    m_grid.resize(m_height);

    for (int y = 0; y < m_height; ++y)
    {
        m_grid[y].resize(m_width);

        for (int x = 0; x < m_width; ++x)
        {
            m_grid[y][x].type = RandomCandy();
            m_grid[y][x].marked = false;
        }
    }
}

bool Match3Board::Swap(int x1, int y1, int x2, int y2)
{
    if (!IsInside(x1, y1) || !IsInside(x2, y2))
    {
        return false;
    }

    if (!AreNeighbors(x1, y1, x2, y2))
    {
        return false;
    }

    Match3Tile temp = m_grid[y1][x1];
    m_grid[y1][x1] = m_grid[y2][x2];
    m_grid[y2][x2] = temp;

    if (!FindMatches())
    {
        temp = m_grid[y1][x1];
        m_grid[y1][x1] = m_grid[y2][x2];
        m_grid[y2][x2] = temp;

        return false;
    }

    return true;
}

bool Match3Board::FindMatches()
{
    ClearMarks();

    bool foundMatch = false;

    for (int y = 0; y < m_height; ++y)
    {
        int count = 1;

        for (int x = 1; x < m_width; ++x)
        {
            CandyType current = m_grid[y][x].type;
            CandyType previous = m_grid[y][x - 1].type;

            if (current != CandyType::Empty && current == previous)
            {
                count++;
            }
            else
            {
                if (count >= 3)
                {
                    foundMatch = true;

                    for (int i = 0; i < count; ++i)
                    {
                        m_grid[y][x - 1 - i].marked = true;
                    }
                }

                count = 1;
            }
        }

        if (count >= 3)
        {
            foundMatch = true;

            for (int i = 0; i < count; ++i)
            {
                m_grid[y][m_width - 1 - i].marked = true;
            }
        }
    }

    for (int x = 0; x < m_width; ++x)
    {
        int count = 1;

        for (int y = 1; y < m_height; ++y)
        {
            CandyType current = m_grid[y][x].type;
            CandyType previous = m_grid[y - 1][x].type;

            if (current != CandyType::Empty && current == previous)
            {
                count++;
            }
            else
            {
                if (count >= 3)
                {
                    foundMatch = true;

                    for (int i = 0; i < count; ++i)
                    {
                        m_grid[y - 1 - i][x].marked = true;
                    }
                }

                count = 1;
            }
        }

        if (count >= 3)
        {
            foundMatch = true;

            for (int i = 0; i < count; ++i)
            {
                m_grid[m_height - 1 - i][x].marked = true;
            }
        }
    }

    return foundMatch;
}

void Match3Board::ResolveMatches()
{
    RemoveMatches();
    ApplyGravity();
    Refill();
}

void Match3Board::RemoveMatches()
{
    for (int y = 0; y < m_height; ++y)
    {
        for (int x = 0; x < m_width; ++x)
        {
            if (m_grid[y][x].marked)
            {
                m_grid[y][x].type = CandyType::Empty;
                m_grid[y][x].marked = false;
                m_score += 10;
            }
        }
    }
}

void Match3Board::ApplyGravity()
{
    for (int x = 0; x < m_width; ++x)
    {
        int emptyY = m_height - 1;

        for (int y = m_height - 1; y >= 0; --y)
        {
            if (m_grid[y][x].type != CandyType::Empty)
            {
                m_grid[emptyY][x] = m_grid[y][x];

                if (emptyY != y)
                {
                    m_grid[y][x].type = CandyType::Empty;
                    m_grid[y][x].marked = false;
                }

                emptyY--;
            }
        }
    }
}

void Match3Board::Refill()
{
    for (int y = 0; y < m_height; ++y)
    {
        for (int x = 0; x < m_width; ++x)
        {
            if (m_grid[y][x].type == CandyType::Empty)
            {
                m_grid[y][x].type = RandomCandy();
                m_grid[y][x].marked = false;
            }
        }
    }
}

CandyType Match3Board::GetCandy(int x, int y) const
{
    if (!IsInside(x, y))
    {
        return CandyType::Empty;
    }

    return m_grid[y][x].type;
}

bool Match3Board::IsMarked(int x, int y) const
{
    if (!IsInside(x, y))
    {
        return false;
    }

    return m_grid[y][x].marked;
}

int Match3Board::GetWidth() const
{
    return m_width;
}

int Match3Board::GetHeight() const
{
    return m_height;
}

int Match3Board::GetScore() const
{
    return m_score;
}

bool Match3Board::IsInside(int x, int y) const
{
    return x >= 0 && x < m_width && y >= 0 && y < m_height;
}

bool Match3Board::AreNeighbors(int x1, int y1, int x2, int y2) const
{
    int dx = std::abs(x1 - x2);
    int dy = std::abs(y1 - y2);

    return dx + dy == 1;
}

CandyType Match3Board::RandomCandy() const
{
    int value = std::rand() % 5;

    switch (value)
    {
    case 0:
        return CandyType::Red;
    case 1:
        return CandyType::Blue;
    case 2:
        return CandyType::Green;
    case 3:
        return CandyType::Yellow;
    case 4:
        return CandyType::Purple;
    default:
        return CandyType::Red;
    }
}

void Match3Board::ClearMarks()
{
    for (int y = 0; y < m_height; ++y)
    {
        for (int x = 0; x < m_width; ++x)
        {
            m_grid[y][x].marked = false;
        }
    }
}