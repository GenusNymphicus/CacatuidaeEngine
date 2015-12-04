#include "Core/IGameScene.h"
#include "Core/GameEngine.h"

bool cac::IGameScene::setEngine(cac::GameEngine* engine)
{
    this->engine = engine;
    this->renderer = engine->getRenderEngine();
    this->input = engine->getInputManager();
    this->audio = engine->getAudioManager();
    
    input->setInputCallback([this](std::string action){this->event(action);});
    return true;
}
