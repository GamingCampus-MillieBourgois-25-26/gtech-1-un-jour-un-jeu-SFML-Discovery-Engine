#pragma once

#include <vector>
#include <optional>
#include "Core/Component.h"
#include "Maths/Vector2.h"

// Types de bonbons
enum class CandyType {
    EMPTY = 0,
    RED,
    BLUE,
    GREEN,
    YELLOW,
    PURPLE,
    COUNT
};

class GridManager : public Component
{
public:
    void Start() override;
    void Update(float _delta_time) override;


    // Pour savoir quoi dessiner et où
    CandyType GetCandyAt(int x, int y) const;
    Maths::Vector2f GetWorldPosition(int x, int y) const;

    // Pour savoir si une animation est en cours
    bool IsProcessing() const { return isAnimating; }

    // Logique Match-3
    void Swap(Maths::Vector2i posA, Maths::Vector2i posB);
    bool CheckMatches();
    void RemoveMatches();
    void ApplyGravity();
    void RefillGrid();

private:
    void HandleInput();
    Maths::Vector2i ScreenToGrid(Maths::Vector2i mousePos);

    int width = 8;
    int height = 8;
    float cellSize = 64.f;
    bool isAnimating = false;

    std::vector<std::vector<CandyType>> grid;
    std::optional<Maths::Vector2i> selectedTile;
};