#include "Core/ResourceLoader.h"

#include <vector>

cac::ResourcePackage cac::ResourceLoader::loadPackage(std::string packageName)
{
    cac::ResourcePackage package;
    package.name = packageName;
    
    std::ifstream packageFile(packageName, std::ios::in |std::ios::binary);
    
    if(packageFile.good())
    {
	loadFonts(packageFile);
	package.textures = loadTextures(packageFile);
    }
    return package;
}

uint32_t cac::ResourceLoader::readBytesToUInt32(std::ifstream& packageFile, unsigned int numberOfBytes)
{
    std::vector<unsigned char> buffer(numberOfBytes);
    packageFile.read((char*)&buffer[0], numberOfBytes);
    
    uint32_t result = 0;
    
    for(unsigned int i = 0; i<numberOfBytes; i++)
    {
	short bitShift = 8 * (numberOfBytes - 1 - i);
	result |= (uint32_t) buffer[i] << bitShift; 
    }
    
    return result;
}


void cac::ResourceLoader::loadAudio(std::ifstream& packageFile)
{
   
}

void cac::ResourceLoader::loadFonts(std::ifstream& packageFile)
{
 unsigned char buffer[256];
    
    //first byte number of fonts
    uint32_t numberOfFonts = readBytesToUInt32(packageFile, 1);
    
    for(unsigned int i = 0; i<numberOfFonts; i++)
    {
	//one byte fontname length
	uint32_t fontNameLength = readBytesToUInt32(packageFile, 1);
	
	//n byte font name
	packageFile.read((char*)buffer, fontNameLength);
	std::string fontname((char*)buffer, fontNameLength);
	
	//1 byte font size
	uint32_t fontSize = (uint32_t)readBytesToUInt32(packageFile, 1);
	
	//2 byte font texture height
	uint32_t textureHeight = readBytesToUInt32(packageFile, 2);
	
	//2 byte font texture width
	uint32_t textureWidth = readBytesToUInt32(packageFile, 1);
	
	//4 byte fonttexture data count 
	uint32_t textureDataCount = readBytesToUInt32(packageFile, 4);;
			
	//nbyte font texture data
	std::vector<char> textureData(textureDataCount);
	packageFile.read((char*) &textureData[0], textureDataCount);
	//font.data = textureData;
		
	
	//2 byte for the number of glyphes 
	uint32_t glyphCount = readBytesToUInt32(packageFile, 2); 
	

	for(unsigned int i = 0; i<glyphCount; ++i)
	{
	    char glyphCharacter;
	    
	    //read 1 byte glyph character 
	    packageFile.read((char*) &glyphCharacter, 1);
	    
	    std::vector<unsigned int> glyphInformation(7);
	    
	    //7 * 4 bytes for the glyph informations 
	    for(int j = 0; j<7; ++j)
	    {
		uint32_t glyphValue =  readBytesToUInt32(packageFile, 4);
		glyphInformation[j] = glyphValue;	
	    }
	    
    // 	font.glyphs[glyphCharacter].advanceX = glyphInformation[0];
    // 	font.glyphs[glyphCharacter].advanceY = glyphInformation[1];
    // 	font.glyphs[glyphCharacter].bitmapWidth = glyphInformation[2];
    // 	font.glyphs[glyphCharacter].bitmapHeight = glyphInformation[3];
    // 	font.glyphs[glyphCharacter].bitmapLeft = glyphInformation[4];
    // 	font.glyphs[glyphCharacter].bitmapTop = glyphInformation[5];
    // 	font.glyphs[glyphCharacter].textureX= glyphInformation[6];
		

	}
    }
}

void cac::ResourceLoader::loadShaders(std::ifstream& packageFile)
{

}

std::vector<cac::TextureResource> cac::ResourceLoader::loadTextures(std::ifstream& packageFile)
{
     unsigned char buffer[256];
    //read textures 
    //first byte number of textures
    uint32_t numberOfTextures = readBytesToUInt32(packageFile, 1);
    std::vector<cac::TextureResource> textures(numberOfTextures);
    for(unsigned i = 0; i<numberOfTextures; ++i)
    {
	//1 byte length of the texture name
	uint32_t textureNameLength = readBytesToUInt32(packageFile, 1);
	
	//n byte texture name
	packageFile.read((char*)buffer, textureNameLength);
	std::string textureName((char*)buffer, textureNameLength);
	textures[i].name = textureName;
	
	//1 byte hasAlpha 
	packageFile.read((char*)buffer, 1);
	if(buffer[0] == 'F')
	    textures[i].hasAlpha = false;
	else 
	    textures[i].hasAlpha  = true;
	
	
	//2 byte texture height 
	uint32_t textureHeight =  readBytesToUInt32(packageFile, 2);
	textures[i].height = textureHeight;
	
	//2 byte texture width 
	uint32_t textureWidth =  readBytesToUInt32(packageFile, 2); 
	textures[i].width = textureWidth;
	
	
	//4 byte texture data count 
	uint32_t textureDataCount =  readBytesToUInt32(packageFile, 4); 
	
	
	std::vector<char> data(textureDataCount);
	packageFile.read((char*) &data[0], textureDataCount);
	textures[i].data = data;
	

    }
    return textures;
}


void cac::ResourceLoader::unloadPackage(std::string packageName)
{

}

