cmake_minimum_required(VERSION 2.8.12)
option(BUILD_SHARED_LIBS "Whether to build a shared library" ON)

project(AntTweakBar)

option(ATB_BUILD_EXAMPLES "Whether to build example programs" OFF)

include(GNUInstallDirs)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/scripts")

include(D3DShader)
include(Functions)

if (APPLE)
	set(CMAKE_MACOSX_RPATH ON)
	set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -xobjective-c++)
endif()

if (BUILD_SHARED_LIBS)
	set(CMAKE_POSITION_INDEPENDENT_CODE ON)
endif()

add_subdirectory(Renderer)
add_subdirectory(TweakBar)

if (ATB_BUILD_EXAMPLES)
	add_subdirectory(Examples)
endif()
