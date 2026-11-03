#include "InputMgr.h"

#include <iostream>
#include <ostream>

#include "Globals.h"
#include "Logger.h"

void InputMgr::Init()
{
    gData.DebugMgr->RegisterDebugableWindow("InputMgr", this);
}

void InputMgr::Start()
{
    
}

void InputMgr::Update(float deltaTime)
{
    for (auto it = InputActions.begin(); it != InputActions.end(); ++it)
    {
        for (sf::Keyboard::Key key : it->second->GetKeys())
        {
            if (sf::Keyboard::isKeyPressed(key))
            {
                std::cout << "Key pressed" << std::endl;
                it->second->SetValue(1.0f);
            }
            it->second->SetValue(0.0f);
        }
    }
}

void InputMgr::Shut()
{
    
}

InputAction* InputMgr::CreateInputAction(const std::string& actionName)
{
    std::size_t hash = std::hash<std::string>{}(actionName);
    const auto& it = InputActions.find(hash);
    if (it != InputActions.end())
    {
        Logger::Info("Input already exists");
        return nullptr;
    }
    InputAction* ia = new InputAction(actionName);
    InputActions.emplace(hash, ia);
    Logger::Info("Created input action.");
    return ia;
}

void InputMgr::RemoveInputAction(const std::string& actionName)
{
    std::size_t hash = std::hash<std::string>{}(actionName);
    const auto& it = InputActions.find(hash);
    if (it != InputActions.end())
    {
        InputActions.erase(it);
    }
}

InputAction* InputMgr::GetInputAction(const std::string& actionName)
{
    std::size_t hash = std::hash<std::string>{}(actionName);
    const auto& it = InputActions.find(hash);
    if (it != InputActions.end())
    {
        return it->second;
    }
    Logger::Warning("Input action doesn't exist. Returning nullptr.");
    return nullptr;
}

void InputMgr::BindKeyToInputAction(sf::Keyboard::Key key, const std::string& actionName)
{
    GetInputAction(actionName)->AddKey(key);
}

void InputMgr::UnbindKeyToInputAction(sf::Keyboard::Key key, const std::string& actionName)
{
    GetInputAction(actionName)->AddKey(key);
}




void InputMgr::DrawDebug()
{
    
}