#pragma 

#include "../../../Include.h"
#include "../Texture/PngLoader.h"

class TextureManager
{
public:
	TextureManager();
	~TextureManager();

	GLuint Get(std::string TextureFileName);

private:
	GLuint LoadTexture(std::string TextureFileName);

	std::map <std::string, GLuint> _textureMap;
};

