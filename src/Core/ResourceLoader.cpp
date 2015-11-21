#include "Core/ResourceLoader.h"

#include <vector>

cac::ResourcePackage cac::ResourceLoader::loadPackage(std::string packageName)
{
    cac::ResourcePackage package;
    package.name = packageName;
    
    std::ifstream packageFile(packageName, std::ios::in |std::ios::binary);
    
    if(packageFile.good())
    {
	package.fonts = loadFonts(packageFile);
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

std::vector<cac::FontResource> cac::ResourceLoader::loadFonts(std::ifstream& packageFile)
{
 unsigned char buffer[256];
    
    //first byte number of fonts
    uint32_t numberOfFonts = readBytesToUInt32(packageFile, 1);
    std::vector<cac::FontResource> fonts(numberOfFonts);
    for(unsigned int i = 0; i<numberOfFonts; i++)
    {
	//1 byte fontname length
	uint32_t fontNameLength = readBytesToUInt32(packageFile, 1);
	
	//n byte font name
	packageFile.read((char*)buffer, fontNameLength);
	std::string fontName((char*)buffer, fontNameLength);
	fonts[i].name = fontName;
	//1 byte font size
	uint32_t fontSize = (uint32_t)readBytesToUInt32(packageFile, 1);
	fonts[i].fontSize = fontSize;
	
	//2 byte font texture height
	uint32_t textureHeight = readBytesToUInt32(packageFile, 2);
	fonts[i].textureHeight = textureHeight;
	
	//2 byte font texture width
	uint32_t textureWidth = readBytesToUInt32(packageFile, 2);
	fonts[i].textureWidth = textureWidth;
	
	//4 byte fonttexture data count 
	uint32_t textureDataCount = readBytesToUInt32(packageFile, 4);
			
	//nbyte font texture data
	fonts[i].data.resize(textureDataCount);
	packageFile.read((char*) &fonts[i].data[0], textureDataCount);

	
	//2 byte for the number of glyphes 
	uint32_t glyphCount = readBytesToUInt32(packageFile, 2); 
	
	for(unsigned int g = 0; g<glyphCount; ++g)
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
	    
	    fonts[i].glyphs[glyphCharacter].advanceX = glyphInformation[0];
	    fonts[i].glyphs[glyphCharacter].advanceY = glyphInformation[1];
	    fonts[i].glyphs[glyphCharacter].bitmapWidth = glyphInformation[2];
	    fonts[i].glyphs[glyphCharacter].bitmapHeight = glyphInformation[3];
	    fonts[i].glyphs[glyphCharacter].bitmapLeft = glyphInformation[4];
	    fonts[i].glyphs[glyphCharacter].bitmapTop = glyphInformation[5];
	    fonts[i].glyphs[glyphCharacter].textureX = glyphInformation[6];
	}
    }
    return fonts;
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
	
	
	textures[i].data.resize(textureDataCount);
	packageFile.read((char*) &textures[i].data[0], textureDataCount);
	

    }
    return textures;
}


void cac::ResourceLoader::unloadPackage(std::string packageName)
{

}

