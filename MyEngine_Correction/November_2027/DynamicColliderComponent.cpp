#include "DynamicColliderComponent.h"
#include "Entity.h"
#include "ImGui/imgui.h"

DynamicColliderComponent::DynamicColliderComponent(Entity& entity) : IComponent(entity)
{
    Size = sf::Vector2(10.0f, 10.0f);
    Collider = sf::FloatRect(Position, Size);
    Shape = sf::RectangleShape(Size);
}

void DynamicColliderComponent::Start()
{
    Transform = GetEntity().GetComponent<TransformComponent>();
    Shape.setFillColor(sf::Color::Transparent);
    Shape.setOutlineColor(sf::Color::Green);
    Shape.setOutlineThickness(2.0f);
    UpdateCollider();
}

void DynamicColliderComponent::Update(float fDeltaTime)
{
    UpdateCollider();
}

void DynamicColliderComponent::Destroy()
{}

void DynamicColliderComponent::UpdateCollider()
{
    Position = Transform->GetWorldPosition();
    Collider.position = Position + Offset;
    Collider.size = Size;
    Shape.setPosition(Collider.position);
    Shape.setSize(Collider.size);
}

void DynamicColliderComponent::Draw(sf::RenderWindow& window) const
{
    window.draw(Shape);
}

void DynamicColliderComponent::DrawDebug()
{
#ifdef _USE_IMGUI
    if (ImGui::InputFloat2("Offset", &Offset.x))
        UpdateCollider();
    if (ImGui::InputFloat2("Size", &Size.x))
        UpdateCollider();
#endif
}