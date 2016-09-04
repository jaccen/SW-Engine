#ifndef UTIL_HPP
#define UTIL_HPP

#include <string>

#ifdef __APPLE__  
    #include <OpenGLES/ES3/gl.h>
    #include <OpenGLES/ES3/glext.h>
	#define LOGI printf
	#define LOGE printf
#elseif define  __ANDRIOD__
	#include <jni.h>
	#include <andriod/log.h>
	#include <android/log.h>
	#include <GLES3/gl3.h>
	#include <GLES3/gl3ext.h>
	//! JNI Information and Error Log
	#define  LOG_TAG    "glOpenGLES3Native"
	#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO, LOG_TAG,__VA_ARGS__)
	#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

#else //Windows
   #include <EGL/egl.h>
   #include <EGL/eglext.h>
   #include <GLES3/gl3.h>
  
#endif

#ifdef __APPLE__
#include "glm.hpp"
#include "matrix_transform.hpp"
#include "intersect.hpp"
#include "noise.hpp"
#include "random.hpp"
#else
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/intersect.hpp>
#include <glm/gtc/noise.hpp>
#include <glm/gtc/random.hpp>
#endif
std::string GetFileContent(const std::string& path);

class GLUtils{
	GLUtils();
	virtual ~GLUtils();
};


#endif // UTIL_HPP