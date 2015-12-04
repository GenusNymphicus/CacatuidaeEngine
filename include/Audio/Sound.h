#ifndef CACATUIDAE_AUDIO_SOUND_H
#define CACATUIDAE_AUDIO_SOUND_H

namespace cac 
{

    class OALAudioPlayer;
    struct Sound 
    {
	std::string audioFile = "";
	
	private:
	friend class OALAudioPlayer;
	unsigned int id = 0;
    };
}

#endif