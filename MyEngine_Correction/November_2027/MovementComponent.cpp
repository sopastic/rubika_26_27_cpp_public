#include "MovementComponent.h"

#include <iostream>
#include <ostream>

#include "Entity.h"
#include "Logger.h"
#include "ImGui/imgui.h"

MovementComponent::MovementComponent(Entity& entity) : IComponent(entity)
{
    
}

void MovementComponent::Start()
{
    Transform = GetEntity().GetComponent<TransformComponent>();
}

void MovementComponent::Update(float fDeltaTime)
{}

void MovementComponent::Destroy()
{}

void MovementComponent::MoveX(float direction)
{
    sf::Vector2f worldPos = Transform->GetWorldPosition();
}

void MovementComponent::MoveY(float direction)
{
    
    sf::Vector2f newPos = Transform->GetWorldPosition() + sf::Vector2f(0, direction);
    Transform->SetWorldPosition(newPos);
    std::cout << "Movement" << std::endl;
}

void MovementComponent::DrawDebug()
{
#ifdef _USE_IMGUI
    
#endif
}