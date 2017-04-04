###############################################################################
# Configuration

set(ATB_EVENT_HANDLER_WINDOWS	WIN32	CACHE BOOL
		"Provide an event handler interface for use with Windows")

set(ATB_EVENT_HANDLER_X11		ON		CACHE BOOL
		"Provide an event handler interface for use with X11")

set(ATB_EVENT_HANDLER_GLFW		ON		CACHE BOOL
		"Provide an event handler interface for use with GLFW")

set(ATB_EVENT_HANDLER_GLFW3		ON		CACHE BOOL
		"Provide an event handler interface for use with GLFW3")

set(ATB_EVENT_HANDLER_GLUT		ON		CACHE BOOL
		"Provide an event handler interface for use with GLUT")

set(ATB_EVENT_HANDLER_SDL12		ON		CACHE BOOL
		"Provide an event handler interface for use with SDL 1.2")

set(ATB_EVENT_HANDLER_SDL13		ON		CACHE BOOL
		"Provide an event handler interface for use with SDL 1.3")

set(ATB_EVENT_HANDLER_SDL20		ON		CACHE BOOL
		"Provide an event handler interface for use with SDL 2")

set(ATB_EVENT_HANDLER_SFML		ON		CACHE BOOL
		"Provide an event handler interface for use with SFML")


###############################################################################
# Files

set(headers
	"include/AntTweakBar.h")

set(sources
	"compile/AntPerfTimer.h"

	"compile/TwBar.cpp"
	"compile/TwBar.h"
	"compile/TwMgr.cpp"
	"compile/TwMgr.h"

	"compile/resource.h"
	"compile/res/TwXCursors.h"
	"compile/AntTweakBar.rc"

	"compile/MiniGLFW.h"
	"compile/TwEventGLFW.c"

	"compile/MiniGLUT.h"
	"compile/TwEventGLUT.c"

	"compile/MiniGLFW3.h"
	"compile/TwEventGLFW3.c"

	"compile/TwEventSDL.c"

	"compile/MiniSDL12.h"
	"compile/TwEventSDL12.c"

	"compile/MiniSDL13.h"
	"compile/TwEventSDL13.c"

	"compile/MiniSDL20.h"
	"compile/TwEventSDL20.c"

	"compile/MiniSFML16.h"
	"compile/TwEventSFML.cpp"

	"compile/TwEventWin.c"
	"compile/TwEventX11.c")

###############################################################################
# Build setup

add_library(AntTweakBar ${headers} ${sources})
target_link_libraries(AntTweakBar PRIVATE ATBGuiRenderer)

target_include_directories(AntTweakBar
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
		$<INSTALL_INTERFACE:include>
	PRIVATE
		compile
		${CMAKE_CURRENT_BINARY_DIR})

set(defs TW_EXPORTS)

if (NOT BUILD_SHARED_LIBS)
	list(APPEND TW_STATIC)
elseif (WIN32 AND CMAKE_SIZEOF_VOID_P EQUAL 8)
	set_target_properties(${PROJECT_NAME}
		PROPERTIES OUTPUT_NAME "${PROJECT_NAME}64")
endif()

if (UNIX AND NOT APPLE)
	find_package(X11 REQUIRED)
	target_link_libraries(AntTweakBar PRIVATE ${X11_LIBRARIES})
endif()

append_unless(defs	TW_NO_WINDOWS_EVENTS			ATB_EVENT_HANDLER_WINDOWS)
append_unless(defs	TW_NO_X11_EVENTS				ATB_EVENT_HANDLER_X11)
append_unless(defs	TW_NO_GLFW_EVENTS				ATB_EVENT_HANDLER_GLFW)
append_unless(defs	TW_NO_GLFW3_EVENTS				ATB_EVENT_HANDLER_GLFW3)
append_unless(defs	TW_NO_GLUT_EVENTS				ATB_EVENT_HANDLER_GLUT)
append_unless(defs	TW_NO_SDL12_EVENTS				ATB_EVENT_HANDLER_SDL12)
append_unless(defs	TW_NO_SDL13_EVENTS				ATB_EVENT_HANDLER_SDL13)
append_unless(defs	TW_NO_SDL20_EVENTS				ATB_EVENT_HANDLER_SDL20)
append_unless(defs	TW_NO_SFML_EVENTS				ATB_EVENT_HANDLER_SFML)

target_compile_definitions(AntTweakBar PRIVATE ${defs})

