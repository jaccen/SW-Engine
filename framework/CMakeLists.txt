cmake_minimum_required(VERSION 3.3)

#静态库生成后存放的目录
SET(LIBRARY_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/lib/")             

# Source files
file(GLOB_RECURSE CPP_FILES  
  ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/*.c
)


# Header files
file(GLOB_RECURSE H_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.h)

# 注意，这里指定绝对路径。  
INCLUDE_DIRECTORIES(${ENGINE_SOURCE_DIR}/include)  
#是定义工程的库文件，其中存放着库文件
#LINK_DIRECTORIES(${EXTERNAL_SOURCE_DIR}/lib)

SET(EXECUTABLE_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/bin/")    #可执行生成后存放的目录(CMAKE_SOURCE_DIR是cmake目录)
SET(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib)

add_library(framework ${CPP_FILES} ${H_FILES})
target_link_libraries(${FRAMEWORK_LIBRARY}
	${LIBRARY_GLES3}
	${LIBRARY_EGL}
)



