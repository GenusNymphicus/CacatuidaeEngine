#ifndef CACATUIDAE_CORE_RESOURCE_LOADER_H
#define CACATUIDAE_CORE_RESOURCE_LOADER_H

#include <fstream>
#include <map>
#include "Core/ResourcePackage.h"
#include "Graphic/TextureResource.h"

namespace cac 
{
    class ResourceLoader 
    {
    public:
	ResourcePackage loadPackage(std::string packageName);
	void unloadPackage(std::string packageName);
	
    private:
	void loadFonts(std::ifstream& packageFile);
	std::vector<TextureResource> loadTextures(std::ifstream& packageFile);
	void loadShaders(std::ifstream& packageFile);
	void loadAudio(std::ifstream& packageFile);
	uint32_t readBytesToUInt32(std::ifstream& packageFile, unsigned int numberOfBytes);
	
	std::map<std::string, std::string> loadedTextures;
    };
}
#endif