#pragma once
#include <SFML/Window/Keyboard.hpp>

#include "DebugMgr.h"
#include "InputAction.h"

class InputMgr : public IDebugable
{
public:
    void Init();
    void Start();
    void Update(float deltaTime);
    void Shut();
    
    InputAction* CreateInputAction(const std::string& actionName);
    void RemoveInputAction(const std::string& actionName);
    
    void BindKeyToInputAction(sf::Keyboard::Key key, const std::string& actionName);
    void UnbindKeyToInputAction(sf::Keyboard::Key key, const std::string& actionName);

    
    InputAction* GetInputAction(const std::string& actionName);
    
    
    virtual void DrawDebug() override;
    
protected:
    std::unordered_map<std::size_t, InputAction*> InputActions;
    
};
