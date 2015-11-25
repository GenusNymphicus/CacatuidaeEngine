#ifndef CACATUIDAE_UTILITY_FPSCOUNTER_H
#define CACATUIDAE_UTILITY_FPSCOUNTER_H



namespace cac
{
    class FPSCounter
    {
    public:
	    FPSCounter();

	    void update();
	    
	    unsigned int getFramesPerSecond();
	    
	    float getDeltaTime();	
    private:
	    unsigned int accumulatedTime;
	    unsigned int deltaTime;
	    int fpsCounter;
	    int framesPerSecond;
	    unsigned int  lastTime;
    };
}

#endif