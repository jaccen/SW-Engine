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

	GLuint CreateDefaultTexture(int width, int height);
	GLuint LoadTexture2D(std::string a_sPath, bool bGenerateMipMaps);
	void LoadFile(const std::string& filename);
	void Bind();
	void UnBind();
protected:
private:
	GLuint m_textureid = 0;
	unsigned char* pdata = nullptr;
	int iWidth, iHeight, iBPP; // Texture width, height, and bytes per pixel
};
#endif