#include "TextureManager.h"


TextureManager::TextureManager()
{
}


TextureManager::~TextureManager()
{
	//! TODO: Clear
}

GLuint TextureManager::Get(std::string textureFileName)
{
	GLuint texture = _textureMap[textureFileName];
	
	if (!texture)
	{
		texture = LoadTexture(textureFileName);

		_textureMap[textureFileName] = texture;
	}

	return texture;
}

GLuint TextureManager::LoadTexture(std::string textureFileName)
{
	PngLoader Loader = PngLoader(textureFileName.c_str());

	printf("Texture %s is loaded\n", textureFileName.c_str());

	return Loader.GetTexture();
}