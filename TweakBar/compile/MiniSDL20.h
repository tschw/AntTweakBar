#if !defined MINI_SDL_INCLUDED
#define MINI_SDL_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#define SDL_MAJOR_VERSION	2
#define SDL_MINOR_VERSION	0

#include <stdint.h>

typedef int8_t Sint8;
typedef uint8_t Uint8;
typedef int16_t Sint16;
typedef uint16_t Uint16;
typedef int32_t Sint32;
typedef uint32_t Uint32;
typedef int64_t Sint64;
typedef uint64_t Uint64;

typedef enum
{
	SDL_SCANCODE_UNKNOWN = 0,

	/**
	 *	\name Usage page 0x07
	 *
	 *	These values are from usage page 0x07 (USB keyboard page).
	 */
	/* @{ */

	SDL_SCANCODE_A = 4,
	SDL_SCANCODE_B = 5,
	SDL_SCANCODE_C = 6,
	SDL_SCANCODE_D = 7,
	SDL_SCANCODE_E = 8,
	SDL_SCANCODE_F = 9,
	SDL_SCANCODE_G = 10,
	SDL_SCANCODE_H = 11,
	SDL_SCANCODE_I = 12,
	SDL_SCANCODE_J = 13,
	SDL_SCANCODE_K = 14,
	SDL_SCANCODE_L = 15,
	SDL_SCANCODE_M = 16,
	SDL_SCANCODE_N = 17,
	SDL_SCANCODE_O = 18,
	SDL_SCANCODE_P = 19,
	SDL_SCANCODE_Q = 20,
	SDL_SCANCODE_R = 21,
	SDL_SCANCODE_S = 22,
	SDL_SCANCODE_T = 23,
	SDL_SCANCODE_U = 24,
	SDL_SCANCODE_V = 25,
	SDL_SCANCODE_W = 26,
	SDL_SCANCODE_X = 27,
	SDL_SCANCODE_Y = 28,
	SDL_SCANCODE_Z = 29,

	SDL_SCANCODE_1 = 30,
	SDL_SCANCODE_2 = 31,
	SDL_SCANCODE_3 = 32,
	SDL_SCANCODE_4 = 33,
	SDL_SCANCODE_5 = 34,
	SDL_SCANCODE_6 = 35,
	SDL_SCANCODE_7 = 36,
	SDL_SCANCODE_8 = 37,
	SDL_SCANCODE_9 = 38,
	SDL_SCANCODE_0 = 39,

	SDL_SCANCODE_RETURN = 40,
	SDL_SCANCODE_ESCAPE = 41,
	SDL_SCANCODE_BACKSPACE = 42,
	SDL_SCANCODE_TAB = 43,
	SDL_SCANCODE_SPACE = 44,

	SDL_SCANCODE_MINUS = 45,
	SDL_SCANCODE_EQUALS = 46,
	SDL_SCANCODE_LEFTBRACKET = 47,
	SDL_SCANCODE_RIGHTBRACKET = 48,
	SDL_SCANCODE_BACKSLASH = 49, /**< Located at the lower left of the return
								  *   key on ISO keyboards and at the right end
								  *   of the QWERTY row on ANSI keyboards.
								  *   Produces REVERSE SOLIDUS (backslash) and
								  *   VERTICAL LINE in a US layout, REVERSE
								  *   SOLIDUS and VERTICAL LINE in a UK Mac
								  *   layout, NUMBER SIGN and TILDE in a UK
								  *   Windows layout, DOLLAR SIGN and POUND SIGN
								  *   in a Swiss German layout, NUMBER SIGN and
								  *   APOSTROPHE in a German layout, GRAVE
								  *   ACCENT and POUND SIGN in a French Mac
								  *   layout, and ASTERISK and MICRO SIGN in a
								  *   French Windows layout.
								  */
	SDL_SCANCODE_NONUSHASH = 50, /**< ISO USB keyboards actually use this code
								  *   instead of 49 for the same key, but all
								  *   OSes I've seen treat the two codes
								  *   identically. So, as an implementor, unless
								  *   your keyboard generates both of those
								  *   codes and your OS treats them differently,
								  *   you should generate SDL_SCANCODE_BACKSLASH
								  *   instead of this code. As a user, you
								  *   should not rely on this code because SDL
								  *   will never generate it with most (all?)
								  *   keyboards.
								  */
	SDL_SCANCODE_SEMICOLON = 51,
	SDL_SCANCODE_APOSTROPHE = 52,
	SDL_SCANCODE_GRAVE = 53, /**< Located in the top left corner (on both ANSI
							  *   and ISO keyboards). Produces GRAVE ACCENT and
							  *   TILDE in a US Windows layout and in US and UK
							  *   Mac layouts on ANSI keyboards, GRAVE ACCENT
							  *   and NOT SIGN in a UK Windows layout, SECTION
							  *   SIGN and PLUS-MINUS SIGN in US and UK Mac
							  *   layouts on ISO keyboards, SECTION SIGN and
							  *   DEGREE SIGN in a Swiss German layout (Mac:
							  *   only on ISO keyboards), CIRCUMFLEX ACCENT and
							  *   DEGREE SIGN in a German layout (Mac: only on
							  *   ISO keyboards), SUPERSCRIPT TWO and TILDE in a
							  *   French Windows layout, COMMERCIAL AT and
							  *   NUMBER SIGN in a French Mac layout on ISO
							  *   keyboards, and LESS-THAN SIGN and GREATER-THAN
							  *   SIGN in a Swiss German, German, or French Mac
							  *   layout on ANSI keyboards.
							  */
	SDL_SCANCODE_COMMA = 54,
	SDL_SCANCODE_PERIOD = 55,
	SDL_SCANCODE_SLASH = 56,

	SDL_SCANCODE_CAPSLOCK = 57,

	SDL_SCANCODE_F1 = 58,
	SDL_SCANCODE_F2 = 59,
	SDL_SCANCODE_F3 = 60,
	SDL_SCANCODE_F4 = 61,
	SDL_SCANCODE_F5 = 62,
	SDL_SCANCODE_F6 = 63,
	SDL_SCANCODE_F7 = 64,
	SDL_SCANCODE_F8 = 65,
	SDL_SCANCODE_F9 = 66,
	SDL_SCANCODE_F10 = 67,
	SDL_SCANCODE_F11 = 68,
	SDL_SCANCODE_F12 = 69,

	SDL_SCANCODE_PRINTSCREEN = 70,
	SDL_SCANCODE_SCROLLLOCK = 71,
	SDL_SCANCODE_PAUSE = 72,
	SDL_SCANCODE_INSERT = 73, /**< insert on PC, help on some Mac keyboards (but
								   does send code 73, not 117) */
	SDL_SCANCODE_HOME = 74,
	SDL_SCANCODE_PAGEUP = 75,
	SDL_SCANCODE_DELETE = 76,
	SDL_SCANCODE_END = 77,
	SDL_SCANCODE_PAGEDOWN = 78,
	SDL_SCANCODE_RIGHT = 79,
	SDL_SCANCODE_LEFT = 80,
	SDL_SCANCODE_DOWN = 81,
	SDL_SCANCODE_UP = 82,

	SDL_SCANCODE_NUMLOCKCLEAR = 83, /**< num lock on PC, clear on Mac keyboards
									 */
	SDL_SCANCODE_KP_DIVIDE = 84,
	SDL_SCANCODE_KP_MULTIPLY = 85,
	SDL_SCANCODE_KP_MINUS = 86,
	SDL_SCANCODE_KP_PLUS = 87,
	SDL_SCANCODE_KP_ENTER = 88,
	SDL_SCANCODE_KP_1 = 89,
	SDL_SCANCODE_KP_2 = 90,
	SDL_SCANCODE_KP_3 = 91,
	SDL_SCANCODE_KP_4 = 92,
	SDL_SCANCODE_KP_5 = 93,
	SDL_SCANCODE_KP_6 = 94,
	SDL_SCANCODE_KP_7 = 95,
	SDL_SCANCODE_KP_8 = 96,
	SDL_SCANCODE_KP_9 = 97,
	SDL_SCANCODE_KP_0 = 98,
	SDL_SCANCODE_KP_PERIOD = 99,

	SDL_SCANCODE_NONUSBACKSLASH = 100, /**< This is the additional key that ISO
										*	keyboards have over ANSI ones,
										*	located between left shift and Y.
										*	Produces GRAVE ACCENT and TILDE in a
										*	US or UK Mac layout, REVERSE SOLIDUS
										*	(backslash) and VERTICAL LINE in a
										*	US or UK Windows layout, and
										*	LESS-THAN SIGN and GREATER-THAN SIGN
										*	in a Swiss German, German, or French
										*	layout. */
	SDL_SCANCODE_APPLICATION = 101, /**< windows contextual menu, compose */
	SDL_SCANCODE_POWER = 102, /**< The USB document says this is a status flag,
							   *   not a physical key - but some Mac keyboards
							   *   do have a power key. */
	SDL_SCANCODE_KP_EQUALS = 103,
	SDL_SCANCODE_F13 = 104,
	SDL_SCANCODE_F14 = 105,
	SDL_SCANCODE_F15 = 106,
	SDL_SCANCODE_F16 = 107,
	SDL_SCANCODE_F17 = 108,
	SDL_SCANCODE_F18 = 109,
	SDL_SCANCODE_F19 = 110,
	SDL_SCANCODE_F20 = 111,
	SDL_SCANCODE_F21 = 112,
	SDL_SCANCODE_F22 = 113,
	SDL_SCANCODE_F23 = 114,
	SDL_SCANCODE_F24 = 115,
	SDL_SCANCODE_EXECUTE = 116,
	SDL_SCANCODE_HELP = 117,
	SDL_SCANCODE_MENU = 118,
	SDL_SCANCODE_SELECT = 119,
	SDL_SCANCODE_STOP = 120,
	SDL_SCANCODE_AGAIN = 121,	/**< redo */
	SDL_SCANCODE_UNDO = 122,
	SDL_SCANCODE_CUT = 123,
	SDL_SCANCODE_COPY = 124,
	SDL_SCANCODE_PASTE = 125,
	SDL_SCANCODE_FIND = 126,
	SDL_SCANCODE_MUTE = 127,
	SDL_SCANCODE_VOLUMEUP = 128,
	SDL_SCANCODE_VOLUMEDOWN = 129,
/* not sure whether there's a reason to enable these */
/*	   SDL_SCANCODE_LOCKINGCAPSLOCK = 130,	*/
/*	   SDL_SCANCODE_LOCKINGNUMLOCK = 131, */
/*	   SDL_SCANCODE_LOCKINGSCROLLLOCK = 132, */
	SDL_SCANCODE_KP_COMMA = 133,
	SDL_SCANCODE_KP_EQUALSAS400 = 134,

	SDL_SCANCODE_INTERNATIONAL1 = 135, /**< used on Asian keyboards, see
											footnotes in USB doc */
	SDL_SCANCODE_INTERNATIONAL2 = 136,
	SDL_SCANCODE_INTERNATIONAL3 = 137, /**< Yen */
	SDL_SCANCODE_INTERNATIONAL4 = 138,
	SDL_SCANCODE_INTERNATIONAL5 = 139,
	SDL_SCANCODE_INTERNATIONAL6 = 140,
	SDL_SCANCODE_INTERNATIONAL7 = 141,
	SDL_SCANCODE_INTERNATIONAL8 = 142,
	SDL_SCANCODE_INTERNATIONAL9 = 143,
	SDL_SCANCODE_LANG1 = 144, /**< Hangul/English toggle */
	SDL_SCANCODE_LANG2 = 145, /**< Hanja conversion */
	SDL_SCANCODE_LANG3 = 146, /**< Katakana */
	SDL_SCANCODE_LANG4 = 147, /**< Hiragana */
	SDL_SCANCODE_LANG5 = 148, /**< Zenkaku/Hankaku */
	SDL_SCANCODE_LANG6 = 149, /**< reserved */
	SDL_SCANCODE_LANG7 = 150, /**< reserved */
	SDL_SCANCODE_LANG8 = 151, /**< reserved */
	SDL_SCANCODE_LANG9 = 152, /**< reserved */

	SDL_SCANCODE_ALTERASE = 153, /**< Erase-Eaze */
	SDL_SCANCODE_SYSREQ = 154,
	SDL_SCANCODE_CANCEL = 155,
	SDL_SCANCODE_CLEAR = 156,
	SDL_SCANCODE_PRIOR = 157,
	SDL_SCANCODE_RETURN2 = 158,
	SDL_SCANCODE_SEPARATOR = 159,
	SDL_SCANCODE_OUT = 160,
	SDL_SCANCODE_OPER = 161,
	SDL_SCANCODE_CLEARAGAIN = 162,
	SDL_SCANCODE_CRSEL = 163,
	SDL_SCANCODE_EXSEL = 164,

	SDL_SCANCODE_KP_00 = 176,
	SDL_SCANCODE_KP_000 = 177,
	SDL_SCANCODE_THOUSANDSSEPARATOR = 178,
	SDL_SCANCODE_DECIMALSEPARATOR = 179,
	SDL_SCANCODE_CURRENCYUNIT = 180,
	SDL_SCANCODE_CURRENCYSUBUNIT = 181,
	SDL_SCANCODE_KP_LEFTPAREN = 182,
	SDL_SCANCODE_KP_RIGHTPAREN = 183,
	SDL_SCANCODE_KP_LEFTBRACE = 184,
	SDL_SCANCODE_KP_RIGHTBRACE = 185,
	SDL_SCANCODE_KP_TAB = 186,
	SDL_SCANCODE_KP_BACKSPACE = 187,
	SDL_SCANCODE_KP_A = 188,
	SDL_SCANCODE_KP_B = 189,
	SDL_SCANCODE_KP_C = 190,
	SDL_SCANCODE_KP_D = 191,
	SDL_SCANCODE_KP_E = 192,
	SDL_SCANCODE_KP_F = 193,
	SDL_SCANCODE_KP_XOR = 194,
	SDL_SCANCODE_KP_POWER = 195,
	SDL_SCANCODE_KP_PERCENT = 196,
	SDL_SCANCODE_KP_LESS = 197,
	SDL_SCANCODE_KP_GREATER = 198,
	SDL_SCANCODE_KP_AMPERSAND = 199,
	SDL_SCANCODE_KP_DBLAMPERSAND = 200,
	SDL_SCANCODE_KP_VERTICALBAR = 201,
	SDL_SCANCODE_KP_DBLVERTICALBAR = 202,
	SDL_SCANCODE_KP_COLON = 203,
	SDL_SCANCODE_KP_HASH = 204,
	SDL_SCANCODE_KP_SPACE = 205,
	SDL_SCANCODE_KP_AT = 206,
	SDL_SCANCODE_KP_EXCLAM = 207,
	SDL_SCANCODE_KP_MEMSTORE = 208,
	SDL_SCANCODE_KP_MEMRECALL = 209,
	SDL_SCANCODE_KP_MEMCLEAR = 210,
	SDL_SCANCODE_KP_MEMADD = 211,
	SDL_SCANCODE_KP_MEMSUBTRACT = 212,
	SDL_SCANCODE_KP_MEMMULTIPLY = 213,
	SDL_SCANCODE_KP_MEMDIVIDE = 214,
	SDL_SCANCODE_KP_PLUSMINUS = 215,
	SDL_SCANCODE_KP_CLEAR = 216,
	SDL_SCANCODE_KP_CLEARENTRY = 217,
	SDL_SCANCODE_KP_BINARY = 218,
	SDL_SCANCODE_KP_OCTAL = 219,
	SDL_SCANCODE_KP_DECIMAL = 220,
	SDL_SCANCODE_KP_HEXADECIMAL = 221,

	SDL_SCANCODE_LCTRL = 224,
	SDL_SCANCODE_LSHIFT = 225,
	SDL_SCANCODE_LALT = 226, /**< alt, option */
	SDL_SCANCODE_LGUI = 227, /**< windows, command (apple), meta */
	SDL_SCANCODE_RCTRL = 228,
	SDL_SCANCODE_RSHIFT = 229,
	SDL_SCANCODE_RALT = 230, /**< alt gr, option */
	SDL_SCANCODE_RGUI = 231, /**< windows, command (apple), meta */

	SDL_SCANCODE_MODE = 257,	/**< I'm not sure if this is really not covered
								 *	 by any of the above, but since there's a
								 *	 special KMOD_MODE for it I'm adding it here
								 */

	/* @} *//* Usage page 0x07 */

	/**
	 *	\name Usage page 0x0C
	 *
	 *	These values are mapped from usage page 0x0C (USB consumer page).
	 */
	/* @{ */

	SDL_SCANCODE_AUDIONEXT = 258,
	SDL_SCANCODE_AUDIOPREV = 259,
	SDL_SCANCODE_AUDIOSTOP = 260,
	SDL_SCANCODE_AUDIOPLAY = 261,
	SDL_SCANCODE_AUDIOMUTE = 262,
	SDL_SCANCODE_MEDIASELECT = 263,
	SDL_SCANCODE_WWW = 264,
	SDL_SCANCODE_MAIL = 265,
	SDL_SCANCODE_CALCULATOR = 266,
	SDL_SCANCODE_COMPUTER = 267,
	SDL_SCANCODE_AC_SEARCH = 268,
	SDL_SCANCODE_AC_HOME = 269,
	SDL_SCANCODE_AC_BACK = 270,
	SDL_SCANCODE_AC_FORWARD = 271,
	SDL_SCANCODE_AC_STOP = 272,
	SDL_SCANCODE_AC_REFRESH = 273,
	SDL_SCANCODE_AC_BOOKMARKS = 274,

	/* @} *//* Usage page 0x0C */

	/**
	 *	\name Walther keys
	 *
	 *	These are values that Christian Walther added (for mac keyboard?).
	 */
	/* @{ */

	SDL_SCANCODE_BRIGHTNESSDOWN = 275,
	SDL_SCANCODE_BRIGHTNESSUP = 276,
	SDL_SCANCODE_DISPLAYSWITCH = 277, /**< display mirroring/dual display
										   switch, video mode switch */
	SDL_SCANCODE_KBDILLUMTOGGLE = 278,
	SDL_SCANCODE_KBDILLUMDOWN = 279,
	SDL_SCANCODE_KBDILLUMUP = 280,
	SDL_SCANCODE_EJECT = 281,
	SDL_SCANCODE_SLEEP = 282,

	SDL_SCANCODE_APP1 = 283,
	SDL_SCANCODE_APP2 = 284,

	/* @} *//* Walther keys */

	/* Add any other keys here. */

	SDL_NUM_SCANCODES = 512 /**< not a key, just marks the number of scancodes
								 for array bounds */
} SDL_Scancode;

