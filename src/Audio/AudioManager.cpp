

template<class AudioPlayer> bool cac::AudioManager<AudioPlayer>::initialize()
{
    return player.initialize();
}

template<class AudioPlayer> bool cac::AudioManager<AudioPlayer>::loadAudio(cac::AudioResource resource)
{
    audioResources[resource.name] = resource;
    return player.createAudioBuffer(resource.name, resource.data, resource.numberOfChannels, resource.sampleRate);
}

template<class AudioPlayer> void cac::AudioManager<AudioPlayer>::unloadAudio(std::string name)
{

}

template<class AudioPlayer> void cac::AudioManager<AudioPlayer>::play(cac::Sound& sound)
{
   player.play(sound);
}

template<class AudioPlayer> void cac::AudioManager<AudioPlayer>::stop(cac::Sound& sound)
{
    player.stop(sound);
}


template<class AudioPlayer> void cac::AudioManager<AudioPlayer>::update()
{
    
}


template<class AudioPlayer> void cac::AudioManager<AudioPlayer>::release()
{

}



template<class AudioPlayer> void cac::AudioManager<AudioPlayer>::setMusicVolume(float volume)
{
    musicVolume = volume;
    settingsChanged = true;
}


template<class AudioPlayer> void cac::AudioManager<AudioPlayer>::setSoundVolume(float volume)
{
    soundVolume = volume;
    settingsChanged = true;
    player.setSoundVolume(soundVolume);
}

template<class AudioPlayer> float cac::AudioManager<AudioPlayer>::getMusicVolume()
{
    return musicVolume;
}

template<class AudioPlayer> float cac::AudioManager<AudioPlayer>::getSoundVolume()
{
    return soundVolume;
}

