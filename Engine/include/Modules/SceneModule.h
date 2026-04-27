#pragma once
#include <vector>
#include <memory>
#include <functional>

#include "Core/Module.h"
#include "Core/Scene.h"
#include "TimeModule.h"
#include "WindowModule.h"

class SceneModule final : public Module
{
public:
    SceneModule();
    ~SceneModule() override;

    void Start() override;
    void Render() override;
    void Update() override;
    void Awake() override;
    void Destroy() override;
    void Finalize() override;
    void OnDebug() override;
    void OnDebugSelected() override;
    void OnDisable() override;
    void OnEnable() override;
    void OnGUI() override;
    void PostRender() override;
    void PreRender() override;
    void Present() override;

    template <typename T>
    Scene* SetScene();

    Scene* activeScene = nullptr;

    const std::vector<std::unique_ptr<Scene>>& GetScenesList() const;

    template <typename SceneType> requires IsScene<SceneType>
    SceneType* CreateScene();

    template <typename SceneType> requires IsScene<SceneType>
    Scene* GetSceneByType() const;
    Scene* GetSceneByName(const std::string& _scene_name) const;

    template <typename SceneType> requires IsScene<SceneType>
    bool DeleteSceneByType();
    bool DeleteSceneByName(const std::string& _scene_name) const;

    void DeleteAllScenes() const;
    std::function<void()> onPresent;
private:
    void DeleteMarkedScenes();

    std::vector<std::unique_ptr<Scene>> scenes;


    WindowModule* windowModule = nullptr;
    TimeModule* timeModule = nullptr;

    Scene* nextFrameScene = nullptr;
};

#include "SceneModule.inl"
