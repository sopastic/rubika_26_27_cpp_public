#pragma once

#include "Entity.h"

template <typename C>
inline C* Entity::GetComponent() const
{
    if (!std::is_base_of<IComponent, C>())
        return nullptr;

    for (auto& component : m_components)
    {
        if (dynamic_cast<C*>(component))
        {
            return reinterpret_cast<C*>(component);
        }
    }

    return nullptr;
}

template<typename C>
inline C* Entity::AddComponent()
{
    if (!std::is_base_of<IComponent, C>())
        return nullptr;

    if (GetComponent<C>())
        return nullptr;

    C* component = new C(*this);
    m_components.push_back(component);
    return component;
}