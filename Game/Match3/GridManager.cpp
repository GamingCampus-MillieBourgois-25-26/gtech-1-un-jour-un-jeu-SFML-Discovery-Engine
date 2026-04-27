#include "GridManager.h"
#include "Core/GameObject.h"
#include "Modules/InputModule.h"
#include <iostream>
#include <ctime>

namespace Match3 {

    void GridManager::Start() {
        float gridWidth = width * cellSize;
        float gridHeight = height * cellSize;

        float screenWidth = 1500.f;
        float screenHeight = 800.f;

        float startX = (screenWidth - gridWidth) / 2.f;
        float startY = (screenHeight - gridHeight) / 2.f;

        GetOwner()->SetPosition({ startX, startY });

        InitializeGrid();
    }

    void GridManager::Update(float _delta_time) {
        if (currentState == GameState::IDLE) {
            HandleInput();
        }
        else {
            timer += _delta_time;
            if (timer >= 0.2f) {
                timer = 0.f;
                ProcessGameLoop();
            }
        }
    }

    void GridManager::ProcessGameLoop() {
        if (currentState == GameState::CHECKING) {
            if (CheckMatches()) {
                std::cout << "[Logic] Match detecte, passage au nettoyage." << std::endl;
                ClearMatches(); 
                UpdateVisuals(); 
                currentState = GameState::REFILLING;
            }
            else {
                currentState = GameState::IDLE;
            }
        }
        else if (currentState == GameState::REFILLING) {
            ApplyGravity();
            RefillGrid();
            UpdateVisuals();

            std::cout << "[Logic] Remplissage termine. Verification des combos..." << std::endl;
            //DebugPrintGrid();

            currentState = GameState::CHECKING;
        }
    }

    void GridManager::InitializeGrid() {
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
        grid.resize(width, std::vector<CandyType>(height, CandyType::EMPTY));

        for (int x = 0; x < width; ++x) {
            for (int y = 0; y < height; ++y) {
                CandyType newType;
                do {
                    newType = static_cast<CandyType>((std::rand() % (static_cast<int>(CandyType::COUNT) - 1)) + 1);
                } while (
                    (x >= 2 && grid[x - 1][y] == newType && grid[x - 2][y] == newType) ||
                    (y >= 2 && grid[x][y - 1] == newType && grid[x][y - 2] == newType)
                    );

                grid[x][y] = newType;
                SpawnCandyVisual(newType, x, y);
            }
        }
    }

    void GridManager::RefillGrid() {
        int countCreated = 0;
        for (int x = 0; x < width; ++x) {
            for (int y = 0; y < height; ++y) {
                if (grid[x][y] == CandyType::EMPTY) {
                    int randomType = (std::rand() % (static_cast<int>(CandyType::COUNT) - 1)) + 1;
                    grid[x][y] = static_cast<CandyType>(randomType);
                    countCreated++;
                }
            }
        }
        std::cout << "[Debug] Refill : " << countCreated << " nouvelles cases remplies." << std::endl;
    }

    void GridManager::HandleInput() {
        if (InputModule::GetMouseButtonDown(sf::Mouse::Button::Left)) {
            Maths::Vector2i mPos = InputModule::GetMousePosition();
            Maths::Vector2f origin = GetOwner()->GetPosition();

            float localX = static_cast<float>(mPos.x) - origin.x;
            float localY = static_cast<float>(mPos.y) - origin.y;

            int gx = static_cast<int>(std::floor(localX / cellSize));
            int gy = static_cast<int>(std::floor(localY / cellSize));

            if (gx >= 0 && gx < width && gy >= 0 && gy < height) {
                if (selectedTile.x == -1) {
                    selectedTile = Maths::Vector2i(gx, gy);
                    if (selectorVisual) {
                        selectorVisual->Enable();
                        Maths::Vector2f centerPos = GetWorldPosition(gx, gy);
                        float halfCell = cellSize / 2.f;
                        selectorVisual->SetPosition({ centerPos.x - halfCell, centerPos.y - halfCell });
                    }
                }
                else {
                    int diffX = std::abs(selectedTile.x - gx);
                    int diffY = std::abs(selectedTile.y - gy);

                    if ((diffX == 1 && diffY == 0) || (diffX == 0 && diffY == 1)) {
                        Swap(selectedTile, Maths::Vector2i(gx, gy));
                    }

                    selectedTile = Maths::Vector2i(-1, -1);
                    if (selectorVisual) selectorVisual->Disable();
                }
            }
        }
    }

