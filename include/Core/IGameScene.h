#ifndef CACATUIDAE_CORE_IGAMESCENE_H
#define CACATUIDAE_CORE_IGAMESCENE_H



namespace kte
{
    class GameObject;

    class IGameScene
    {
    public:
        IGameScene();

        virtual ~IGameScene();
    
        virtual bool init() { return true; }
       // virtual void update(float dt) { for (auto& system : systems) system->update(dt); }
       // virtual void addSystem(ISystem* system);
       // virtual void notifySystems(Message* message) { for(auto& system : systems) system->receiveMessage(message); }
	virtual void refresh() { }
	
        GameObject* getGameObject(unsigned int gameObjectId);
        void removeGameObject(unsigned int gameObjectid);
        void addGameObject(GameObject* gameObject);

    protected:
        std::shared_ptr<GameObject> scene;
        std::map<unsigned int, GameObject*> gameObjects;

    //    std::vector<std::unique_ptr<ISystem>> systems;
    };
}


#endif