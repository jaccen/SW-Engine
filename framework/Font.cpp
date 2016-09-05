#include "Font.h"

Font::Font()
{
	m_nType = LEGACY_TYPE;
}
Font::~Font(){

}

void Font::LoadFile(const char* pFileName)
{
	m_texture.LoadFile(pFileName);
}

void Font::LoadArray(const unsigned char* pdata, int nType)
{
	if (nType == LEGACY_TYPE)
	{
		
	}
	else{

	}
}

void Font::SetRenderState(unsigned int prog)
{
	int hTexture = glGetUniformLocation(prog, "uTexture");
	glUniform1i(hTexture, 0);
	m_texture.Bind();
}
