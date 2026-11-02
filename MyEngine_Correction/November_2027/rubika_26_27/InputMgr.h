#pragma once
#include "DebugMgr.h"
#include "InputAction.h"

class InputMgr : public IDebugable
{
public:
    void Init();
    void Start();
    void Update(float deltaTime);
    void Shut();
    
    void CreateInputAction(std::string& actionName);
    void RemoveInputAction(std::string& actionName);
    
    virtual void DrawDebug() override;
    
protected:
    std::unordered_map<std::string, InputAction> InputActions;
    
};