typedef Sint32 SDL_Keycode;
typedef Sint32 SDL_JoystickID;
typedef Sint64 SDL_TouchID;
typedef Sint64 SDL_FingerID;
typedef Sint64 SDL_GestureID;

typedef struct SDL_Keysym
{
	SDL_Scancode scancode;		/**< SDL physical key code - see ::SDL_Scancode for details */
	SDL_Keycode sym;			/**< SDL virtual key code - see ::SDL_Keycode for details */
	Uint16 mod;					/**< current key modifiers */
	Uint32 unused;
} SDL_Keysym;

#define SDL_RELEASED	0
#define SDL_PRESSED 1

/**
 * \brief The types of events that can be delivered.
 */
typedef enum
{
	SDL_FIRSTEVENT	   = 0,		/**< Unused (do not remove) */

	/* Application events */
	SDL_QUIT		   = 0x100, /**< User-requested quit */

	/* These application events have special meaning on iOS, see README-ios.txt for details */
	SDL_APP_TERMINATING,		/**< The application is being terminated by the OS
									 Called on iOS in applicationWillTerminate()
									 Called on Android in onDestroy()
								*/
	SDL_APP_LOWMEMORY,			/**< The application is low on memory, free memory if possible.
									 Called on iOS in applicationDidReceiveMemoryWarning()
									 Called on Android in onLowMemory()
								*/
	SDL_APP_WILLENTERBACKGROUND, /**< The application is about to enter the background
									 Called on iOS in applicationWillResignActive()
									 Called on Android in onPause()
								*/
	SDL_APP_DIDENTERBACKGROUND, /**< The application did enter the background and may not get CPU for some time
									 Called on iOS in applicationDidEnterBackground()
									 Called on Android in onPause()
								*/
	SDL_APP_WILLENTERFOREGROUND, /**< The application is about to enter the foreground
									 Called on iOS in applicationWillEnterForeground()
									 Called on Android in onResume()
								*/
	SDL_APP_DIDENTERFOREGROUND, /**< The application is now interactive
									 Called on iOS in applicationDidBecomeActive()
									 Called on Android in onResume()
								*/

	/* Window events */
	SDL_WINDOWEVENT    = 0x200, /**< Window state change */
	SDL_SYSWMEVENT,				/**< System specific event */

	/* Keyboard events */
	SDL_KEYDOWN		   = 0x300, /**< Key pressed */
	SDL_KEYUP,					/**< Key released */
	SDL_TEXTEDITING,			/**< Keyboard text editing (composition) */
	SDL_TEXTINPUT,				/**< Keyboard text input */

	/* Mouse events */
	SDL_MOUSEMOTION    = 0x400, /**< Mouse moved */
	SDL_MOUSEBUTTONDOWN,		/**< Mouse button pressed */
	SDL_MOUSEBUTTONUP,			/**< Mouse button released */
	SDL_MOUSEWHEEL,				/**< Mouse wheel motion */

	/* Joystick events */
	SDL_JOYAXISMOTION  = 0x600, /**< Joystick axis motion */
	SDL_JOYBALLMOTION,			/**< Joystick trackball motion */
	SDL_JOYHATMOTION,			/**< Joystick hat position change */
	SDL_JOYBUTTONDOWN,			/**< Joystick button pressed */
	SDL_JOYBUTTONUP,			/**< Joystick button released */
	SDL_JOYDEVICEADDED,			/**< A new joystick has been inserted into the system */
	SDL_JOYDEVICEREMOVED,		/**< An opened joystick has been removed */

	/* Game controller events */
	SDL_CONTROLLERAXISMOTION  = 0x650, /**< Game controller axis motion */
	SDL_CONTROLLERBUTTONDOWN,		   /**< Game controller button pressed */
	SDL_CONTROLLERBUTTONUP,			   /**< Game controller button released */
	SDL_CONTROLLERDEVICEADDED,		   /**< A new Game controller has been inserted into the system */
	SDL_CONTROLLERDEVICEREMOVED,	   /**< An opened Game controller has been removed */
	SDL_CONTROLLERDEVICEREMAPPED,	   /**< The controller mapping was updated */

	/* Touch events */
	SDL_FINGERDOWN		= 0x700,
	SDL_FINGERUP,
	SDL_FINGERMOTION,

	/* Gesture events */
	SDL_DOLLARGESTURE	= 0x800,
	SDL_DOLLARRECORD,
	SDL_MULTIGESTURE,

	/* Clipboard events */
	SDL_CLIPBOARDUPDATE = 0x900, /**< The clipboard changed */

	/* Drag and drop events */
	SDL_DROPFILE		= 0x1000, /**< The system requests a file open */

	/* Render events */
	SDL_RENDER_TARGETS_RESET = 0x2000, /**< The render targets have been reset */

	/** Events ::SDL_USEREVENT through ::SDL_LASTEVENT are for your use,
	 *	and should be allocated with SDL_RegisterEvents()
	 */
	SDL_USEREVENT	 = 0x8000,

	/**
	 *	This last event is only for bounding internal arrays
	 */
	SDL_LASTEVENT	 = 0xFFFF
} SDL_EventType;

