//
//  Author: Shervin Aflatooni
//

#ifndef WINDOW_H
#define WINDOW_H

#include "Util.h"

class Window
{
public:
	Window(void);
	~Window(void);

	void tick(void);
	//
	bool createRenderContext(EGLNativeWindowType nativeWindow, EGLNativeDisplayType nativeDisplay);
	void destroyRenderContext();
	void swapBuffers();


	unsigned int getDeltaTime();
	int getWidth(void);
	int getHeight(void);
	glm::vec4 getViewport(void);

	bool shouldQuit(void);

private:

	int width, height;

	EGLDisplay _display = nullptr;
	EGLSurface _surface = nullptr;
	EGLContext _context = nullptr;

	bool quit;
};

#endif
