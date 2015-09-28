//  ---------------------------------------------------------------------------
//
//  @file       TwEventGLFW3.c
//  @brief      Helper:
//              translate and re-send mouse and keyboard events
//              from GLFW3 event callbacks to AntTweakBar
//
//  @author     Philippe Decaudin, Joachim Fenkes
//  @license    This file is part of the AntTweakBar library.
//              For conditions of distribution and use, see License.txt
//
//  ---------------------------------------------------------------------------

#include "MiniGLFW3.h" // a subset of GLFW3.h needed to compile TwEventGLFW3.c
// note: AntTweakBar.dll does not need to link with GLFW,
// it just needs some definitions for its helper functions.

#include <AntTweakBar.h>


int TW_CALL TwEventMouseButtonGLFW3(GLFWwindow *window, int glfwButton, int glfwAction, int glfwMods)
{
    int handled = 0;
    TwMouseAction action = (glfwAction==GLFW_PRESS) ? TW_MOUSE_PRESSED : TW_MOUSE_RELEASED;

    if( glfwButton==GLFW_MOUSE_BUTTON_LEFT )
        handled = TwMouseButton(action, TW_MOUSE_LEFT);
    else if( glfwButton==GLFW_MOUSE_BUTTON_RIGHT )
        handled = TwMouseButton(action, TW_MOUSE_RIGHT);
    else if( glfwButton==GLFW_MOUSE_BUTTON_MIDDLE )
        handled = TwMouseButton(action, TW_MOUSE_MIDDLE);

    return handled;
}


static int convertModifiers(int glfwMods)
{
	int ret = 0;
	if (glfwMods & GLFW_MOD_ALT)
		ret |= TW_KMOD_ALT;
	if (glfwMods & GLFW_MOD_CONTROL)
		ret |= TW_KMOD_CTRL;
	if (glfwMods & GLFW_MOD_SHIFT)
		ret |= TW_KMOD_SHIFT;
	if (glfwMods & GLFW_MOD_SUPER)
		ret |= TW_KMOD_META;
	return ret;
}


int TW_CALL TwEventKeyGLFW3(GLFWwindow *window, int glfwKey, int glfwScancode, int glfwAction, int glfwMods)
{
    int handled = 0;
	int mod = convertModifiers(glfwMods);
	int testkp = ((mod&TW_KMOD_CTRL) || (mod&TW_KMOD_ALT)) ? 1 : 0;
	int k = 0;

    if (glfwAction == GLFW_RELEASE)
		return 0;

    if( (mod&TW_KMOD_CTRL) && glfwKey>0 && glfwKey<GLFW_KEY_SPECIAL )   // CTRL cases
        return TwKeyPressed(glfwKey, mod);

	if (glfwKey < GLFW_KEY_SPECIAL)
		return 0;

    if( glfwKey>=GLFW_KEY_F1 && glfwKey<=GLFW_KEY_F15 )
        k = TW_KEY_F1 + (glfwKey-GLFW_KEY_F1);
    else if( testkp && glfwKey>=GLFW_KEY_KP_0 && glfwKey<=GLFW_KEY_KP_9 )
        k = '0' + (glfwKey-GLFW_KEY_KP_0);
    else
    {
        switch( glfwKey )
        {
        case GLFW_KEY_ESCAPE:
            k = TW_KEY_ESCAPE;
            break;
        case GLFW_KEY_UP:
            k = TW_KEY_UP;
            break;
        case GLFW_KEY_DOWN:
            k = TW_KEY_DOWN;
            break;
        case GLFW_KEY_LEFT:
            k = TW_KEY_LEFT;
            break;
        case GLFW_KEY_RIGHT:
            k = TW_KEY_RIGHT;
            break;
        case GLFW_KEY_TAB:
            k = TW_KEY_TAB;
            break;
        case GLFW_KEY_ENTER:
            k = TW_KEY_RETURN;
            break;
        case GLFW_KEY_BACKSPACE:
            k = TW_KEY_BACKSPACE;
            break;
        case GLFW_KEY_INSERT:
            k = TW_KEY_INSERT;
            break;
        case GLFW_KEY_DELETE:
            k = TW_KEY_DELETE;
            break;
		case GLFW_KEY_PAGE_UP:
            k = TW_KEY_PAGE_UP;
            break;
        case GLFW_KEY_PAGE_DOWN:
            k = TW_KEY_PAGE_DOWN;
            break;
        case GLFW_KEY_HOME:
            k = TW_KEY_HOME;
            break;
        case GLFW_KEY_END:
            k = TW_KEY_END;
            break;
        case GLFW_KEY_KP_ENTER:
            k = TW_KEY_RETURN;
            break;
        case GLFW_KEY_KP_DIVIDE:
            if( testkp )
                k = '/';
            break;
        case GLFW_KEY_KP_MULTIPLY:
            if( testkp )
                k = '*';
            break;
        case GLFW_KEY_KP_SUBTRACT:
            if( testkp )
                k = '-';
            break;
        case GLFW_KEY_KP_ADD:
            if( testkp )
                k = '+';
            break;
        case GLFW_KEY_KP_DECIMAL:
            if( testkp )
                k = '.';
            break;
        case GLFW_KEY_KP_EQUAL:
            if( testkp )
                k = '=';
            break;
        }
    }

	return k ? TwKeyPressed(k, mod) : 0;
}


int TW_CALL TwEventCharModsGLFW3(GLFWwindow *window, int glfwChar, int glfwMods)
{
    if( (glfwChar & 0xff00)==0 )
        return TwKeyPressed(glfwChar, convertModifiers(glfwMods));

    return 0;
}


int TW_CALL TwEventCursorPosGLFW3(GLFWwindow *window, double xpos, double ypos)
{
	return TwMouseMotion((int)xpos, (int)ypos);
}


int TW_CALL TwEventScrollGLFW3(GLFWwindow *window, double xoffset, double yoffset)
{
	static int wheelPos = 0;
	wheelPos += (int)yoffset;
	return TwMouseWheel(wheelPos);
}


// functions with __cdecl calling convension
TW_API int TW_CDECL_CALL TwEventMouseButtonGLFW3cdecl(GLFWwindow *window, int glfwButton, int glfwAction, int glfwMods)
{
	return TwEventMouseButtonGLFW3(window, glfwButton, glfwAction, glfwMods);
}
TW_API int TW_CDECL_CALL TwEventKeyGLFW3cdecl(GLFWwindow *window, int glfwKey, int glfwScancode, int glfwAction, int glfwMods)
{
	return TwEventKeyGLFW3(window, glfwKey, glfwScancode, glfwAction, glfwMods);
}
TW_API int TW_CDECL_CALL TwEventCharModsGLFW3cdecl(GLFWwindow *window, int glfwChar, int glfwMods)
{
	return TwEventCharModsGLFW3(window, glfwChar, glfwMods);
}
TW_API int TW_CDECL_CALL TwEventCursorPosGLFW3cdecl(GLFWwindow *window, double xpos, double ypos)
{
    return TwMouseMotion((int)xpos, (int)ypos);
}
TW_API int TW_CDECL_CALL TwEventScrollGLFW3cdecl(GLFWwindow *window, double xoffset, double yoffset)
{
    return TwEventScrollGLFW3(window, xoffset, yoffset);
}