/**
 *	\brief Fields shared by every event
 */
typedef struct SDL_CommonEvent
{
	Uint32 type;
	Uint32 timestamp;
} SDL_CommonEvent;

/**
 *	\brief Window state change event data (event.window.*)
 */
typedef struct SDL_WindowEvent
{
	Uint32 type;		/**< ::SDL_WINDOWEVENT */
	Uint32 timestamp;
	Uint32 windowID;	/**< The associated window */
	Uint8 event;		/**< ::SDL_WindowEventID */
	Uint8 padding1;
	Uint8 padding2;
	Uint8 padding3;
	Sint32 data1;		/**< event dependent data */
	Sint32 data2;		/**< event dependent data */
} SDL_WindowEvent;

/**
 *	\brief Keyboard button event structure (event.key.*)
 */
typedef struct SDL_KeyboardEvent
{
	Uint32 type;		/**< ::SDL_KEYDOWN or ::SDL_KEYUP */
	Uint32 timestamp;
	Uint32 windowID;	/**< The window with keyboard focus, if any */
	Uint8 state;		/**< ::SDL_PRESSED or ::SDL_RELEASED */
	Uint8 repeat;		/**< Non-zero if this is a key repeat */
	Uint8 padding2;
	Uint8 padding3;
	SDL_Keysym keysym;	/**< The key that was pressed or released */
} SDL_KeyboardEvent;

