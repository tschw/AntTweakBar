###############################################################################
# Files

set(headers
		"include/TwColors.h"
		"include/TwFonts.h"
		"include/TwGraph.h")

set(sources
		"compile/TwPrecomp.cpp"
		"compile/TwPrecomp.h"
		"compile/TwColors.cpp"
		"compile/TwFonts.cpp"
		"compile/TwGraph.cpp"

		"compile/TwOpenGL.cpp"
		"compile/TwOpenGL.h"
		"compile/LoadOGL.cpp"
		"compile/LoadOGL.h"

		"compile/TwOpenGLCore.cpp"
		"compile/TwOpenGLCore.h"
		"compile/LoadOGLCore.cpp"
		"compile/LoadOGLCore.h"

		"compile/TwDirect3D9.cpp"
		"compile/TwDirect3D9.h"

		"compile/TwDirect3D10.cpp"
		"compile/TwDirect3D10.h"
		"compile/d3d10vs2003.h"

		"compile/TwDirect3D11.cpp"
		"compile/TwDirect3D11.h"
		"compile/TwDirect3D11.hlsl")

###############################################################################
# Build setup

add_library(ATB_GUIRenderer ${headers} ${sources})


find_program(ATB_D3D11_FXC fxc DOC "Direct3D 11 Shader Compiler")

if (NOT ATB_D3D11_FXC)
	message(SEND_ERROR "No fxc.exe for Direct3D 11 available.")
endif()

set(shaders
		"LineRectVS"
		"LineRectCstColorVS"
		"LineRectPS"
		"TextVS"
		"TextCstColorVS"
		"TextPS")

set(input "${CMAKE_CURRENT_SOURCE_DIR}/compile/TwDirect3D11.hlsl")

set(shaderTargets "")
foreach(shader IN LISTS shaders)
	set(target "TwDirect3D11_${shader}.h")
	string(REGEX MATCH "..$" suffix ${shader})
	string(TOLOWER ${suffix} prefix)
	add_custom_command(
		OUTPUT ${target}
		COMMAND
			${ATB_D3D11_FXC}
			/T ${prefix}_4_0_level_9_1 /E ${shader}
			/Fh ${target} ${input}
		MAIN_DEPENDENCY ${input})
	list(APPEND shaderTargets ${target})
endforeach()

set_property(SOURCE "compile/TwDirect3D11.cpp"
		APPEND PROPERTY OBJECT_DEPENDS ${shaderTargets})


target_include_directories(ATB_GUIRenderer
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
		$<INSTALL_INTERFACE:include>
	PRIVATE
		compile
		${CMAKE_CURRENT_BINARY_DIR}
)

