#include "SceneMgr.h"

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
    if (ImGui::BeginTable("Logs##LogConsole", 3, ImGuiTableFlags_Resizable | ImGuiTableFlags_NoSavedSettings | ImGuiTableFlags_Borders))
    {
        ImGui::TableSetupColumn("Name");
        ImGui::TableSetupColumn("Entities");
        ImGui::TableHeadersRow();
        ImGui::TableNextRow();

        for (const sSceneInfo& info : ScenesInfo)
        {
            ImVec4 color = ImVec4(1, 0.58, 0.77, 1);
            ImGui::TableSetColumnIndex(0);
            
            ImGui::TextColored(color, info.Name.c_str());
            ImGui::TableSetColumnIndex(1);
            for (std::string e : info.EntitiesName)
            {
                ImGui::Text(e.c_str());
            }
            ImGui::TableNextRow();
        }

        ImGui::EndTable();
    }
#endif
}
