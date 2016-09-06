#include "texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void Texture::LoadFile(const std::string& filename)
{

}

void Texture::Bind()
{
	glActiveTexture(GL_TEXTURE0 + m_textureid);
	glBindTexture(GL_TEXTURE_2D, m_textureid);
}

void Texture::UnBind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::Texture()
{

}

Texture::Texture(const std::string& filename)
{

}

Texture::~Texture()
{
	glDeleteTextures(1, &m_textureid);
	m_textureid = 0;

	if (pdata)
	{
		delete pdata;
		pdata = nullptr;
	}
}
GLuint Texture::LoadTexture2D(std::string a_sPath, bool bGenerateMipMaps)
{
	unsigned char* image = stbi_load(a_sPath.c_str(), &iWidth, &iHeight, &iBPP, STBI_rgb_alpha);
	if (pdata == nullptr)
	{
		return 0;
	}
	glGenTextures(1, &m_textureid);

	glBindTexture(GL_TEXTURE_2D, m_textureid);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	if (iBPP == 3){
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, iWidth, iHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	}
	else if (iBPP == 4){
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, iWidth, iHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	}
	glBindTexture(GL_TEXTURE_2D, 0);

	stbi_image_free(image);
	return m_textureid; // Success
}

GLuint Texture::CreateDefaultTexture(int width, int height){
	GLuint textureId;

	// 2x2 Image, 3 bytes per pixel (R, G, B)
	GLubyte pixels[4 * 3] =
	{
		255, 0, 0, // Red
		0, 255, 0, // Green
		0, 0, 255, // Blue
		255, 255, 0  // Yellow
	};
	GLuint* pTexData = new GLuint[width * height];
	for (int i = 0; i < width; i++){
		for (int j = 0; j < height; j++)
		{
			// Fills the data with a fancy pattern
			GLuint col = (255 << 24) + ((255 - j * 2) << 16) + ((255 - i) << 8) + (255 - i * 2);
			if (((i*j) / 8) % 2) col = (GLuint)(255 << 24) + (255 << 16) + (0 << 8) + (255);
			pTexData[j*width + i] = col;
		}
	}
	// Use tightly packed data
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// Generate a texture object
	glGenTextures(1, &textureId);

	// Bind the texture object
	glBindTexture(GL_TEXTURE_2D, textureId);

	// Load the texture
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pTexData);

	// Set the filtering mode
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	delete pTexData;
	pTexData = nullptr;

	return textureId;
}