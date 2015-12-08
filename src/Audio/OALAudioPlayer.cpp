#include "Audio/Player/OALAudioPlayer.h"


#include <iostream>
#include <cstring>

cac::OALAudioPlayer::~OALAudioPlayer()
{
    release();
}


bool cac::OALAudioPlayer::initialize()
{
  
    std::cout<<"\nAvailable audio devices:"<<std::endl;
    
    std::vector<std::string> devices = getAudioDevices();
    
    
        if(!alcIsExtensionPresent(nullptr, "ALC_ENUMERATION_EXT"))
    {
	std::cout<<"Enumeration not available!"<<std::endl;
//	return false;
    }
     
    for(auto device : devices)
    {
	std::cout<<"\t"<<device<<std::endl;
    }
    
    const ALCchar* defaultDeviceName = alcGetString(nullptr, ALC_DEFAULT_DEVICE_SPECIFIER);
    
    //flush previous errors
    checkError("");
    
    audioDevice = alcOpenDevice(defaultDeviceName);
    
    if(!audioDevice)
    {
	std::cout<<"Failed to open the audio device"<<std::endl;
	return false;
    }


    checkError("Open audio device");   
	
    
    context = alcCreateContext(audioDevice, nullptr);
    if(!alcMakeContextCurrent(context))
    {
	std::cout<<"Failed to set audio context"<<std::endl;
	return false;
    }
    checkError("Set audio context");
    
	    
    //default listener
    ALfloat listenerOrientation[] = { 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f };
    alListener3f(AL_POSITION, 0, 0, 1.0f);
    alListener3f(AL_VELOCITY, 0, 0, 0);
    alListenerfv(AL_ORIENTATION, listenerOrientation);
    
    generateSourcePool(16);
    
    return true;
}

bool cac::OALAudioPlayer::generateSourcePool(unsigned int numberOfSources)
{
    for(unsigned int i = 0; i<numberOfSources; i++)
    {
	ALuint source;
	alGenSources(1, &source);

	alSourcef(source, AL_PITCH, 1);
	alSourcef(source, AL_GAIN, 1);
	alSource3f(source, AL_POSITION, 0, 0, 0);
	alSource3f(source, AL_VELOCITY, 0, 0, 0);
	alSourcei(source, AL_LOOPING, AL_FALSE);
	
	checkError("Audio source generation");
	
	if(!source)
	    return false;
	
	audioSources[source] = 0;
    }
    return true;
}


void cac::OALAudioPlayer::play(cac::Sound& sound)
{
    //check if sound has an id, otherwise give it a new one. Needed to stop the audio source again.
    if(!sound.id)
	sound.id = ++currendIdIndex;
    
    ALuint buffer = 0;
    if(audioBuffers.count(sound.audioFile))
	buffer = audioBuffers[sound.audioFile];
    else
    {
	std::cout<<"Audio file "<<sound.audioFile<<"not loaded!"<<std::endl;
	return;
    }
    //go through all available sources until an empty one is found
    for (auto& audioSource : audioSources)
    {
	if(audioSource.second == 0)
	{
	    audioSource.second = sound.id;
	    
	    alSourcei(audioSource.first, AL_BUFFER, buffer);
	    alSourcePlay(audioSource.first);
	    checkError("Play Audio");
	    return;
	}
    }
}

std::vector< std::string > cac::OALAudioPlayer::getAudioDevices()
{
    std::vector<std::string> availableDevices;
	    
    const ALCchar* devices = alcGetString(NULL, ALC_DEVICE_SPECIFIER);
    const ALCchar* next = devices+1;
    size_t length = 0;
    
    
    while (devices && *devices != '\0' && next && *next != '\0') 
    {
	availableDevices.push_back(std::string(devices));
	length = std::strlen(devices);
	devices += (length + 1);
	next += (length + 2);
    };

    return availableDevices;
}

bool cac::OALAudioPlayer::createAudioBuffer(const std::string name, std::vector<short> data, const unsigned int channels, const unsigned int sampleRate)
{
    if(audioBuffers.count(name))
    {
	std::cout<<"buffer "<<name<<" already exists"<<std::endl;
	return false;
    }    
    ALuint buffer;
    alGenBuffers(1, &buffer);
	       
    checkError("Audio Buffer generation");

    alBufferData(buffer, (channels == 1) ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16,
		    &data.front(), data.size() * sizeof(short), sampleRate);

    checkError("Set Audio Buffer Data");
    audioBuffers[name] = buffer;
    
    return buffer == 0;
}

void cac::OALAudioPlayer::stop(cac::Sound& sound)
{
    for(auto& audioSource : audioSources)
    {
	if(audioSource.second == sound.id)
	{
	    audioSource.second = 0;
	    alSourceStop(audioSource.first);
	    checkError("Stop Audio");
	}
    }
}

void cac::OALAudioPlayer::release()
{
    for(auto& audioSource : audioSources)
	alDeleteSources(1, &audioSource.first);
	
    alcMakeContextCurrent(nullptr);
  //  alcDestroyContext(context);
    alcCloseDevice(audioDevice);
}

void cac::OALAudioPlayer::setSoundVolume(float volume)
{
    if(volume > 1.0f)
	volume = 1.0f;
    if(volume < 0.0f)
	volume = 0.0f;
    
    for(auto& audioSource : audioSources)
    {
	alSourcef(audioSource.first, AL_GAIN, volume);
    }
}

bool cac::OALAudioPlayer::checkError(std::string message)
{
    ALenum error = alGetError();
    if(error == AL_NO_ERROR)
	return false;
    else
    {
	std::cout<<"AL_ERROR: "<<getErrorString(error)<<"\n"<<message<<std::endl;
	return true;
    }
}

std::string cac::OALAudioPlayer::getErrorString(ALenum error)
{
    switch (error)
    {
	case AL_INVALID_NAME: return "Invalid name param"; break;
	case AL_INVALID_ENUM: return "Invalid param"; break;
	case AL_INVALID_VALUE: return "Invalid enum-Param"; break;
	case AL_INVALID_OPERATION: return "Invalid operation"; break;
	case AL_OUT_OF_MEMORY: return "Out of memory"; break;
	default: return "unknown error";
    }
}

