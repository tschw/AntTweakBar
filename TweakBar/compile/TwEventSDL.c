//	---------------------------------------------------------------------------
//
//	@file		TwEventSDL.c
//	@brief		Helper:
//				translate and re-send mouse and keyboard events
//				from SDL event loop to AntTweakBar
//
//	@author		Philippe Decaudin
//	@license	This file is part of the AntTweakBar library.
//				For conditions of distribution and use, see License.txt
//
//	note:		AntTweakBar.dll does not need to link with SDL,
//				it just needs some definitions for its helper functions.
//
//	---------------------------------------------------------------------------


#include <AntTweakBar.h>

#if !defined TW_NO_SDL12_EVENTS
int TW_CALL TwEventSDL12(const void *sdlEvent); // implemented in TwEventSDL12.c
#endif
#if !defined TW_NO_SDL13_EVENTS
int TW_CALL TwEventSDL13(const void *sdlEvent); // implmeneted in TwEventSDL13.c
#endif
#if !defined TW_NO_SDL20_EVENTS
int TW_CALL TwEventSDL20(const void *sdlEvent); // implemented in TwEventSDL20.c
#endif

#if !(defined TW_NO_SDL12_EVENTS && defined TW_NO_SDL13_EVENTS && defined TW_NO_SDL20_EVENTS)

#ifdef	__cplusplus
	extern "C" { int TW_CALL TwSetLastError(const char *staticErrorMessage); }
#else
	int TW_CALL TwSetLastError(const char *staticErrorMessage);
#endif	// __cplusplus


//	TwEventSDL returns zero if msg has not been handled or the SDL version
//	is not supported, and a non-zero value if it has been handled by the
//	AntTweakBar library.
int TW_CALL TwEventSDL(const void *sdlEvent, unsigned char majorVersion, unsigned char minorVersion)
{
#if !defined TW_NO_SDL12_EVENTS
	if( majorVersion == 1 && minorVersion == 2 )
		return TwEventSDL12(sdlEvent);
#endif
#if !defined TW_NO_SDL13_EVENTS
	if( majorVersion==1 && minorVersion == 3 )
		return TwEventSDL13(sdlEvent);
#endif
#if !defined TW_NO_SDL20_EVENTS
	if ( majorVersion < 1 || (majorVersion == 1 && minorVersion <= 3) )
	{
#endif
		static const char *g_ErrBadSDLVersion = "Unsupported SDL version";
		TwSetLastError(g_ErrBadSDLVersion);
		return 0;
#if !defined TW_NO_SDL20_EVENTS
	}
	return TwEventSDL20(sdlEvent);
#endif
}

#endif
