set(target ATBGuiRenderer)

###############################################################################
# OpenGL Configuration

set(ATB_GUIRENDERER_USE_CORE_GL		ON		CACHE BOOL
		"Enable OpenGL core profile rendering code")

set(ATB_GUIRENDERER_USE_LEGACY_GL	ON		CACHE BOOL
		"Enable legacy OpenGL rendering code")

###############################################################################
# Direct3D Configuration

if (WIN32)

	set(ATB_GUIRENDERER_USE_D3D11	ON		CACHE BOOL
			"Enable Direct3D 11 rendering code")

	set(ATB_GUIRENDERER_USE_D3D10	ON		CACHE BOOL
			"Enable Direct3D 10 rendering code")

	set(ATB_GUIRENDERER_USE_D3D9	ON		CACHE BOOL
			"Enable Direct3D 9 rendering code")

else()

	set(ATB_GUIRENDERER_USE_D3D11	OFF)
	set(ATB_GUIRENDERER_USE_D3D10	OFF)
	set(ATB_GUIRENDERER_USE_D3D9	OFF)

endif()

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

add_library(${target} STATIC ${headers} ${sources})

target_include_directories(${target}
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	PRIVATE
		compile
		${CMAKE_CURRENT_BINARY_DIR}
)

set(defs "")

if (NOT WIN32)

	if (NOT APPLE)
		find_package(OpenGL REQUIRED)
	else()
		set(OPENGL_LIBRARIES "-framework Foundation" "-framework OpenGL")
		list(APPEND defs "GL_SILENCE_DEPRECATION")
	endif()

	target_link_libraries(${target} PRIVATE ${OPENGL_LIBRARIES})

elseif (CMAKE_SIZEOF_VOID_P EQUAL 8)

	set_target_properties(${target}
			PROPERTIES OUTPUT_NAME "${target}64")
endif()

append_unless(defs	"ANT_TW_NO_CORE_GL"		ATB_GUIRENDERER_USE_CORE_GL)
append_unless(defs	"ANT_TW_NO_LEGACY_GL"	ATB_GUIRENDERER_USE_LEGACY_GL)
append_unless(defs	"ANT_TW_NO_D3D11"		ATB_GUIRENDERER_USE_D3D11)
append_unless(defs	"ANT_TW_NO_D3D10"		ATB_GUIRENDERER_USE_D3D10)
append_unless(defs	"ANT_TW_NO_D3D9"		ATB_GUIRENDERER_USE_D3D9)

target_compile_definitions(${target} PRIVATE ${defs})

set(d3d11HlslFile "compile/TwDirect3D11.hlsl")

if (ATB_GUIRENDERER_USE_D3D11)

	target_include_directories(${target} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})

	set(d3d11Renderer "compile/TwDirect3D11.cpp")

	set(vertex_shaders
			"LineRectVS"
			"LineRectCstColorVS"
			"TextVS"
			"TextCstColorVS")

	foreach(shader IN LISTS vertex_shaders)
		add_hlsl_header(
				${d3d11HlslFile} ${shader} "vs_4_0_level_9_1" ${d3d11Renderer})
	endforeach()

	set(pixel_shaders
			"LineRectPS"
			"TextPS")

	foreach(shader IN LISTS pixel_shaders)
		add_hlsl_header(
				${d3d11HlslFile} ${shader} "ps_4_0_level_9_1" ${d3d11Renderer})
	endforeach()

else()
	ignore_hlsl(${d3d11HlslFile})
endif()

###############################################################################
# Installation (required for static builds of the lib)

if (NOT BUILD_SHARED_LIBS)
	install(TARGETS ${target} EXPORT AntTweakBarTargets
			ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})
endif()