#define SDL_TEXTEDITINGEVENT_TEXT_SIZE (32)
/**
 *	\brief Keyboard text editing event structure (event.edit.*)
 */
typedef struct SDL_TextEditingEvent
{
	Uint32 type;								/**< ::SDL_TEXTEDITING */
	Uint32 timestamp;
	Uint32 windowID;							/**< The window with keyboard focus, if any */
	char text[SDL_TEXTEDITINGEVENT_TEXT_SIZE];	/**< The editing text */
	Sint32 start;								/**< The start cursor of selected editing text */
	Sint32 length;								/**< The length of selected editing text */
} SDL_TextEditingEvent;


#define SDL_TEXTINPUTEVENT_TEXT_SIZE (32)
/**
 *	\brief Keyboard text input event structure (event.text.*)
 */
typedef struct SDL_TextInputEvent
{
	Uint32 type;							  /**< ::SDL_TEXTINPUT */
	Uint32 timestamp;
	Uint32 windowID;						  /**< The window with keyboard focus, if any */
	char text[SDL_TEXTINPUTEVENT_TEXT_SIZE];  /**< The input text */
} SDL_TextInputEvent;

/**
 *	\brief Mouse motion event structure (event.motion.*)
 */
typedef struct SDL_MouseMotionEvent
{
	Uint32 type;		/**< ::SDL_MOUSEMOTION */
	Uint32 timestamp;
	Uint32 windowID;	/**< The window with mouse focus, if any */
	Uint32 which;		/**< The mouse instance id, or SDL_TOUCH_MOUSEID */
	Uint32 state;		/**< The current button state */
	Sint32 x;			/**< X coordinate, relative to window */
	Sint32 y;			/**< Y coordinate, relative to window */
	Sint32 xrel;		/**< The relative motion in the X direction */
	Sint32 yrel;		/**< The relative motion in the Y direction */
} SDL_MouseMotionEvent;

