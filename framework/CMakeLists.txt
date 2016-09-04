
set(COMMON_SOURCE
	Util.h
	Util.cpp
	Application.h
	Application.cpp
	PlatformWindows.h
	PlatformWindows.cpp
	
	gl/Program.h
	gl/Program.cpp
	gl/Shader.h
	gl/Shader.cpp
)


add_library(${FRAMEWORK_LIBRARY}
	${COMMON_SOURCE}
)
target_link_libraries(${FRAMEWORK_LIBRARY}
	${LIBRARY_GLES3}
	${LIBRARY_EGL}
)
