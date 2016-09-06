#ifndef ENGINE_EGLWINDOW_H
#define ENGINE_EGLWINDOW_H
#include "Util.h"

#ifndef EGL_PLATFORM_SW_DEVICE_TYPE_NULL
#define EGL_PLATFORM_SW_DEVICE_TYPE_NULL 0x6AC0
#endif
class Window;
struct EGLPlatformParameters
{
	EGLint renderer;
	EGLint majorVersion;
	EGLint minorVersion;
	EGLint deviceType;
	EGLint presentPath;

	EGLPlatformParameters();
	explicit EGLPlatformParameters(EGLint renderer);
	EGLPlatformParameters(EGLint renderer, EGLint majorVersion, EGLint minorVersion, EGLint deviceType);
	EGLPlatformParameters(EGLint renderer,
		EGLint majorVersion,
		EGLint minorVersion,
		EGLint deviceType,
		EGLint presentPath);
};
bool operator<(const EGLPlatformParameters &a, const EGLPlatformParameters &b);
bool operator==(const EGLPlatformParameters &a, const EGLPlatformParameters &b);

class EGLWindow 
{
public:
	EGLWindow(EGLint glesMajorVersion,
		EGLint glesMinorVersion,
		const EGLPlatformParameters &platform);

	~EGLWindow();

	void setConfigRedBits(int bits) { mRedBits = bits; }
	void setConfigGreenBits(int bits) { mGreenBits = bits; }
	void setConfigBlueBits(int bits) { mBlueBits = bits; }
	void setConfigAlphaBits(int bits) { mAlphaBits = bits; }
	void setConfigDepthBits(int bits) { mDepthBits = bits; }
	void setConfigStencilBits(int bits) { mStencilBits = bits; }
	void setMultisample(bool multisample) { mMultisample = multisample; }
	void setDebugEnabled(bool debug) { mDebug = debug; }
	void setNoErrorEnabled(bool noError) { mNoError = noError; }
	void setSwapInterval(EGLint swapInterval) { mSwapInterval = swapInterval; }

	static EGLBoolean FindEGLConfig(EGLDisplay dpy, const EGLint *attrib_list, EGLConfig *config);

	void swap();

	EGLint getClientMajorVersion() const { return mClientMajorVersion; }
	EGLint getClientMinorVersion() const { return mClientMinorVersion; }
	const EGLPlatformParameters &getPlatform() const { return mPlatform; }
	EGLConfig getConfig() const;
	EGLDisplay getDisplay() const;
	EGLSurface getSurface() const;
	EGLContext getContext() const;
	int getConfigRedBits() const { return mRedBits; }
	int getConfigGreenBits() const { return mGreenBits; }
	int getConfigBlueBits() const { return mBlueBits; }
	int getConfigAlphaBits() const { return mAlphaBits; }
	int getConfigDepthBits() const { return mDepthBits; }
	int getConfigStencilBits() const { return mStencilBits; }
	bool isMultisample() const { return mMultisample; }
	bool isDebugEnabled() const { return mDebug; }
	EGLint getSwapInterval() const { return mSwapInterval; }

	bool initializeGL(Window *osWindow);
	void destroyGL();
	bool isGLInitialized() const;

private:
	EGLConfig mConfig;
	EGLDisplay mDisplay;
	EGLSurface mSurface;
	EGLContext mContext;

	EGLint mClientMajorVersion;
	EGLint mClientMinorVersion;
	EGLPlatformParameters mPlatform;
	int mRedBits;
	int mGreenBits;
	int mBlueBits;
	int mAlphaBits;
	int mDepthBits;
	int mStencilBits;
	bool mMultisample;
	bool mDebug;
	bool mNoError;
	EGLint mSwapInterval;
};
#endif