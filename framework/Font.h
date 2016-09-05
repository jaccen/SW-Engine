#ifndef ENGINE_FONT_H
#define ENGINE_FONT_H
/*
×ÖÌå
jaccen
*/
#include "texture.h"
enum FontEnum
{
	LEGACY_TYPE = 0,
	LEGACY_WIDTH = 256,
	LEGACY_HEIGHT = 512
};
class Font
{
public:
	Font();
	virtual ~Font();

	void LoadFile(const char* pFileName);
	void LoadArray(const unsigned char* pdata, int nType);
	void SetRenderState(unsigned int prog);
	void SetFiltering(int nFilterTyoe);
protected:
private:
	int m_nType = 0;
	Texture m_texture;
};
#endif // !ENGINE_FONT_H
