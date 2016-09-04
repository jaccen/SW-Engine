#ifndef ENGINE_TEXTURE_H
#define ENGINE_TEXTURE_H
#include "stb_image.h"
#include <string>
#include "Util.h"
class Texture
{
public:
	Texture();
	Texture(const std::string& filename);
	virtual ~Texture();
protected:
private:
	GLuint m_textureid = 0;
};
#endif