/**
 *	\brief Mouse button event structure (event.button.*)
 */
typedef struct SDL_MouseButtonEvent
{
	Uint32 type;		/**< ::SDL_MOUSEBUTTONDOWN or ::SDL_MOUSEBUTTONUP */
	Uint32 timestamp;
	Uint32 windowID;	/**< The window with mouse focus, if any */
	Uint32 which;		/**< The mouse instance id, or SDL_TOUCH_MOUSEID */
	Uint8 button;		/**< The mouse button index */
	Uint8 state;		/**< ::SDL_PRESSED or ::SDL_RELEASED */
	Uint8 clicks;		/**< 1 for single-click, 2 for double-click, etc. */
	Uint8 padding1;
	Sint32 x;			/**< X coordinate, relative to window */
	Sint32 y;			/**< Y coordinate, relative to window */
} SDL_MouseButtonEvent;

/**
 *	\brief Mouse wheel event structure (event.wheel.*)
 */
typedef struct SDL_MouseWheelEvent
{
	Uint32 type;		/**< ::SDL_MOUSEWHEEL */
	Uint32 timestamp;
	Uint32 windowID;	/**< The window with mouse focus, if any */
	Uint32 which;		/**< The mouse instance id, or SDL_TOUCH_MOUSEID */
	Sint32 x;			/**< The amount scrolled horizontally, positive to the right and negative to the left */
	Sint32 y;			/**< The amount scrolled vertically, positive away from the user and negative toward the user */
} SDL_MouseWheelEvent;

