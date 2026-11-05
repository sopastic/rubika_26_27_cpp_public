#pragma once
#include <SFML/System/Vector2.hpp>

#include "Entity.h"

class Obstacle : public Entity
{
public:
    Obstacle(std::string friendlyName = "");
    
    void Start() override;
    
private:
    sf::Vector2f Pos = sf::Vector2f(rand() % 800 + 1, rand() % 600 + 1);
};
