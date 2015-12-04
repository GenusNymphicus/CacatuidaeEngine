#ifndef CACATUIDAE_GRAPHICS_OALAUDIO_PLAYER_H
#define CACATUIDAE_GRAPHICS_OALAUDIO_PLAYER_H

#include <AL/al.h>
#include <AL/alc.h>
#include <string>
#include <map>
#include "IAudioPlayer.h"

namespace cac
{
    class OALAudioPlayer : public IAudioPlayer
    {
    public:
	virtual ~OALAudioPlayer() override;
	virtual bool initialize() override;
	virtual bool createAudioBuffer(const std::string name, std::vector<short> data, const unsigned int channels, const unsigned int sampleRate) override;
	virtual void play(Sound& sound) override;
	virtual void stop(Sound& sound) override;
	virtual void release() override;
	virtual void setSoundVolume(float volume) override;
	
	std::vector<std::string> getAudioDevices();
	bool checkError(std::string message);
	
	
    private:
	bool generateSourcePool(unsigned int numberOfSources);
	unsigned int currendIdIndex = 0;
	std::string getErrorString(ALenum error);
	std::map<ALuint, unsigned int> audioSources;
	std::map<std::string, unsigned int> audioBuffers;
	
	ALCdevice* audioDevice;
	ALCcontext* context;
    };
}
#endif