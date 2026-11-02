#include "SceneMgr.h"

#include <format>
#include <iostream>
#include <ostream>

#include "Globals.h"
#include "Logger.h"

#ifdef _USE_IMGUI
#include <Imgui/imgui.h>
#endif

void SceneMgr::Start()
{
    if (m_activeScene != nullptr)
    {
        m_activeScene->Start();
    }
}

void SceneMgr::Update(float fDeltaTime)
{
    if (m_activeScene != nullptr)
    {
        m_activeScene->Update(fDeltaTime);
    }
}

void SceneMgr::Destroy()
{
    if (m_activeScene != nullptr)
    {
        m_activeScene->Destroy();
    }
}

void SceneMgr::AddScene(Scene* scene)
{
    if (m_scenes.empty())
    {
        m_scenes.push_back(scene);
        Logger::Info("First Scene added");
    }
    else
    {
        for (Scene* s : m_scenes)
        {
            if (s == scene)
            {
                Logger::Warning("Scene alr exists");
                break;
            }
            m_scenes.push_back(scene);
            Logger::Info("Scene added");
            break;
            
        }
    }
}

void SceneMgr::SetActiveScene(const std::string& sceneName)
{
    if (m_activeScene == nullptr)
    {
        m_activeScene = GetScene(sceneName);
        Logger::Info("Active Scene is now '" + m_activeScene->getName() + "'");
    }
    else
    {
        Scene* oldActiveScene = m_activeScene;
        for (Scene* scene : m_scenes)
        {
            if (scene->getName() == sceneName)
            {
                m_activeScene = scene;
                Logger::Info("Active Scene is now '" + m_activeScene->getName() + "'");
                oldActiveScene->Destroy();
                return;
            }
        }
        Logger::Warning("No Scene with name '" + sceneName + "'");
    }
}

Scene* SceneMgr::GetScene(const std::string& sceneName)
{
    for (Scene* scene : m_scenes)
    {
        if (scene->getName() == sceneName)
        {
            return scene;
        }
    }
    Logger::Warning("No Scene with name '" + sceneName + "'");
}

void SceneMgr::ShowDebug()
{
    if (m_scenes.empty())
    {
        Logger::Warning("No scenes.");
    }
    else
    {
        for (Scene* s : m_scenes)
        {
            SceneDebug(s);
        }
    }
}

void SceneMgr::Draw(sf::RenderWindow& window) const
{
    if (!m_activeScene)
    {
        return;
    }

    m_activeScene->Draw(window);
}

void SceneMgr::Init()
{
    gData.DebugMgr->RegisterDebugableWindow("Scene", this);
}

void SceneMgr::Shut()
{
    gData.DebugMgr->UnregisterDebugableWindow("Scene");
}

void SceneMgr::PushNewSceneInfo(const sSceneInfo& sceneInfo)
{
    ScenesInfo.push_back(sceneInfo);
}

void SceneMgr::SceneDebug(Scene* scene)
{
    sSceneInfo info;
    info.Scene = scene;
    info.Name = scene->getName();
    for (Entity* e : scene->getEntities())
    {
        info.EntitiesName.push_back(e->getName());
    }
    gData.SceneMgr->PushNewSceneInfo(info);
}

void SceneMgr::DrawDebug()
{
#ifdef _USE_IMGUI

    for (auto it : m_scenes)
    {
        ImGui::PushID(it.second);

        ImVec4 color = it.second == ActiveScene ? ImVec4(0, 200, 0, 255) : ImVec4(255, 255, 255, 255);
        ImGui::PushStyleColor(ImGuiCol_Text, color);

        bool bTree = ImGui::TreeNode("%s (%lld)", it.second->GetName().c_str(), it.second->GetHash());
        ImGui::PopStyleColor();
        if (bTree)
        {
            it.second->DrawDebug();
            ImGui::TreePop();
        }

        ImGui::PopID();
    }

#endif
}
