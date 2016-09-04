cmake_minimum_required(VERSION 3.3)

project(SW-Engine)


set(GLES_ROOT ${CMAKE_SOURCE_DIR})

#if (CMAKE_SYSTEM_NAME STREQUAL Android )
#if ( NOT CMAKE_SYSTEM_PROCESSOR )
 #       set ( CMAKE_SYSTEM_PROCESSOR    armeabi-v7a )
 #   endif ()
#if ( NOT CMAKE_SYSTEM_VERSION )
 #       set ( CMAKE_SYSTEM_VERSION      8 )
 #   endif ()
 #   if ( NOT NDK_TOOLCHAIN_VERSION) 
 #       set ( NDK_TOOLCHAIN_VERSION     4.8 )
  #  endif ()

#    set ( ANDROID_NDK_ROOT $ENV{ANDROID_NDK_ROOT} )

  #  find_path ( TOOLCHAIN_ROOT bin PATHS ${ANDROID_NDK_ROOT}/toolchains/arm-linux-androideabi-${NDK_TOOLCHAIN_VERSION}/prebuilt/* )
    
if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")   
    
if(WIN32)
	set(SYSTEM_STRING win32)
else()
	set(SYSTEM_STRING win64)
endif()
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
   if(ANDROID)
    set(SYSTEM_STRING "Android")
else()
    set(LINUX TRUE)
    set(SYSTEM_STRING "Linux")
 endif()
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  if(IOS)
    set(SYSTEM_STRING "IOS")
  else()
    set(MACOSX TRUE)
    set(APPLE TRUE)
    set(SYSTEM_STRING "Mac OSX")
  endif()
endif()    
 if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  set(COMPILER_STRING ${CMAKE_CXX_COMPILER_ID})
  set(CLANG TRUE)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  if(MINGW)
    set(COMPILER_STRING "Mingw GCC")
  else()
    set(COMPILER_STRING "GCC")
  endif()
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
  set(COMPILER_STRING "${CMAKE_CXX_COMPILER_ID} C++")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
  set(COMPILER_STRING "Visual Studio C++")
endif()   
    if(CMAKE_CROSSCOMPILING)
  set(BUILDING_STRING "It appears you are cross compiling for ${SYSTEM_STRING} with ${COMPILER_STRING}")
else()
  set(BUILDING_STRING "It appears you are builing natively for ${SYSTEM_STRING} with ${COMPILER_STRING}")
endif()



set(BINARY_GLES3 ${GLES_ROOT}/external/lib/${SYSTEM_STRING}/libGLESv2.dll)
set(BINARY_EGL   ${GLES_ROOT}/external/lib/${SYSTEM_STRING}/libEGL.dll)


include_directories(
	external/include
	external/glm-0.9.6.3
)
link_directories(
	external/lib/${SYSTEM_STRING}
)


set(LIBRARY_GLES3 ${GLES_ROOT}/external/lib/${SYSTEM_STRING}/libGLESv2.lib)
set(LIBRARY_EGL   ${GLES_ROOT}/external/lib/${SYSTEM_STRING}/libEGL.lib)


# framework library
set(FRAMEWORK_LIBRARY framework)
add_subdirectory(framework)


# samples
add_subdirectory(example)

