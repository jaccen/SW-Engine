#ifndef ENGINE_PLATFORM_H
#define ENGINE_PLATFORM_H

#if defined(_WIN32) || defined(_WIN64)
#   define SW_PLATFORM_WINDOWS 1
#elif defined(__APPLE__)
#   define SW_PLATFORM_APPLE 1
#   define SW_PLATFORM_POSIX 1
#elif defined(ANDROID)
#   define SW_PLATFORM_ANDROID 1
#   define SW_PLATFORM_POSIX 1
#elif defined(__linux__) || defined(EMSCRIPTEN)
#   define SW_PLATFORM_LINUX 1
#   define SW_PLATFORM_POSIX 1
#elif defined(__FreeBSD__) || \
      defined(__OpenBSD__) || \
      defined(__NetBSD__) || \
      defined(__DragonFly__) || \
      defined(__sun) || \
      defined(__GLIBC__) || \
      defined(__GNU__) || \
      defined(__QNX__)
#   define SW_PLATFORM_POSIX 1
#else
#   error Unsupported platform.
#endif

#ifdef SW_PLATFORM_WINDOWS
#   ifndef STRICT
#       define STRICT 1
#   endif
#   ifndef WIN32_LEAN_AND_MEAN
#       define WIN32_LEAN_AND_MEAN 1
#   endif
#   ifndef NOMINMAX
#       define NOMINMAX 1
#   endif

#   include <windows.h>
#   include <intrin.h>

#   if defined(WINAPI_FAMILY) && (WINAPI_FAMILY != WINAPI_FAMILY_DESKTOP_APP)
#       define SW_ENABLE_WINDOWS_STORE 1
#   endif

#   if defined(SW_ENABLE_D3D9)
#       include <d3d9.h>
#       include <d3dcompiler.h>
#   endif

#   if defined(SW_ENABLE_D3D11)
#       include <d3d10_1.h>
#       include <d3d11.h>
#       include <d3d11_1.h>
#       include <dxgi.h>
#       include <dxgi1_2.h>
#       include <d3dcompiler.h>
#   endif

#   if defined(SW_ENABLE_WINDOWS_STORE)
#       include <dxgi1_3.h>
#       if defined(_DEBUG)
#           include <DXProgrammableCapture.h>
#           include <dxgidebug.h>
#       endif
#   endif

#   undef near
#   undef far
#endif

#if defined(_MSC_VER) && !defined(_M_ARM)
#include <intrin.h>
#define SW_USE_SSE
#elif defined(__GNUC__) && (defined(__x86_64__) || defined(__i386__))
#include <x86intrin.h>
#define SW_USE_SSE
#endif

// The MemoryBarrier function name collides with a macro under Windows
// We will undef the macro so that the function name does not get replaced
#undef MemoryBarrier
#endif // !ENGINE_PLATFORM_H
