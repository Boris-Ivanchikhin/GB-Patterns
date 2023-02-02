cmake_minimum_required(VERSION 3.24)
project(SBomber-02)

set(CMAKE_CXX_STANDARD 20)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories(include)
#include_directories(src)

set(SOURCE_FILES
	app.cpp
		include/Factory.h src/Factory.cpp src/Commands.cpp)

file(GLOB SOURCES
	*.h
	*.cpp
	include/*.h
	src/*.cpp
	)

add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${SOURCES})
