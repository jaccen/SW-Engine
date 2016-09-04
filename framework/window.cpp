

#include <stdio.h>

#include "Window.h"
#include <iostream>

Window::Window(void)
{
	quit = false;

	//log_info("Window init to: %i x %i", this->width, this->height);
}

Window::~Window(void)
{

}


void Window::tick(void)
{

}


int Window::getWidth(void)
{
	return width;
}

int Window::getHeight(void)
{
	return height;
}

glm::vec4 Window::getViewport(void)
{
	return glm::vec4(0.0f, 0.0f, width, height);
}

bool Window::shouldQuit(void)
{
	return quit;
}

bool Window::createRenderContext(EGLNativeWindowType nativeWindow, EGLNativeDisplayType nativeDisplay)
{
	// Binding rendering API to the OpenGL ES API.
	if (!eglBindAPI(EGL_OPENGL_ES_API)) {
		std::cerr << "[ERROR] eglBindAPI\n";
		return false;
	}

	// 1.
	_display = eglGetDisplay(nativeDisplay);
	if (_display == EGL_NO_DISPLAY) {
		std::cerr << "[ERROR] eglGetDisplay: EGL_NO_DISPLAY\n";
		return false;
	}

	// 2.
	EGLint major, minor;
	if (eglInitialize(_display, &major, &minor) == EGL_FALSE) {
		EGLint error = eglGetError();
		switch (error) {
		case EGL_BAD_DISPLAY:
			std::cerr << "[ERROR] eglInitialize: EGL_BAD_DISPLAY\n";
			break;
		case EGL_NOT_INITIALIZED:
			std::cerr << "[ERROR] eglInitialize: EGL_NOT_INITIALIZED\n";
			break;
		default:
			std::cerr << "[ERROR] eglInitialize: unknown reason, error=" << error << '\n';
			break;
		}
		return false;
	}
	std::cout << "EGL initialized successful, EGL v" << major << "." << minor << '\n';

	// 3. Choose configuration.
	EGLint attribList[] = {
		EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
		EGL_RENDERABLE_TYPE, EGL_OPENGL_ES3_BIT_KHR,
		EGL_RED_SIZE, 8,
		EGL_GREEN_SIZE, 8,
		EGL_BLUE_SIZE, 8,
		EGL_ALPHA_SIZE, 8,
		EGL_DEPTH_SIZE, 24,
		EGL_STENCIL_SIZE, 8,
		EGL_NONE
	};
	EGLConfig config;
	EGLint numConfigs;
	if (eglChooseConfig(_display, attribList, &config, 1, &numConfigs) == EGL_FALSE) {
		std::cerr << "[ERROR] eglChooseConfig failed.\n";
		return false;
	}
	if (numConfigs < 1) {
		std::cerr << "[ERROR] eglChooseConfig error: num_config = 0\n";
		return false;
	}

	// 4. Creates an EGL window surface.
	EGLint nativeAttribList[] = {
		EGL_NONE
	};
	_surface = eglCreateWindowSurface(_display, config, nativeWindow, nativeAttribList);
	if (_surface == EGL_NO_SURFACE) {
		EGLint error = eglGetError();
		switch (error) {
		case EGL_BAD_MATCH:
			std::cerr << "[ERROR] eglCreateWindowSurface: EGL_BAD_MATCH\n";
			break;
		case EGL_BAD_CONFIG:
			std::cerr << "[ERROR] eglCreateWindowSurface: EGL_BAD_CONFIG\n";
			break;
		case EGL_BAD_NATIVE_WINDOW:
			std::cerr << "[ERROR] eglCreateWindowSurface: EGL_BAD_NATIVE_WINDOW\n";
			break;
		case EGL_BAD_ALLOC:
			std::cerr << "[ERROR] eglCreateWindowSurface: EGL_BAD_ALLOC\n";
			break;
		default:
			std::cerr << "[ERROR] eglCreateWindowSurface: unknown reason: " << error << "\n";
			break;
		}
		return false;
	}


	// 5. Create Context.
	const EGLint contextAttribList[] = {
		EGL_CONTEXT_CLIENT_VERSION, 2, // OpenGL ES 3.0
		EGL_NONE
	};
	_context = eglCreateContext(_display, config, EGL_NO_CONTEXT, contextAttribList);
	if (_context == EGL_NO_CONTEXT) {
		EGLint error = eglGetError();
		switch (error) {
		case EGL_BAD_CONFIG:
			std::cerr << "[ERROR] eglCreateContext failed, EGL_BAD_CONFIG.\n";
			break;
		default:
			std::cerr << "[ERROR] eglCreateContext failed, unknown error=" << error << '\n';
			break;
		}
		return false;
	}

	// Attack an EGL rendering context to EGL surfaces.
	if (eglMakeCurrent(_display, _surface, _surface, _context) == EGL_FALSE) {
		std::cerr << "[ERROR] eglMakeCurrent failed.\n";
		return false;
	}

	return true;
}

void Window::destroyRenderContext()
{
	if (_display != nullptr) {
		eglMakeCurrent(_display, _surface, _surface, _context);
		eglDestroyContext(_display, _context);
		eglDestroySurface(_display, _surface);

		eglTerminate(_display);

		_context = nullptr;
		_surface = nullptr;
		_display = nullptr;
	}
}

void Window::swapBuffers()
{
	eglSwapBuffers(_display, _surface);
}

unsigned int Window::getDeltaTime()
{
	return 20;
}
