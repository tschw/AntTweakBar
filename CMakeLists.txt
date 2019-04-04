cmake_minimum_required(VERSION 2.8.11)

project(AntTweakBar)

option(ATB_BUILD_EXAMPLES "Whether to build example programs" OFF)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/scripts")

include(D3DShader)
include(Functions)

add_subdirectory(Renderer)
add_subdirectory(TweakBar)

if (ATB_BUILD_EXAMPLES)
	add_subdirectory(Examples)
endif()
