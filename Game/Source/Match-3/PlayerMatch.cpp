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

        if (draggingX < -20.f)
        {
            Logger::Log(ELogLevel::Debug, "Drag vers la gauche detecte");

            // Action match-3 ici
            isDragging = false;
        }

        else if (draggingX > 20.f)
        {
            Logger::Log(ELogLevel::Debug, "Drag vers la droite detecte");

            // Action match-3 ici
            isDragging = false;
        }

        else if (draggingY < -20.f)
        {
            Logger::Log(ELogLevel::Debug, "Drag vers le haut detecte");

            // Action match-3 ici
            isDragging = false;
        }

        else if (draggingY > 20.f)
        {
            Logger::Log(ELogLevel::Debug, "Drag vers le bas detecte");

            // Action match-3 ici
            isDragging = false;
        }
    }

    if (InputModule::GetMouseButtonUp(sf::Mouse::Button::Left))
    {
        isDragging = false;
        selectedTile = nullptr;
    }
}

SquareCollider* PlayerMatch::ReturnTileName(int id)
{
	return sceneOwner->FindGameObject("Tile" + std::to_string(id))->GetComponent<SquareCollider>();
}
