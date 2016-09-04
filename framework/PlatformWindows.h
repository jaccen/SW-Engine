#ifndef GLESView_HPP
#define GLESView_HPP

#include <Windowsx.h>
#include "Application.h"

class PlatformWindows {
public:
	PlatformWindows();
	~PlatformWindows();

	void run();

private:
	bool createNativeWindow();
	void destroyNativeWindow();

	bool handleEvents();
	void loop();

	inline EGLNativeWindowType getNativeWindow() const {
		return (EGLNativeWindowType)_hWnd;
	}
	inline EGLNativeDisplayType getNativeDisplay() const {
		return (EGLNativeDisplayType)_hDC;
	}

private:
	HWND _hWnd = nullptr;
	HDC _hDC = nullptr;
};


#endif // GLESView_HPP