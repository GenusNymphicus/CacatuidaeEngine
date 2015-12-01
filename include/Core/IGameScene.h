#ifndef CACATUIDAE_CORE_IGAMESCENE_H
#define CACATUIDAE_CORE_IGAMESCENE_H

#include "Graphics/RenderEngine.h"
#include "Graphics/Renderer/OGLRenderer.h"
#include "Input/InputManager.h"

namespace cac
{
    class GameEngine;
    
    class IGameScene
    {
    public:
	bool setEngine(GameEngine* engine);
	
	
        virtual bool initialize() {return true;}
	
	
        virtual ~IGameScene() {}
    
	virtual void event(std::string message){}
        virtual void update(float dt) { }
       // virtual void addSystem(ISystem* system);
       // virtual void notifySystems(Message* message) { for(auto& system : systems) system->receiveMessage(message); }
	virtual void refresh() { }
	
   /*     GameObject* getGameObject(unsigned int gameObjectId);
        void removeGameObject(unsigned int gameObjectid);
        void addGameObject(GameObject* gameObject);
*/
    protected:
 //       std::shared_ptr<GameObject> scene;
  //      std::map<unsigned int, GameObject*> gameObjects;

    //    std::vector<std::unique_ptr<ISystem>> systems;
	GameEngine* engine;
	RenderEngine<OGLRenderer>* renderer;
	InputManager* input;
    };
}


#endif