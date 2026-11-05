#include "Obstacle.h"
#include "DynamicColliderComponent.h"
#include "RenderComponent.h"
#include "SpriteDrawable.h"
#include "TransformComponent.h"

Obstacle::Obstacle(std::string friendlyName) : Entity(friendlyName)
{
    AddTag(ENTITY_TAG_STATIC);
}

void Obstacle::Start()
{
    TransformComponent* tc = AddComponent<TransformComponent>();
    {
        tc->SetWorldPosition(Pos);
    }
    
    AddComponent<DynamicColliderComponent>();
    
    Entity::Start();
}
