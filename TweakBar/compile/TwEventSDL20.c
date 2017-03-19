//	---------------------------------------------------------------------------
//
//	@file		TwEventSDL20.c
//	@brief		Helper:
//				translate and re-send mouse and keyboard events
//				from SDL 2.0 event loop to AntTweakBar
//
//	@author		Philippe Decaudin, Marius Schilder
//	@license	This file is part of the AntTweakBar library.
//				For conditions of distribution and use, see License.txt
//
//	---------------------------------------------------------------------------

#if !defined TW_NO_SDL20_EVENTS

#include "MiniSDL20.h"
#include <AntTweakBar.h>
#include <stdio.h>

//	The way SDL handles keyboard events has changed between version 1.2
//	and 2.0. It is now more difficult to translate SDL keyboard events to
//	AntTweakBar events. The following code is an attempt to do so, but
//	it is rather complex and not always accurate (eg, CTRL+1 is not handled).
//	If someone knows a better and more robust way to do the keyboard events
//	translation, please let me know.

//	TwEventSDL returns zero if msg has not been handled,
//	and a non-zero value if it has been handled by the AntTweakBar library.
int TW_CALL TwEventSDL20(const void *sdlEvent)
{
	int handled = 0;
	const SDL_Event *event = (const SDL_Event *)sdlEvent;

	if( event==NULL )
		return 0;

	switch( event->type )
	{
	case SDL_KEYDOWN:
		if( event->key.keysym.sym & SDLK_SCANCODE_MASK ) {
			int key = 0;
			switch( event->key.keysym.scancode ) {
			case SDL_SCANCODE_UP:
				key = TW_KEY_UP;
				break;
			case SDL_SCANCODE_DOWN:
				key = TW_KEY_DOWN;
				break;
			case SDL_SCANCODE_RIGHT:
				key = TW_KEY_RIGHT;
				break;
			case SDL_SCANCODE_LEFT:
				key = TW_KEY_LEFT;
				break;
			case SDL_SCANCODE_INSERT:
				key = TW_KEY_INSERT;
				break;
			case SDL_SCANCODE_HOME:
				key = TW_KEY_HOME;
				break;
			case SDL_SCANCODE_END:
				key = TW_KEY_END;
				break;
			case SDL_SCANCODE_PAGEUP:
				key = TW_KEY_PAGE_UP;
				break;
			case SDL_SCANCODE_PAGEDOWN:
				key = TW_KEY_PAGE_DOWN;
				break;
			default:
				if( event->key.keysym.scancode >= SDL_SCANCODE_F1 &&
					event->key.keysym.scancode <= SDL_SCANCODE_F12 ) {
				  key = event->key.keysym.scancode + TW_KEY_F1 - SDL_SCANCODE_F1;
				}
				break;
			}
			if( key != 0 ) {
				handled = TwKeyPressed(key, event->key.keysym.mod);
			}
		} else {
			handled = TwKeyPressed(event->key.keysym.sym /*& 0xFF*/,
								   event->key.keysym.mod);
		}
		break;
	case SDL_MOUSEMOTION:
		handled = TwMouseMotion(event->motion.x, event->motion.y);
		break;
	case SDL_MOUSEBUTTONUP:
	case SDL_MOUSEBUTTONDOWN:
		if( event->type == SDL_MOUSEBUTTONDOWN &&
			(event->button.button == 4 || event->button.button == 5) ) {
			// mouse wheel
			static int s_WheelPos = 0;
			if( event->button.button == 4 )
				++s_WheelPos;
			else
				--s_WheelPos;
			handled = TwMouseWheel(s_WheelPos);
		} else {
			handled = TwMouseButton(
				(event->type==SDL_MOUSEBUTTONUP) ?
					TW_MOUSE_RELEASED : TW_MOUSE_PRESSED,
				(TwMouseButtonID)event->button.button);
		}
		break;
	case SDL_WINDOWEVENT:
		if (event->window.event == SDL_WINDOWEVENT_RESIZED) {
		  // tell the new size to TweakBar
		  TwWindowSize(event->window.data1, event->window.data2);
		  // do not set 'handled'
		  // SDL_VIDEORESIZE may be also processed by the calling application
		}
		break;
	}

	return handled;
}

#endif