    void GridManager::Swap(Maths::Vector2i a, Maths::Vector2i b) {
        CandyType temp = grid[a.x][a.y];
        grid[a.x][a.y] = grid[b.x][b.y];
        grid[b.x][b.y] = temp;

        if (!CheckMatches()) {
            grid[b.x][b.y] = grid[a.x][a.y];
            grid[a.x][a.y] = temp;
            std::cout << "Swap invalide !" << std::endl;
        }
        else {
            std::cout << "Swap valide, debut de la sequence de match." << std::endl;
            currentState = GameState::CHECKING;
        }
    }

    bool GridManager::CheckMatches() {
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width - 2; ++x) {
                CandyType type = grid[x][y];
                if (type != CandyType::EMPTY && grid[x + 1][y] == type && grid[x + 2][y] == type) return true;
            }
        }
        for (int x = 0; x < width; ++x) {
            for (int y = 0; y < height - 2; ++y) {
                CandyType type = grid[x][y];
                if (type != CandyType::EMPTY && grid[x][y + 1] == type && grid[x][y + 2] == type) return true;
            }
        }
        return false;
    }

    void GridManager::ClearMatches() {
        std::vector<std::vector<bool>> toDestroy(width, std::vector<bool>(height, false));

        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width - 2; ++x) {
                CandyType type = grid[x][y];
                if (type != CandyType::EMPTY && grid[x + 1][y] == type && grid[x + 2][y] == type) {
                    toDestroy[x][y] = toDestroy[x + 1][y] = toDestroy[x + 2][y] = true;
                }
            }
        }
        for (int x = 0; x < width; ++x) {
            for (int y = 0; y < height - 2; ++y) {
                CandyType type = grid[x][y];
                if (type != CandyType::EMPTY && grid[x][y + 1] == type && grid[x][y + 2] == type) {
                    toDestroy[x][y] = toDestroy[x][y + 1] = toDestroy[x][y + 2] = true;
                }
            }
        }

        for (int x = 0; x < width; ++x) {
            for (int y = 0; y < height; ++y) {
                if (toDestroy[x][y]) grid[x][y] = CandyType::EMPTY;
            }
        }
    }

    void GridManager::ApplyGravity() {
        for (int x = 0; x < width; ++x) {
            int emptySlot = height - 1;
            for (int y = height - 1; y >= 0; --y) {
                if (grid[x][y] != CandyType::EMPTY) {
                    if (y != emptySlot) {
                        grid[x][emptySlot] = grid[x][y];
                        grid[x][y] = CandyType::EMPTY;
                    }
                    emptySlot--;
                }
            }
        }
    }

    void GridManager::UpdateVisuals() {
        if (pool == nullptr) return;

        for (auto& pair : *pool) {
            for (GameObject* obj : pair.second) {
                obj->Disable();
            }
        }
        for (int x = 0; x < width; ++x) {
            for (int y = 0; y < height; ++y) {
                if (grid[x][y] != CandyType::EMPTY) {
                    SpawnCandyVisual(grid[x][y], x, y);
                }
            }
        }
    }

    void GridManager::SpawnCandyVisual(CandyType _type, int _x, int _y) {
        if (_type == CandyType::EMPTY || pool == nullptr) return;

        std::vector<GameObject*>& list = (*pool)[_type];
        for (GameObject* obj : list) {
            if (!obj->IsEnabled()) {
                obj->Enable();
                obj->SetPosition(GetWorldPosition(_x, _y));
                return;
            }
        }
    }

    Maths::Vector2f GridManager::GetWorldPosition(int x, int y) const {
        Maths::Vector2f origin = GetOwner()->GetPosition();
        return Maths::Vector2f(
            origin.x + (x * cellSize) + (cellSize / 2.f),
            origin.y + (y * cellSize) + (cellSize / 2.f)
        );
    }

    void GridManager::DebugPrintGrid() {
        std::cout << "--- Grille (Etat: " << (int)currentState << ") ---" << std::endl;
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                if (grid[x][y] == CandyType::EMPTY) std::cout << ". ";
                else std::cout << (int)grid[x][y] << " ";
            }
            std::cout << std::endl;
        }
    }
}