/**
 *	\brief Joystick axis motion event structure (event.jaxis.*)
 */
typedef struct SDL_JoyAxisEvent
{
	Uint32 type;		/**< ::SDL_JOYAXISMOTION */
	Uint32 timestamp;
	SDL_JoystickID which; /**< The joystick instance id */
	Uint8 axis;			/**< The joystick axis index */
	Uint8 padding1;
	Uint8 padding2;
	Uint8 padding3;
	Sint16 value;		/**< The axis value (range: -32768 to 32767) */
	Uint16 padding4;
} SDL_JoyAxisEvent;

/**
 *	\brief Joystick trackball motion event structure (event.jball.*)
 */
typedef struct SDL_JoyBallEvent
{
	Uint32 type;		/**< ::SDL_JOYBALLMOTION */
	Uint32 timestamp;
	SDL_JoystickID which; /**< The joystick instance id */
	Uint8 ball;			/**< The joystick trackball index */
	Uint8 padding1;
	Uint8 padding2;
	Uint8 padding3;
	Sint16 xrel;		/**< The relative motion in the X direction */
	Sint16 yrel;		/**< The relative motion in the Y direction */
} SDL_JoyBallEvent;

/**
 *	\brief Joystick hat position change event structure (event.jhat.*)
 */
typedef struct SDL_JoyHatEvent
{
	Uint32 type;		/**< ::SDL_JOYHATMOTION */
	Uint32 timestamp;
	SDL_JoystickID which; /**< The joystick instance id */
	Uint8 hat;			/**< The joystick hat index */
	Uint8 value;		/**< The hat position value.
						 *	 \sa ::SDL_HAT_LEFTUP ::SDL_HAT_UP ::SDL_HAT_RIGHTUP
						 *	 \sa ::SDL_HAT_LEFT ::SDL_HAT_CENTERED ::SDL_HAT_RIGHT
						 *	 \sa ::SDL_HAT_LEFTDOWN ::SDL_HAT_DOWN ::SDL_HAT_RIGHTDOWN
						 *
						 *	 Note that zero means the POV is centered.
						 */
	Uint8 padding1;
	Uint8 padding2;
} SDL_JoyHatEvent;

