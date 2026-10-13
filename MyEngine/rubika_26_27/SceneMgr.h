#pragma once
#include "Scene.h"
#include "DebugMgr.h"

class SceneMgr : public IDebugable
{
    public:
    SceneMgr() {}
    ~SceneMgr() {}
    
    void Init();
    void Shut();
    
    virtual void Start();
    virtual void Update(float fDeltaTime);
    virtual void Destroy();
    
    //----- Getters -----
    Scene* GetActiveScene(){ return m_activeScene; }
    Scene* GetScene(const std::string& sceneName);
    std::vector<Scene*> GetAllScenes() {return m_scenes;}
    
    //----- Methods -----
    void AddScene(Scene* scene);
    void SetActiveScene(const std::string& sceneName);
    static void SceneDebug(Scene* scene);
    virtual void DrawDebug() override;
    void ShowDebug();
    
    private:
        std::vector<Scene*> m_scenes;
        Scene* m_activeScene {};
    
    protected:
    struct sSceneInfo
    {
        std::string Name;
        std::vector<std::string> EntitiesName;
    };
    void PushNewSceneInfo(const sSceneInfo& sceneInfo);
    std::vector<sSceneInfo> ScenesInfo;
    
};
