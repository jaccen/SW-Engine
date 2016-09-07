#ifndef UTIL_HPP
#define UTIL_HPP
/**************************************************************************

Copyright:

Author: jiaxiaobo

Date:

Description:

**************************************************************************/
#include <string>

#ifdef __APPLE__  
#include <OpenGLES/ES3/gl.h>
#include <OpenGLES/ES3/glext.h>
#define glBindVertexArray glBindVertexArrayOES
#define glDeleteVertexArrays glDeleteVertexArraysOES
#define glGenVertexArrays glGenVertexArraysOES
#define glIsVertexArray glIsVertexArrayOES
#define glMapBuffer glMapBufferOES
#define glUnmapBuffer glUnmapBufferOES
#define GL_WRITE_ONLY GL_WRITE_ONLY_OES
#define GL_DEPTH24_STENCIL8 GL_DEPTH24_STENCIL8_OES
#define glClearDepth glClearDepthf
#define OPENGL_ES
#define GP_USE_VAO
#define LOGI printf
#define LOGE printf
#elseif define  __ANDRIOD__
#include <jni.h>
#include <andriod/log.h>
#include <android/log.h>
#include <GLES3/gl3.h>
#include <GLES3/gl3ext.h>

//
extern PFNGLBINDVERTEXARRAYOESPROC glBindVertexArray;
extern PFNGLDELETEVERTEXARRAYSOESPROC glDeleteVertexArrays;
extern PFNGLGENVERTEXARRAYSOESPROC glGenVertexArrays;
extern PFNGLISVERTEXARRAYOESPROC glIsVertexArray;
extern PFNGLMAPBUFFEROESPROC glMapBuffer;
extern PFNGLUNMAPBUFFEROESPROC glUnmapBuffer;
#define GL_WRITE_ONLY GL_WRITE_ONLY_OES
#define GL_DEPTH24_STENCIL8 GL_DEPTH24_STENCIL8_OES
#define glClearDepth glClearDepthf
#define OPENGL_ES
#define GP_USE_VAO
//! JNI Information and Error Log
#define  LOG_TAG    "glOpenGLES2Native"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO, LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

#else //Windows

#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <GLES3/gl3.h>
#define GP_USE_VAO
#endif

#ifdef __APPLE__
#include "glm.hpp"
#include "matrix_transform.hpp"
#include "intersect.hpp"
#include "noise.hpp"
#include "random.hpp"
#include "type_ptr.hpp"
#else
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/intersect.hpp>
#include <glm/gtc/noise.hpp>
#include <glm/gtc/random.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#endif
#include <string>
#include <vector>
#include <map>

typedef signed char   s8;
typedef unsigned char u8;
typedef char          c8;
typedef unsigned short int u16;
typedef signed   short int s16;
typedef unsigned  int u32;
typedef signed    int s32;
typedef unsigned long long u64;
typedef signed long long s64;
typedef bool   b2;
typedef float  f32;
typedef double f64;
typedef glm::vec4 vec4;
typedef glm::vec3 vec3;
typedef glm::vec2 vec2;
typedef glm::mat4 Matrix;
typedef glm::quat Rotation;

#define MIN(x, y) ((x) < (y) ? (x) :(y))
#define MAX(x, y) ((x) > (y) ? (x) :(y))
#define CLAMP(x, min, max) (MAX(MIN(x, max), min))
#define ALIGN(x) ((x + 3) & ~0x03)

class VertexPos {
public:

	VertexPos() : position(0.0f, 0.0f, 0.0f) {
	}

	VertexPos(const vec3& p) : position(p) {
	}
	vec3 position;
};

class VertexPosTex {
public:

	VertexPosTex() : position(0.0f, 0.0f, 0.0f), texCoord(0.0f, 0.0f) {
	}

	VertexPosTex(const vec3& p, const vec2& t) : position(p), texCoord(t) {
	}
	vec3 position;
	vec2 texCoord;
};

class VertexPosNormTex {
public:

	VertexPosNormTex() : position(0.0f, 0.0f, 0.0f), normal(0.0f, 0.0f, 0.0f), texCoord(0.0f, 0.0f) {
	}

	VertexPosNormTex(const vec3& p, const vec3& n, const vec2& t) : position(p), normal(n), texCoord(t) {
	}
	vec3 position;
	vec3 normal;
	vec2 texCoord;
};

class VertexPosNormTex3 {
public:
	vec3 position;
	vec3 normal;
	vec2 texCoord;
	//vec2 texCoord1; // Shane: 暂时用不到
	//vec2 texCoord2;
};

class VertexPosColorTex {
public:

	VertexPosColorTex() : position(0.0f, 0.0f, 0.0f), color(0.0f, 0.0f, 0.0f, 1.0f), texCoord(0.0f, 0.0f), texCoord1(0.0f, 0.0f) {
	}

	VertexPosColorTex(const vec3& p, const vec4& c, const vec2& t, const vec2& t1) : position(p), color(c), texCoord(t), texCoord1(t1) {
	}
	vec3 position;
	vec4 color;
	vec2 texCoord;
	vec2 texCoord1;
};

class VertexPosNormColorTex {
public:

	VertexPosNormColorTex() : position(0.0f, 0.0f, 0.0f), normal(0, 0, 0), color(0.0f, 0.0f, 0.0f, 1.0f), texCoord(0.0f, 0.0f) {
	}

	VertexPosNormColorTex(const vec3& p, const vec3& n, const vec4& c, const vec2& t, const vec2& t1) : position(p), color(c), texCoord(t), texCoord1(t1) {
	}
	vec3 position;
	vec3 normal;
	vec4 color;
	vec2 texCoord;
	vec2 texCoord1;
};

//点纹理

class VertexPosColor {
public:

	VertexPosColor(const vec3& p, const vec4& c)
		: position(p), color(c) {
	}
	vec3 position;
	vec4 color;
};

std::string GetFileContent(const std::string& path);

//-----Memory Leak Report-----//
#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new (_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DBG_NEW
#endif
#endif

//-----Safe Memory Delete-----//
template <typename T>
inline void SafeDelete(T*& pPointer)
{
	if (pPointer != NULL)
	{
		delete (pPointer);
		(pPointer) = NULL;
	}
}

template <typename T>
inline void SafeDeleteArray(T*& pPointer)
{
	if (pPointer != NULL)
	{
		delete[](pPointer);
		(pPointer) = NULL;
	}
}

class GLUtils{
	GLUtils();
	virtual ~GLUtils();
};



#ifdef __ANDROID__
typedef unsigned int GamepadHandle;
#else
typedef unsigned long GamepadHandle;
#endif


// namespace ECS {}
#ifdef __cplusplus
#define NS_ECS_BEGIN                     namespace ECS {
#define NS_ECS_END                       }
#define USING_NS_ECS                     using namespace ECS
#else
#define NS_ECS_BEGIN
#define NS_ECS_END
#define USING_NS_ECS
#endif




#endif // UTIL_HPP