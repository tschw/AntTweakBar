###############################################################################
# Configuration

if (WIN32)
	set(ATB_EVENT_HANDLER_WINDOWS	ON	CACHE BOOL
			"Provide an event handler interface for use with Windows")
else()
	set(ATB_EVENT_HANDLER_WINDOWS	OFF)
endif()


if (WIN32 OR APPLE)
	set(x11 OFF)
else()
	set(x11 ON)
endif()

set(ATB_EVENT_HANDLER_X11		${x11}	CACHE BOOL
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

if ((UNIX AND NOT APPLE) OR ATB_EVENT_HANDLER_X11)
	find_package(X11 REQUIRED)
	target_link_libraries(AntTweakBar PRIVATE ${X11_LIBRARIES})
endif()

if (APPLE)
	target_link_libraries(AntTweakBar PRIVATE "-framework AppKit")
endif()

set(defs "INTERFACE")

if (NOT BUILD_SHARED_LIBS)

	list(APPEND defs TW_STATIC)
endif()

if (WIN32)

	# No MSVC auto linking via '#pragma lib' for CMake builds
	list(APPEND defs TW_NO_LIB_PRAGMA)

	# However, use suitable DLL name, so it can work in non-CMake builds

	set(dllname "${PROJECT_NAME}")

	if (NOT BUILD_SHARED_LIBS)
		set(dllname "${dllname}Static")
	endif()

	if (CMAKE_SIZEOF_VOID_P EQUAL 8)
		set(dllname "${dllname}64")
	endif()

	set_target_properties(${PROJECT_NAME}
			PROPERTIES OUTPUT_NAME "${dllname}")
endif()

list(APPEND defs PRIVATE TW_EXPORTS)

append_unless(defs	TW_NO_WINDOWS_EVENTS			ATB_EVENT_HANDLER_WINDOWS)
append_unless(defs	TW_NO_X11_EVENTS				ATB_EVENT_HANDLER_X11)
append_unless(defs	TW_NO_GLFW_EVENTS				ATB_EVENT_HANDLER_GLFW)
append_unless(defs	TW_NO_GLFW3_EVENTS				ATB_EVENT_HANDLER_GLFW3)
append_unless(defs	TW_NO_GLUT_EVENTS				ATB_EVENT_HANDLER_GLUT)
append_unless(defs	TW_NO_SDL12_EVENTS				ATB_EVENT_HANDLER_SDL12)
append_unless(defs	TW_NO_SDL13_EVENTS				ATB_EVENT_HANDLER_SDL13)
append_unless(defs	TW_NO_SDL20_EVENTS				ATB_EVENT_HANDLER_SDL20)
append_unless(defs	TW_NO_SFML_EVENTS				ATB_EVENT_HANDLER_SFML)

target_compile_definitions(AntTweakBar ${defs})

install(TARGETS AntTweakBar EXPORT AntTweakBarTargets
		RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
		ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
		LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

install(FILES "include/AntTweakBar.h" DESTINATION include)

set(ATB_CMAKE_PACKAGE_INSTALL_DIR
		"${CMAKE_INSTALL_LIBDIR}/cmake/AntTweakBar"
		CACHE PATH "Installation directory for CMake package configuration")
mark_as_advanced(ATB_CMAKE_PACKAGE_INSTALL_DIR)

install(EXPORT AntTweakBarTargets
		DESTINATION ${ATB_CMAKE_PACKAGE_INSTALL_DIR})
install(FILES "${CMAKE_SOURCE_DIR}/scripts/AntTweakBarConfig.cmake"
		DESTINATION ${ATB_CMAKE_PACKAGE_INSTALL_DIR})
