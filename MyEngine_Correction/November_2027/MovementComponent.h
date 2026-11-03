#pragma once
#include "IComponent.h"
#include "TransformComponent.h"

class MovementComponent : public IComponent
{
public:

    MovementComponent(Entity& entity);

    void Start() override;
    void Update(float fDeltaTime) override;
    void Destroy() override;
    
    void MoveX(float direction);
    void MoveY(float direction);

    const char* GetName() const override { return "MovementComponent"; }
    void DrawDebug() override;

private:
    float speed = 1.0f;
    TransformComponent* Transform;
    
};
