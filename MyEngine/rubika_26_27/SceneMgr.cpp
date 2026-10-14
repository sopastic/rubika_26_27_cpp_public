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
    if (ImGui::BeginTable("Logs##LogConsole", 3, ImGuiTableFlags_Resizable | ImGuiTableFlags_NoSavedSettings | ImGuiTableFlags_Borders))
    {
        ImGui::TableSetupColumn("Name");
        ImGui::TableSetupColumn("Entities");
        ImGui::TableSetupColumn("Actions");
        ImGui::TableHeadersRow();
        ImGui::TableNextRow();

        for (Scene* scene : m_scenes)
        {
            ImVec4 color = ImVec4(1, 0.58, 0.77, 1);
            
            if (scene == m_activeScene)
            {
                color = ImVec4(1, 1, 0, 1);
            }
            ImGui::TableSetColumnIndex(0);
            
            ImGui::TextColored(color, scene->getName().c_str());
            ImGui::TableSetColumnIndex(1);
            for (Entity* entity : scene->getEntities())
            {
                ImGui::Text(entity->getName().c_str());
            }
            ImGui::TableSetColumnIndex(2);
            static char str1[128] = "";
            ImGui::InputTextWithHint(std::format("name input##{}", scene->getName()).c_str(), "enter entity name here", str1, IM_COUNTOF(str1));
            if (ImGui::Button(std::format("Add Entity##{}", scene->getName()).c_str()))
            {
                Entity* entity = new Entity(str1);
                scene->AddEntity(entity);
                std::cout << "Entity added" << std::endl;
            }
            if (ImGui::Button(std::format("Make Active scene##{}", scene->getName()).c_str()))
            {
                SetActiveScene(scene->getName());
            }
            ImGui::TableNextRow();
        }

        ImGui::EndTable();
    }
#endif
}
