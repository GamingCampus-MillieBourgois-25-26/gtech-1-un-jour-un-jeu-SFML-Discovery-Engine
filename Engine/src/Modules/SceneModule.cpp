#include "Modules/SceneModule.h"

#include <ranges>

#include "ModuleManager.h"



SceneModule::SceneModule() : Module()
{
}

SceneModule::~SceneModule()
{
    DeleteAllScenes();
    DeleteMarkedScenes();
}

void SceneModule::Start()
{
    Module::Start();

    timeModule = moduleManager->GetModule<TimeModule>();
    windowModule = moduleManager->GetModule<WindowModule>();

    for (const auto& scene : scenes)
    {
        scene->Start();
    }
}

void SceneModule::Render()
{
    Module::Render();

    if (activeScene)
        activeScene->Render(windowModule->GetWindow());
}

void SceneModule::Update()
{
    Module::Update();

    if (activeScene)
        activeScene->Update(timeModule->GetDeltaTime());
}

void SceneModule::Awake()
{
    Module::Awake();

    for (const auto& scene : scenes)
    {
        scene->Awake();
    }
}

void SceneModule::Destroy()
{
    Module::Destroy();

    for (const auto& scene : scenes)
    {
        scene->Destroy();
    }
}

void SceneModule::Finalize()
{
    Module::Finalize();

    for (const auto& scene : scenes)
    {
        scene->Finalize();
    }
}

void SceneModule::OnDebug()
{
    Module::OnDebug();

    if (activeScene)
        activeScene->OnDebug();
}

void SceneModule::OnDebugSelected()
{
    Module::OnDebugSelected();

    if (activeScene)
        activeScene->OnDebugSelected();
}

void SceneModule::OnDisable()
{
    Module::OnDisable();

    for (const auto& scene : scenes)
    {
        scene->OnDisable();
    }
}

void SceneModule::OnEnable()
{
    Module::OnEnable();

    for (const auto& scene : scenes)
    {
        scene->OnEnable();
    }
}

void SceneModule::OnGUI()
{
    Module::OnGUI();

    if (activeScene)
        activeScene->OnGUI();
}

void SceneModule::PostRender()
{
    Module::PostRender();

    if (activeScene)
        activeScene->PostRender();
}

void SceneModule::PreRender()
{
    Module::PreRender();

    if (activeScene)
        activeScene->PreRender();
}

void SceneModule::Present()
{
    Module::Present();

    if (activeScene)
        activeScene->Present();

    if (onPresent)
        onPresent();

    if (nextFrameScene != nullptr)
    {
        if (activeScene != nullptr)
            activeScene->MarkForDeletion();
        activeScene = nextFrameScene;
        nextFrameScene = nullptr;
        activeScene->Awake();
        activeScene->Start();
    }

    DeleteMarkedScenes();
}

const std::vector<std::unique_ptr<Scene>>& SceneModule::GetScenesList() const
{
    return scenes;
}

Scene* SceneModule::GetSceneByName(const std::string& _scene_name) const
{
    auto condition = [_scene_name](const std::unique_ptr<Scene>& _scene)
        {
            return _scene->GetName() == _scene_name;
        };

    if (const auto it = std::ranges::find_if(scenes, condition); it != scenes.end())
    {
        return it->get();
    }

    Logger::Log(ELogLevel::Warning, "Scene with name {} not found.", _scene_name);

    return nullptr;
}

bool SceneModule::DeleteSceneByName(const std::string& _scene_name) const
{
    if (Scene* scene = GetSceneByName(_scene_name))
    {
        scene->MarkForDeletion();
        return true;
    }

    return false;
}

void SceneModule::DeleteAllScenes() const
{
    for (const auto& scene : scenes)
    {
        scene->MarkForDeletion();
    }
}

void SceneModule::DeleteMarkedScenes()
{
    std::erase_if(scenes, [this](const std::unique_ptr<Scene>& _scene)
        {
            if (!_scene->IsMarkedForDeletion())
                return false;

            if (activeScene == _scene.get())  
                activeScene = nullptr;

            _scene->Destroy();
            _scene->Finalize();

           

            return true;
        });
}