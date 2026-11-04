#pragma once
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "IComponent.h"
#include "IDrawable.h"
#include "TransformComponent.h"

class DynamicColliderComponent : public IComponent
{
public:
    DynamicColliderComponent(Entity& entity);

    void Start() override;
    void Update(float fDeltaTime) override;
    void Destroy() override;
    
    const char* GetName() const override { return "DynamicColliderComponent"; }
    void DrawDebug() override;
    
    void Draw(sf::RenderWindow& window) const;
    
    sf::Vector2f GetOffset() const { return Offset; }
    sf::Vector2f GetPosition() const { return Position; }
    sf::Vector2f GetSize() const { return Size; }
    
    void SetSize(sf::Vector2f size) { Size = size; }
    void SetOffset(sf::Vector2f offset) { Offset = offset; }
    
protected:
    TransformComponent* Transform;
    sf::RectangleShape Shape;
    sf::Vector2<float> Position = sf::Vector2(0.0f, 0.0f);
    sf::Vector2<float> Size = sf::Vector2(5.0f, 5.0f);
    sf::FloatRect Collider;
    sf::Vector2<float> Offset = sf::Vector2(0.0f, 0.0f);
    
    void UpdateCollider();
};
