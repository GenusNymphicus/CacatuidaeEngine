#ifndef CACATUIDAE_GRAPHICS_IAUDIO_PLAYER_H
#define CACATUIDAE_GRAPHICS_IAUDIO_PLAYER_H
#include <Audio/Sound.h>
#include <vector>
namespace cac
{
    class IAudioPlayer 
    {
    public:
	virtual ~IAudioPlayer(){}
	virtual bool initialize() = 0;
	virtual bool createAudioBuffer(const std::string name, std::vector<short> data, const unsigned int channels, const unsigned int sampleRate) = 0;
	virtual void play(Sound& sound) = 0;
	virtual void stop(Sound& sound) = 0;
	virtual void release() = 0;
	virtual void setSoundVolume(float volume) = 0;
    };
}
#endif