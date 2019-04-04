
###############################################################################
# Direct3D Examples
###############################################################################

function(add_d3d_example main dxlib)
	get_filename_component(target "${main}" NAME_WE)
	add_executable(${target} WIN32 ${main} ${ARGN})
	target_link_libraries(${target} PRIVATE AntTweakBar ${dxlib})
	target_include_directories(${target} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
endfunction()

if (ATB_EVENT_HANDLER_WINDOWS)

	if (ATB_GUIRENDERER_USE_D3D9)
		add_d3d_example(TwSimpleDX9.cpp d3d9)
	endif()

	if (ATB_GUIRENDERER_USE_D3D10)
		add_d3d_example(TwSimpleDX10.cpp d3d10)
	endif()

	if (ATB_GUIRENDERER_USE_D3D11)
		add_d3d_example(TwSimpleDX11.cpp d3d11 TwSimpleDX11.hlsl)

		add_hlsl_header(
				TwSimpleDX11.hlsl MainVS "vs_4_0_level_9_1" TwSimpleDX11.cpp)
		add_hlsl_header(
				TwSimpleDX11.hlsl MainPS "ps_4_0_level_9_1" TwSimpleDX11.cpp)
	endif()

endif(ATB_EVENT_HANDLER_WINDOWS)


###############################################################################
# OpenGL Examples
###############################################################################

function(add_ogl_example main libprefix)

	get_filename_component(target "${main}" NAME_WE)
	add_executable(${target} ${main})

	target_link_libraries(${target} AntTweakBar
			${${libprefix}_LIBRARY} ${${libprefix}_LIBRARIES})
	target_include_directories(${target} PRIVATE
			${${libprefix}_INCLUDE_DIR} ${${libprefix}_INCLUDE_DIRS})

endfunction()

find_package(OpenGL)

function(add_legacy_ogl_example main libprefix)

	if (OPENGL_FOUND)
		return()
	endif()

	add_ogl_example(${amin} ${libprefix})

	get_filename_component(target "${main}" NAME_WE)
	target_link_libraries(${target} PRIVATE ${OPENGL_LIBRARIES})
	target_include_directories(${target} PRIVATE ${OPENGL_INCLUDE_DIRS})

endfunction()

#------------------------------------------------------------------------------
# SDL 1.X

macro(sdl1_examples_try_version version)

	find_package(SDL ${version} EXACT QUIET)

	if (SDL_FOUND)

		if (ATB_GUIRENDERER_USE_LEGACY_GL)
			add_legacy_ogl_example(TwSimpleSDL.c SDL)
		endif()

		if (ATB_GUIRENDERER_USE_CORE_GL)
			add_legacy_ogl_example(TwGLCoreSDL.c SDL)
		endif()

	endif()
endmacro()


if (ATB_EVENT_HANDLER_SDL12)
	sdl1_examples_try_version(1.2)
endif()

if (ATB_EVENT_HANDLER_SDL13)
	sdl1_examples_try_version(1.3)
endif()

#------------------------------------------------------------------------------
# SDL 2

if (ATB_EVENT_HANDLER_SDL20)

	find_package(SDL2 CONFIG)

	if (SDL2_FOUND)
		add_ogl_example(TwGLCoreSDL2 SDL2)
	endif()

endif()

#------------------------------------------------------------------------------
# GLUT

if (ATB_GUIRENDERER_USE_LEGACY_GL AND ATB_EVENT_HANDLER_GLUT)

	find_package(GLUT)

	if (GLUT_FOUND)
		add_legacy_ogl_example(TwSimpleGLUT.c GLUT)
		add_legacy_ogl_example(TwDualGLUT.c GLUT)
		add_legacy_ogl_example(TwString.cpp GLUT)
	endif()

endif()

