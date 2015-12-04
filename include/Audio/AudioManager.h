#ifndef CACATUIDAE_AUDIO_AUDIOMANAGER_H
#define CACATUIDAE_AUDIO_AUDIOMANAGER_H

#include <string>
#include <map>
#include <boost/concept_check.hpp>

#include "Core/Resources/AudioResource.h"
#include "Sound.h"

namespace cac
{
    template<class AudioPlayer> class AudioManager 
    {
    public:
	bool initialize();
	void update();
	void release();
	
	bool loadAudio(AudioResource data);
	void unloadAudio(std::string name);
	
	void play(Sound& sound);
	void stop(Sound& sound);
	
// 	void play(Music music);
// 	void stop(Music music);
// 	
	void setMusicVolume(float volume);
	float getMusicVolume();
	
	void setSoundVolume(float volume);
	float getSoundVolume();
	
	
    private:
	AudioPlayer player;
	float musicVolume = 0.1f;
	float soundVolume = 0.1f;
	
	bool musicMuted = false;
	bool soundMuted = false;
	bool settingsChanged = true;
	
	std::map<std::string, AudioResource> audioResources;
    };
}

// Required due the template class. Needed to avoid "unresolved references" linking errors.
#include "Audio/AudioManager.cpp"

#endif