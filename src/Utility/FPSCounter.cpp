#include "Utility/FPSCounter.h"
#include "Utility/Time.h"

cac::FPSCounter::FPSCounter()
{
    accumulatedTime = 0;
    deltaTime = 0;
    fpsCounter = 0;
    lastTime = cac::Time::getTimeInMs();
}

float cac::FPSCounter::getDeltaTime()
{
    return deltaTime / 1000.0f;
}


unsigned int cac::FPSCounter::getFramesPerSecond()
{
    return framesPerSecond;
}

void cac::FPSCounter::update()
{
    unsigned int currentTime = cac::Time::getTimeInMs();
    deltaTime = currentTime - lastTime;
    lastTime = currentTime;
    
    accumulatedTime += deltaTime;
    fpsCounter++;
    
    if(accumulatedTime >= 1.0f)
    {
	accumulatedTime = 0.0f;
	framesPerSecond = fpsCounter;
	fpsCounter = 0;
    }
}