/**
 *	\brief Joystick button event structure (event.jbutton.*)
 */
typedef struct SDL_JoyButtonEvent
{
	Uint32 type;		/**< ::SDL_JOYBUTTONDOWN or ::SDL_JOYBUTTONUP */
	Uint32 timestamp;
	SDL_JoystickID which; /**< The joystick instance id */
	Uint8 button;		/**< The joystick button index */
	Uint8 state;		/**< ::SDL_PRESSED or ::SDL_RELEASED */
	Uint8 padding1;
	Uint8 padding2;
} SDL_JoyButtonEvent;

/**
 *	\brief Joystick device event structure (event.jdevice.*)
 */
typedef struct SDL_JoyDeviceEvent
{
	Uint32 type;		/**< ::SDL_JOYDEVICEADDED or ::SDL_JOYDEVICEREMOVED */
	Uint32 timestamp;
	Sint32 which;		/**< The joystick device index for the ADDED event, instance id for the REMOVED event */
} SDL_JoyDeviceEvent;


/**
 *	\brief Game controller axis motion event structure (event.caxis.*)
 */
typedef struct SDL_ControllerAxisEvent
{
	Uint32 type;		/**< ::SDL_CONTROLLERAXISMOTION */
	Uint32 timestamp;
	SDL_JoystickID which; /**< The joystick instance id */
	Uint8 axis;			/**< The controller axis (SDL_GameControllerAxis) */
	Uint8 padding1;
	Uint8 padding2;
	Uint8 padding3;
	Sint16 value;		/**< The axis value (range: -32768 to 32767) */
	Uint16 padding4;
} SDL_ControllerAxisEvent;


/**
 *	\brief Game controller button event structure (event.cbutton.*)
 */
typedef struct SDL_ControllerButtonEvent
{
	Uint32 type;		/**< ::SDL_CONTROLLERBUTTONDOWN or ::SDL_CONTROLLERBUTTONUP */
	Uint32 timestamp;
	SDL_JoystickID which; /**< The joystick instance id */
	Uint8 button;		/**< The controller button (SDL_GameControllerButton) */
	Uint8 state;		/**< ::SDL_PRESSED or ::SDL_RELEASED */
	Uint8 padding1;
	Uint8 padding2;
} SDL_ControllerButtonEvent;


/**
 *	\brief Controller device event structure (event.cdevice.*)
 */
typedef struct SDL_ControllerDeviceEvent
{
	Uint32 type;		/**< ::SDL_CONTROLLERDEVICEADDED, ::SDL_CONTROLLERDEVICEREMOVED, or ::SDL_CONTROLLERDEVICEREMAPPED */
	Uint32 timestamp;
	Sint32 which;		/**< The joystick device index for the ADDED event, instance id for the REMOVED or REMAPPED event */
} SDL_ControllerDeviceEvent;


/**
 *	\brief Touch finger event structure (event.tfinger.*)
 */
typedef struct SDL_TouchFingerEvent
{
	Uint32 type;		/**< ::SDL_FINGERMOTION or ::SDL_FINGERDOWN or ::SDL_FINGERUP */
	Uint32 timestamp;
	SDL_TouchID touchId; /**< The touch device id */
	SDL_FingerID fingerId;
	float x;			/**< Normalized in the range 0...1 */
	float y;			/**< Normalized in the range 0...1 */
	float dx;			/**< Normalized in the range 0...1 */
	float dy;			/**< Normalized in the range 0...1 */
	float pressure;		/**< Normalized in the range 0...1 */
} SDL_TouchFingerEvent;


/**
 *	\brief Multiple Finger Gesture Event (event.mgesture.*)
 */
typedef struct SDL_MultiGestureEvent
{
	Uint32 type;		/**< ::SDL_MULTIGESTURE */
	Uint32 timestamp;
	SDL_TouchID touchId; /**< The touch device index */
	float dTheta;
	float dDist;
	float x;
	float y;
	Uint16 numFingers;
	Uint16 padding;
} SDL_MultiGestureEvent;


/**
 * \brief Dollar Gesture Event (event.dgesture.*)
 */
typedef struct SDL_DollarGestureEvent
{
	Uint32 type;		/**< ::SDL_DOLLARGESTURE */
	Uint32 timestamp;
	SDL_TouchID touchId; /**< The touch device id */
	SDL_GestureID gestureId;
	Uint32 numFingers;
	float error;
	float x;			/**< Normalized center of gesture */
	float y;			/**< Normalized center of gesture */
} SDL_DollarGestureEvent;


/**
 *	\brief An event used to request a file open by the system (event.drop.*)
 *		   This event is disabled by default, you can enable it with SDL_EventState()
 *	\note If you enable this event, you must free the filename in the event.
 */
typedef struct SDL_DropEvent
{
	Uint32 type;		/**< ::SDL_DROPFILE */
	Uint32 timestamp;
	char *file;			/**< The file name, which should be freed with SDL_free() */
} SDL_DropEvent;


/**
 *	\brief The "quit requested" event
 */
typedef struct SDL_QuitEvent
{
	Uint32 type;		/**< ::SDL_QUIT */
	Uint32 timestamp;
} SDL_QuitEvent;

