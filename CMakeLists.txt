cmake_minimum_required(VERSION 3.6)

project(AntTweakBar)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/scripts)

include(D3DShader)
include(Functions)

add_subdirectory(Renderer)
add_subdirectory(TweakBar)
add_subdirectory(Examples)

