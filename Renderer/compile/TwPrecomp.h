//	---------------------------------------------------------------------------
//
//	@file		TwPrecomp.h
//	@brief		Precompiled header
//	@author		Philippe Decaudin
//	@license	This file is part of the AntTweakBar library.
//				For conditions of distribution and use, see License.txt
//
//	note:		Private header
//
//	---------------------------------------------------------------------------


#if !defined ANT_TW_PRECOMP_INCLUDED
#define ANT_TW_PRECOMP_INCLUDED


#if defined _MSC_VER
#	pragma warning(disable: 4514)	// unreferenced inline function has been removed
#	pragma warning(disable: 4710)	// function not inlined
#	pragma warning(disable: 4786)	// template name truncated
#	pragma warning(disable: 4530)	// exceptions not handled
#	define _CRT_SECURE_NO_DEPRECATE // visual 8 secure crt warning
#endif

#if defined(_WINDOWS) || defined(WIN32) || defined(WIN64) || defined(_WIN32) || defined(_WIN64)
#	ifndef WIN32_LEAN_AND_MEAN
#		define WIN32_LEAN_AND_MEAN // Exclude rarely-used stuff from Windows headers
#	endif
#	include <windows.h>
#	include <shellapi.h>
#	define ANT_WINDOWS
#elif defined(__APPLE__)
#	include <unistd.h>
#	include <Foundation/Foundation.h>
#	define ANT_OSX
#	ifndef _MACOSX
#		define _MACOSX
#	endif
#	undef _WIN32
#	undef WIN32
#	undef _WIN64
#	undef WIN64
#	undef _WINDOWS
#	undef ANT_WINDOWS
#	undef ANT_UNIX
#else
#	include <X11/cursorfont.h>
#	define GLX_GLXEXT_LEGACY
#	include <GL/glx.h>
#	include <X11/Xatom.h>
#	include <unistd.h>
#	include <malloc.h>
#	define ANT_UNIX
#	undef _WIN32
#	undef WIN32
#	undef _WIN64
#	undef WIN64
#	undef _WINDOWS
#	undef ANT_WINDOWS
#	undef ANT_OSX
#endif

#if !defined(ANT_OGL_HEADER_INCLUDED)
#	if defined(ANT_OSX)
#		include <OpenGL/gl.h>
#	else
#		include <GL/gl.h>  // must be included after windows.h
#	endif
#	define	ANT_OGL_HEADER_INCLUDED
#endif

#if !defined(NDEBUG) && !defined(_DEBUG)
#	define _DEBUG
#endif

#include <cstdio>
#include <cassert>
#include <cmath>
#include <cfloat>
#include <cstring>
#include <cstdlib>
#include <memory.h>

#if defined(_MSC_VER) && _MSC_VER<=1200
#	pragma warning(push, 3)
#endif
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <list>
#include <set>
#if defined(_MSC_VER) && _MSC_VER<=1200
#	pragma warning(pop)
#endif

#endif	// !defined ANT_TW_PRECOMP_INCLUDED
