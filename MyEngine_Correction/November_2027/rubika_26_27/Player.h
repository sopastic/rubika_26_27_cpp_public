#pragma once
#include "Entity.h"

class Player : public Entity
{
public:
    Player(std::string friendlyName = "");
    
    void Start() override;
};
