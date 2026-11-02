#include "Entity.h"
#include <RenderComponent.h>

#include "ImGui/imgui.h"

Entity::~Entity()
{
    for (const IComponent* component : m_components)
    {
        delete component;
    }

    m_components.clear();
}

void Entity::Start()
{
    for (IComponent* c : m_components)
    {
        c->Start();
    }
}

void Entity::Update(float fDeltaTime)
{
    for (IComponent* c : m_components)
    {
        c->Update(fDeltaTime);
    }
}
void Entity::Destroy()
{
    for (IComponent* c : m_components)
    {
        c->Destroy();
    }
}

void Entity::Draw(sf::RenderWindow& window) const
{
    RenderComponent* r = GetComponent<RenderComponent>();
    if (r)
    {
        r->Draw(window);
    }
}

void Entity::DrawDebug()
{
#ifdef _USE_IMGUI
    for (IComponent* c : m_components)
    {
        if (ImGui::TreeNode(c->GetName()))
        {
            c->DrawDebug();
            ImGui::TreePop();
        }
    }
#endif
}
