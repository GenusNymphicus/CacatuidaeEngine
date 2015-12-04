/** \addtogroup Resources
 *  \ingroup Core
 *  @{
 */
 
 
#ifndef CACATUIDAE_CORE_RESOURCES_AUDIO_RESOURCE_H 
#define CACATUIDAE_CORE_RESOURCES_AUDIO_RESOURCE_H 

#include "IResource.h"

namespace cac 
{
     /** Loaded Texture
     * Contains the information for a audio file needed by the audio sources.
     * 
     * @sa ResourceLoader
     */
 
    struct AudioResource : public IResource
    {
	int sampleRate;
	int numberOfChannels;
	int numberOfFrames;
	std::vector<short> data;
    };
}
#endif

 /** @}*/