#pragma once
#include "Scene.h"

class SceneMgr
{
    public:
    SceneMgr() {}
    ~SceneMgr() {}
    virtual void Start();
    virtual void Update(float fDeltaTime);
    virtual void Destroy();
    
    //----- Getters -----
    Scene* GetActiveScene(){ return m_activeScene; }
    
    //----- Methods -----
    void AddScene(Scene* scene);
    void SetActiveScene(const std::string& sceneName);
    
    private:
        std::vector<Scene*> m_scenes;
        Scene* m_activeScene {};
    
};
