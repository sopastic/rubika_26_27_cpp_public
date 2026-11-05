#include "Player.h"
#include "DynamicColliderComponent.h"
#include "Globals.h"
#include "InputAction.h"
#include "MovementComponent.h"
#include "RenderComponent.h"
#include "SpriteDrawable.h"
#include "TransformComponent.h"
#include "InputMgr.h"

Player::Player(std::string friendlyName) : Entity(friendlyName)
{
    AddTag(ENTITY_TAG_PLAYER);
    AddTag(ENTITY_TAG_DYNAMIC);
}

void Player::Start()
{
    const char* texturePath = "../../../MyEngine/Ressources/IsaacSprite.png";
    gData.TextureMgr->LoadTexture(texturePath);
    
    TransformComponent* tc = AddComponent<TransformComponent>();
    {
        tc->SetWorldPosition(sf::Vector2f(100.f, 100.f));
    }

    RenderComponent* rc = AddComponent<RenderComponent>();
    {
        SpriteDrawable* bodySprite = rc->AddNewDrawable<SpriteDrawable>("Body", sf::Vector2f(2, 0), 0, sf::Vector2f(1, 1));
        bodySprite->SetVisibility(true);
        bodySprite->SetTexture(texturePath);
        bodySprite->SetAnimation("Body_Vertical");

        SpriteDrawable* headSprite = rc->AddNewDrawable<SpriteDrawable>("Head", sf::Vector2f(-2.5f, -20), 0, sf::Vector2f(1, 1));
        headSprite->SetVisibility(true);
        headSprite->SetTexture(texturePath);
        headSprite->SetAnimation("Head_Down");
    }
    MovementComponent* mc = AddComponent<MovementComponent>();
    {
        InputAction* up = gData.InputMgr->CreateInputAction("Up");
        InputAction* down = gData.InputMgr->CreateInputAction("Down");
        InputAction* left = gData.InputMgr->CreateInputAction("Left");
        InputAction* right = gData.InputMgr->CreateInputAction("Right");
    
        gData.InputMgr->BindKeyToInputAction(sf::Keyboard::Key::W, "Up");
        gData.InputMgr->BindKeyToInputAction(sf::Keyboard::Key::S, "Down");
        gData.InputMgr->BindKeyToInputAction(sf::Keyboard::Key::A, "Left");
        gData.InputMgr->BindKeyToInputAction(sf::Keyboard::Key::D, "Right");
    
        up->RegisterCallback("MoveUp", [mc](float __f) {mc->MoveY(-0.05);}, mc);
        down->RegisterCallback("MoveDown", [mc](float __f) {mc->MoveY(0.05);}, mc);
        left->RegisterCallback("MoveLeft", [mc](float __f) {mc->MoveX(-0.05);}, mc);
        right->RegisterCallback("MoveRight", [mc](float __f) {mc->MoveX(0.05);}, mc);
    }
    DynamicColliderComponent* dcc = AddComponent<DynamicColliderComponent>();
    {
        dcc->SetCollisionMask(ENTITY_TAG_STATIC);
    }
    
    Entity::Start();
}