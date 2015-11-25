#include "Core/IGameScene.h"
#include "Core/GameEngine.h"

bool cac::IGameScene::setEngine(cac::GameEngine* engine)
{
    this->engine = engine;
    this->renderer = engine->getRenderEngine();
    
    return true;
}
