#ifndef CACATUIDAE_CORE_IGAMESCENE_H
#define CACATUIDAE_CORE_IGAMESCENE_H

#include "Graphics/RenderEngine.h"
#include "Graphics/Renderer/OGLRenderer.h"
#include "Input/InputManager.h"
#include "Input/InputKeys.h"
#include "Input/EMouseInput.h"

#include "Audio/Player/OALAudioPlayer.h"
#include "Audio/AudioManager.h"
#include "Audio/Sound.h"

namespace cac
{
    class GameEngine;
    class Message;
    
    class IGameScene
    {
    public:
	bool setEngine(GameEngine* engine);
        virtual bool initialize() {return true;}
        virtual ~IGameScene() {}
	virtual void event(std::string message){}
	virtual void event(Message* message){}
        virtual void update(float dt) { }
	virtual void refresh() { }

    protected:
	GameEngine* engine;
	RenderEngine<OGLRenderer>* renderer;
	InputManager* input;
	AudioManager<OALAudioPlayer>* audio;
    };
}


#endif