/**
 *	\brief OS Specific event
 */
typedef struct SDL_OSEvent
{
	Uint32 type;		/**< ::SDL_QUIT */
	Uint32 timestamp;
} SDL_OSEvent;

/**
 *	\brief A user-defined event type (event.user.*)
 */
typedef struct SDL_UserEvent
{
	Uint32 type;		/**< ::SDL_USEREVENT through ::SDL_LASTEVENT-1 */
	Uint32 timestamp;
	Uint32 windowID;	/**< The associated window if any */
	Sint32 code;		/**< User defined event code */
	void *data1;		/**< User defined data pointer */
	void *data2;		/**< User defined data pointer */
} SDL_UserEvent;


struct SDL_SysWMmsg;
typedef struct SDL_SysWMmsg SDL_SysWMmsg;

/**
 *	\brief A video driver dependent system event (event.syswm.*)
 *		   This event is disabled by default, you can enable it with SDL_EventState()
 *
 *	\note If you want to use this event, you should include SDL_syswm.h.
 */
typedef struct SDL_SysWMEvent
{
	Uint32 type;		/**< ::SDL_SYSWMEVENT */
	Uint32 timestamp;
	SDL_SysWMmsg *msg;	/**< driver dependent data, defined in SDL_syswm.h */
} SDL_SysWMEvent;

/**
 *	\brief General event structure
 */
typedef union SDL_Event
{
	Uint32 type;					/**< Event type, shared with all events */
	SDL_CommonEvent common;			/**< Common event data */
	SDL_WindowEvent window;			/**< Window event data */
	SDL_KeyboardEvent key;			/**< Keyboard event data */
	SDL_TextEditingEvent edit;		/**< Text editing event data */
	SDL_TextInputEvent text;		/**< Text input event data */
	SDL_MouseMotionEvent motion;	/**< Mouse motion event data */
	SDL_MouseButtonEvent button;	/**< Mouse button event data */
	SDL_MouseWheelEvent wheel;		/**< Mouse wheel event data */
	SDL_JoyAxisEvent jaxis;			/**< Joystick axis event data */
	SDL_JoyBallEvent jball;			/**< Joystick ball event data */
	SDL_JoyHatEvent jhat;			/**< Joystick hat event data */
	SDL_JoyButtonEvent jbutton;		/**< Joystick button event data */
	SDL_JoyDeviceEvent jdevice;		/**< Joystick device change event data */
	SDL_ControllerAxisEvent caxis;		/**< Game Controller axis event data */
	SDL_ControllerButtonEvent cbutton;	/**< Game Controller button event data */
	SDL_ControllerDeviceEvent cdevice;	/**< Game Controller device event data */
	SDL_QuitEvent quit;				/**< Quit request event data */
	SDL_UserEvent user;				/**< Custom event data */
	SDL_SysWMEvent syswm;			/**< System dependent window event data */
	SDL_TouchFingerEvent tfinger;	/**< Touch finger event data */
	SDL_MultiGestureEvent mgesture; /**< Gesture event data */
	SDL_DollarGestureEvent dgesture; /**< Gesture event data */
	SDL_DropEvent drop;				/**< Drag and drop event data */

	/* This is necessary for ABI compatibility between Visual C++ and GCC
	   Visual C++ will respect the push pack pragma and use 52 bytes for
	   this structure, and GCC will use the alignment of the largest datatype
	   within the union, which is 8 bytes.

	   So... we'll add padding to force the size to be 56 bytes for both.
	*/
	Uint8 padding[56];
} SDL_Event;


typedef enum
{
	SDL_WINDOWEVENT_NONE,			/**< Never used */
	SDL_WINDOWEVENT_SHOWN,			/**< Window has been shown */
	SDL_WINDOWEVENT_HIDDEN,			/**< Window has been hidden */
	SDL_WINDOWEVENT_EXPOSED,		/**< Window has been exposed and should be
										 redrawn */
	SDL_WINDOWEVENT_MOVED,			/**< Window has been moved to data1, data2
									 */
	SDL_WINDOWEVENT_RESIZED,		/**< Window has been resized to data1xdata2 */
	SDL_WINDOWEVENT_SIZE_CHANGED,	/**< The window size has changed, either as a result of an API call or through the system or user changing the window size. */
	SDL_WINDOWEVENT_MINIMIZED,		/**< Window has been minimized */
	SDL_WINDOWEVENT_MAXIMIZED,		/**< Window has been maximized */
	SDL_WINDOWEVENT_RESTORED,		/**< Window has been restored to normal size
										 and position */
	SDL_WINDOWEVENT_ENTER,			/**< Window has gained mouse focus */
	SDL_WINDOWEVENT_LEAVE,			/**< Window has lost mouse focus */
	SDL_WINDOWEVENT_FOCUS_GAINED,	/**< Window has gained keyboard focus */
	SDL_WINDOWEVENT_FOCUS_LOST,		/**< Window has lost keyboard focus */
	SDL_WINDOWEVENT_CLOSE			/**< The window manager requests that the
										 window be closed */
} SDL_WindowEventID;

#define SDLK_SCANCODE_MASK (1<<30)

#ifdef __cplusplus
}
#endif

#endif // !defined MINI_SDL_INCLUDED
