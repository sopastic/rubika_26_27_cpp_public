#include "InputMgr.h"

#include <iostream>
#include <ostream>

#include "Globals.h"
#include "Logger.h"
#include "ImGui/imgui.h"

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
#ifdef _USE_IMGUI
    for (auto it = InputActions.begin(); it != InputActions.end(); ++it)
    {
        ImVec4 color = ImVec4(0, 200, 200, 255);
        ImGui::TextColored(color, it->second->GetActionName().c_str());
        ImGui::Text(std::to_string(it->second->GetValue()).c_str());
        for (InputAction::sCallbackInfo cb : it->second->GetCallbacks())
        {
            color = ImVec4(100, 0, 100, 255);
            ImGui::TextColored(color, cb.DebugName.c_str());
        }
    }
    
#endif
}