#ifndef CACATUIDAE_CORE_GAME_ENGINE_H
#define CACATUIDAE_CORE_GAME_ENGINE_H

#include <memory>
#include <vector>

#include "IGameScene.h"
#include "Graphics/RenderEngine.h"
#include "Graphics/Renderer/OGLRenderer.h"
#include "Audio/AudioManager.h"
#include <Audio/Player/OALAudioPlayer.h>

namespace cac
{
    class GameEngine
    {
    public:
	~GameEngine();
	
        //run the game. The parameter is the first gameScene that should run.
        void run(IGameScene* initialScene, WindowDesc windowDesc, bool isMainloop = true);
	
	void update(float dt);
        
	//exit the whole game
        void exit();
	
// 	void pushScene(IGameScene* scene);
// 	void popScene();

	bool loadPackage(std::string packagePath);
	
	RenderEngine<OGLRenderer>* getRenderEngine();
	AudioManager<OALAudioPlayer>* getAudioManager();
	InputManager* getInputManager();
 
    private:
	bool initializeRenderEngine(cac::WindowDesc windowDesc);
	
	InputManager inputManager;
	RenderEngine<OGLRenderer> renderEngine;
	AudioManager<OALAudioPlayer> audioManager;
	
        bool isRunning;
        std::vector<std::unique_ptr<IGameScene>> gameScenes;
    };
}

#endif