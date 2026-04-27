#include "Core/Scene.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <algorithm>

#include "Core/GameObject.h"

Scene::Scene(const std::string& _name, const bool _enabled_at_start)
{
    name = _name;
    enabled = _enabled_at_start;
}

// --- CYCLE DE VIE ---

void Scene::Awake() const
{
    for (size_t i = 0; i < gameObjects.size(); ++i)
    {
        if (gameObjects[i]) gameObjects[i]->Awake();
    }
}

void Scene::Start() const
{
    for (size_t i = 0; i < gameObjects.size(); ++i)
    {
        if (gameObjects[i]) gameObjects[i]->Start();
    }
}

void Scene::PreRender() const
{
    if (!enabled) return;

    // 1. GESTION DES CRÉATIONS (On laisse au début pour que l'objet existe dès cette frame)
    if (!pendingObjects.empty()) {
        for (auto& obj : pendingObjects) {
            obj->Awake();
            obj->Start();
            gameObjects.push_back(std::move(obj));
        }
        pendingObjects.clear();
    }

    // 2. MISE À JOUR DES OBJETS
    for (size_t i = 0; i < gameObjects.size(); ++i)
    {
        if (gameObjects[i]) gameObjects[i]->Update(_delta_time);
    }

    // 3. GESTION DES DESTRUCTIONS (DÉPLACÉ ICI)
    // En supprimant ici, l'objet ne sera PAS présent pour la phase de Render() qui suit !
    if (!objectsToDestroy.empty()) {
        for (const auto* target : objectsToDestroy) {
            std::erase_if(gameObjects, [target](const std::unique_ptr<GameObject>& obj) {
                return obj.get() == target;
                });
        }
        objectsToDestroy.clear();
    }
}

// --- RENDU ET GUI ---

void Scene::PreRender() const
void Scene::Render(sf::RenderWindow* _window) const
{
    for (size_t i = 0; i < gameObjects.size(); ++i)
    {
        game_object->Render(_window);
        if (gameObjects[i]) gameObjects[i]->PreRender();
    }
}

void Scene::Render(sf::RenderWindow* _window) const
void Scene::OnGUI() const
{
    for (size_t i = 0; i < gameObjects.size(); ++i)
    {
        game_object->OnGUI();
        if (gameObjects[i]) gameObjects[i]->Render(_window);
    }
}

void Scene::OnGUI() const
{
    for (size_t i = 0; i < gameObjects.size(); ++i)
    {
        if (gameObjects[i]) gameObjects[i]->OnGUI();
    }
}

void Scene::OnDebug() const
{
    for (size_t i = 0; i < gameObjects.size(); ++i)
    {
        if (gameObjects[i]) gameObjects[i]->OnDebug();
    }
}

void Scene::PostRender() const
{
    for (const auto& game_object : gameObjects)
    {
        game_object->PostRender();
    }
}

void Scene::Present()
void Scene::OnDebugSelected() const
{
    for (size_t i = 0; i < gameObjects.size(); ++i)
    {
        if (gameObjects[i]) gameObjects[i]->OnDebugSelected();
    }

    DeleteMarkedGameObjects();
}

void Scene::PostRender() const
{
    for (size_t i = 0; i < gameObjects.size(); ++i)
    {
        if (gameObjects[i]) gameObjects[i]->PostRender();
    }
}

void Scene::Present() const
{
    for (size_t i = 0; i < gameObjects.size(); ++i)
    {
        if (gameObjects[i]) gameObjects[i]->Present();
    }
}

// --- ÉTATS ET NETTOYAGE ---

void Scene::OnEnable() const
{
    for (size_t i = 0; i < gameObjects.size(); ++i)
    {
        if (gameObjects[i]) gameObjects[i]->OnEnable();
    }
}

void Scene::OnDisable() const
{
    for (size_t i = 0; i < gameObjects.size(); ++i)
    {
        if (gameObjects[i]) gameObjects[i]->OnDisable();
    }
}

void Scene::Destroy() const
{
    for (size_t i = 0; i < gameObjects.size(); ++i)
    {
        if (gameObjects[i]) gameObjects[i]->Destroy();
    }
}

void Scene::Finalize() const
{
    for (size_t i = 0; i < gameObjects.size(); ++i)
    {
        if (gameObjects[i]) gameObjects[i]->Finalize();
    }
}

// --- GESTION DES GAMEOBJECTS ---
const std::string& Scene::GetName() const
{
    return name;
}

GameObject* Scene::CreateGameObject(const std::string& _name)
{
    auto game_object = std::make_unique<GameObject>();
    game_object->SetName(_name);
    game_object->SetScene(this);

    game_object->Awake();
    game_object->OnEnable();
    game_object->Start();

    GameObject* raw_ptr = game_object.get();
    gameObjects.push_back(std::move(game_object));
    return raw_ptr;
    GameObject* rawPtr = game_object.get();
    pendingObjects.push_back(std::move(game_object));
    return rawPtr;
}

void Scene::DestroyGameObject(const GameObject* _game_object)
{
    if (!_game_object) return;
    objectsToDestroy.push_back(_game_object);
}

GameObject* Scene::FindGameObject(const std::string& _name) const
{
    for (const auto& game_object : gameObjects)
    {
        if (game_object->GetName() == _name) return game_object.get();
    }
    return nullptr;
}

// --- ACCESSEURS ET FLAGS ---

const std::string& Scene::GetName() const { return name; }

const std::vector<std::unique_ptr<GameObject>>& Scene::GetGameObjects() const { return gameObjects; }

void Scene::DestroyGameObject(const GameObject* _game_object)
{
    std::erase_if(gameObjects, [_game_object](const std::unique_ptr<GameObject>& _obj)
    {
        return _obj.get() == _game_object;
    });
}

void Scene::Enable()
{
    if (!enabled)
    {
        enabled = true;
        OnEnable();
    }
}

void Scene::Disable()
{
    if (enabled)
    {
        enabled = false;
        OnDisable();
    }
}

bool Scene::IsEnabled() const { return enabled; }

void Scene::MarkForDeletion()
{
    markedForDeletion = true;
    Disable();
}

bool Scene::IsMarkedForDeletion() const
{
    return markedForDeletion;
}

void Scene::DeleteMarkedGameObjects()
{
    std::erase_if(gameObjects, [](const std::unique_ptr<GameObject>& _game_object)
    {
        if (!_game_object->IsMarkedForDeletion())
            return false;

        _game_object->Destroy();
        _game_object->Finalize();

        Logger::Log(ELogLevel::Debug, "GameObject {} deleted.", _game_object->GetName());

        return true;
    });
}
bool Scene::IsMarkedForDeletion() const { return markedForDeletion; }