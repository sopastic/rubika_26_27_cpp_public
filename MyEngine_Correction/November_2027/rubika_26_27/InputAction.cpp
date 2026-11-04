#include "InputAction.h"

#include "Logger.h"

InputAction::InputAction(const std::string& name) : ActionName(name)
{
    ActionNameHash = std::hash<std::string>{}(ActionName);
}

void InputAction::SetActionName(const std::string& name)
{
    ActionName = name;
}

void InputAction::SetValue(float value)
{
    Value = value;
    RunCallbacks();
}

void InputAction::RegisterCallback(const std::string& debugName, std::function<void(float)> callback, void* owner)
{
    Callbacks.push_back(sCallbackInfo(debugName, callback, owner));
    Logger::Info("Registered callback");
}

void InputAction::UnregisterCallbacks(void* owner)
{
    if (Callbacks.empty()) return;
    for (std::vector<sCallbackInfo>::iterator it = Callbacks.begin(); it != Callbacks.end();)
    {
        if (it->Owner == owner) Callbacks.erase(it);
    }
}


void InputAction::RunCallbacks()
{
    if (Callbacks.empty()) return;
    
    if (Value != 0.0f)
    {
        for (const sCallbackInfo& cb : Callbacks)
        {
            cb.Callback(Value);
        }
    }
}

void InputAction::AddKey(sf::Keyboard::Key key)
{
    Keys.push_back(key);
    Logger::Info("Key added");
}

// void InputAction::RemoveKey(sf::Keyboard::Key key)
// {
//     for (auto it = Keys.begin(); it != Keys.end();)
//     {
//         if (it == key)
//         {
//             Keys.erase(it);
//         }
//     }
// }

