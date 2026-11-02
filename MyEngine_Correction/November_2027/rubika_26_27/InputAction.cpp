#include "InputAction.h"

void InputAction::SetActionName(const std::string& name)
{
    ActionName = name;
}

void InputAction::SetValue(float value)
{
    Value = value;
}

void InputAction::RegisterCallback(const std::string& debugName, std::function<void(float)> callback, void* owner)
{
    // sCallbackInfo cbInfo = sCallbackInfo(debugName, callback, owner);
    Callbacks.push_back(sCallbackInfo(debugName, callback, owner));
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
    
    for (const sCallbackInfo& cb : Callbacks)
    {
            cb.Callback(Value);
    }
}