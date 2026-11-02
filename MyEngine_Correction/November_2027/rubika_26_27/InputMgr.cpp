#include "InputMgr.h"
#include "Globals.h"

void InputMgr::Init()
{
    gData.DebugMgr->RegisterDebugableWindow("InputMgr", this);
}

void InputMgr::Start()
{
    
}

void InputMgr::Update(float deltaTime)
{
    
}

void InputMgr::Shut()
{
    
}

void InputMgr::CreateInputAction(std::string& actionName)
{
    //TODO: IMPLEMENT THIS
}

void InputMgr::RemoveInputAction(std::string& actionName)
{
    InputActions.erase(actionName);
}

void InputMgr::DrawDebug()
{
    
}