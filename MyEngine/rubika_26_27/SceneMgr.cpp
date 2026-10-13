#include "SceneMgr.h"

#include <iostream>
#include <ostream>

#include "Logger.h"

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
            
        }
    }
}

void SceneMgr::SetActiveScene(const std::string& sceneName)
{
    if (m_activeScene == nullptr)
    {
        for (Scene* scene : m_scenes)
        {
            if (scene->getName() == sceneName)
            {
                m_activeScene = scene;
                Logger::Info("Active Scene is now '" + m_activeScene->getName() + "'");
                return;
            }
        }
        Logger::Warning("No Scene with name '" + sceneName + "'");
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