#include "Scene.h"

#include <iostream>
#include <ostream>

#include "Logger.h"

void Scene::Start()
{
    for (Entity* e : m_entities)
    {
        e->Start();
    }
}

void Scene::Update(float fDeltaTime)
{
    for (Entity* e : m_entities)
    {
        e->Update(fDeltaTime);
    }
}

void Scene::Destroy()
{
    for (Entity* e : m_entities)
    {
        e->Destroy();
    }
}

void Scene::AddEntity(Entity* entity)
{
    if (m_entities.empty())
    {
        m_entities.push_back(entity);
    }
    else
    {
        for (Entity* e : m_entities)
        {
            if (e == entity)
            {
                break;
            }
            m_entities.push_back(entity);
            break;
            
        }
    }
}

void Scene::RemoveEntity(Entity* entity)
{
    if (!m_entities.empty())
    {
        for (auto it = m_entities.begin(); it != m_entities.end(); it++)
        {
            if (*it == entity)
            {
                m_entities.erase(it);
                break;
            }
        }
    }
}
