#include "Match-3/PlayerMatch.h"

void PlayerMatch::Start()
{
	sceneOwner = GetOwner()->GetScene();
	ownerCollider = GetOwner()->GetComponent<SquareCollider>();
}

void PlayerMatch::Update(float deltaTime)
{
	float mousePositionX = InputModule::GetMousePosition().x;
	float mousePositionY = InputModule::GetMousePosition().y;

	GetOwner()->SetPosition({ mousePositionX - 40.f, mousePositionY - 40.f });

    if (InputModule::GetMouseButtonDown(sf::Mouse::Button::Left))
    {
        clickPosition = InputModule::GetMousePosition();
        
        for (int i = 0; i < BOARD_SIZE; i++)
        {
            for (int j = 0; j < BOARD_SIZE; j++)
            {
                SquareCollider* tileCollider = ReturnTileName(i + j);

                if (ownerCollider->IsColliding(*ownerCollider, *tileCollider))
                {
                    index_I = i;
                    index_J = j;
                    selectedTile = tileCollider;
                    isDragging = true;
                    Logger::Log(ELogLevel::Debug, "Tile selectionnee : {},{}", i, j);
                }
            }
        }
    }

    if (isDragging && InputModule::GetMouseButton(sf::Mouse::Button::Left))
    {
        Maths::Vector2i currentMouse = InputModule::GetMousePosition();
        float draggingX = currentMouse.x - clickPosition.x;
        float draggingY = currentMouse.y - clickPosition.y;

        Logger::Log(ELogLevel::Debug, "dragging X = {}", draggingX);
        Logger::Log(ELogLevel::Debug, "dragging Y = {}", draggingY);

        if (draggingX < -20.f && index_I > 0)
        {
            Logger::Log(ELogLevel::Debug, "Drag vers la gauche detecte");

            swapPosition(index_I - 1, index_J);
            // Action match-3 ici
            isDragging = false;
        }

        else if (draggingX > 20.f && index_I < BOARD_SIZE)
        {
            Logger::Log(ELogLevel::Debug, "Drag vers la droite detecte");

            swapPosition(index_I + 1, index_J);
            // Action match-3 ici
            isDragging = false;
        }

        else if (draggingY < -20.f && index_J > 0)
        {
            Logger::Log(ELogLevel::Debug, "Drag vers le haut detecte");

            swapPosition(index_I, index_J - 1);
            // Action match-3 ici
            isDragging = false;
        }

        else if (draggingY > 20.f && index_J < BOARD_SIZE)
        {
            Logger::Log(ELogLevel::Debug, "Drag vers le bas detecte");

            swapPosition(index_I, index_J + 1);
            // Action match-3 ici
            isDragging = false;
        }
    }

    if (InputModule::GetMouseButtonUp(sf::Mouse::Button::Left))
    {
        isDragging = false;
        selectedTile = nullptr;
        index_I = 0;
        index_J = 0;
    }
}

SquareCollider* PlayerMatch::ReturnTileName(int id)
{
	return sceneOwner->FindGameObject("Tile" + std::to_string(id))->GetComponent<SquareCollider>();
}

void PlayerMatch::swapPosition(int i, int j)
{
    GameObject* TileMatchComponent = GetOwner()->GetScene()->FindGameObject("TileMatch");
    GameObject* TileSelected = TileMatchComponent->GetComponent<Match_3::TileMatch>()->GetTiles()[index_I][index_J];
    GameObject* otherTile = TileMatchComponent->GetComponent<Match_3::TileMatch>()->GetTiles()[i][j]; // On récupère l'autre tile (celle à inverser).
    
    Maths::Vector2f TileSelectedPosition = TileSelected->GetPosition();
    Maths::Vector2f otherTilePosition = otherTile->GetPosition();
    Maths::Vector2f tempPosition = TileSelectedPosition;

    // Swap des GameObjects

    tempPosition = TileSelectedPosition;
    TileSelectedPosition = otherTilePosition;
    otherTilePosition = tempPosition;

    // Swap dans le tableau

    GameObject* temp = TileSelected;
    TileSelected = otherTile;
    otherTile = temp;

}
