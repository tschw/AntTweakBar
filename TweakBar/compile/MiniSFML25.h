//	---------------------------------------------------------------------------
//
//	@file		MiniSFML25.h
//	@brief		A subset of SFML 2.5 definitions needed to compile helper
//				functions implemented in TwEventSFML25.cpp
//
//	@author		Nicolas Glade
//	notes:	  - Private header
//			  - AntTweakBar.dll does not need to link with SFML,
//				it just needs some definitions for its helper functions.
//			  - This header is provided to avoid the need of having SFML
//				installed to recompile AntTweakBar.
//				It declares a small and incomplete part of SFML classes.
//				For instance, many non-virtual methods have been stripped out.
//			  - Do not use this header in your own programs, better use the
//				SFML headers from the actual SFML library SDK :
//				http://www.sfml-dev.org
//
//	---------------------------------------------------------------------------

#if !defined MINI_SFML25_INCLUDED
#define MINI_SFML25_INCLUDED

#include <string>

namespace sf {
// prototype window
class Window;
class String {};
struct Vector2i;
struct Vector3f;
//#define SFML_WINDOW_API


// Keyboard -> SFML2.5
class Keyboard	{
    public:
        enum Key {
            Unknown = -1, A = 0, B, C,
            D, E, F, G,
            H, I, J, K,
            L, M, N, O,
            P, Q, R, S,
            T, U, V, W,
            X, Y, Z, Num0,
            Num1, Num2, Num3, Num4,
            Num5, Num6, Num7, Num8,
            Num9, Escape, LControl, LShift,
            LAlt, LSystem, RControl, RShift,
            RAlt, RSystem, Menu, LBracket,
            RBracket, Semicolon, Comma, Period,
            Quote, Slash, Backslash, Tilde,
            Equal, Hyphen, Space, Enter,
            Backspace, Tab, PageUp, PageDown,
            End, Home, Insert, Delete,
            Add, Subtract, Multiply, Divide,
            Left, Right, Up, Down,
            Numpad0, Numpad1, Numpad2, Numpad3,
            Numpad4, Numpad5, Numpad6, Numpad7,
            Numpad8, Numpad9, F1, F2,
            F3, F4, F5, F6,
            F7, F8, F9, F10,
            F11, F12, F13, F14,
            F15, Pause, KeyCount, Dash = Hyphen,
            BackSpace = Backspace, BackSlash = Backslash, SemiColon = Semicolon, Return = Enter
            }; // ends Key enum

        static bool isKeyPressed(Key key);
        static void setVirtualKeyboardVisible(bool visible);
    }; // ends Keyboard class

// Mouse -> SFML2.5
class Mouse {
    public:
        enum Button { Left, Right, Middle, XButton1, XButton2, Count };
        enum Wheel { VerticalWheel, HorizontalWheel };

        static bool isButtonPressed(Button button);
        static Vector2i getPosition();
        static Vector2i getPosition(const Window& relativeTo);
        static void setPosition(const Vector2i& position);
        static void setPosition(const Vector2i& position, const Window& relativeTo);
    };

// Joystick -> SFML2.5
class Joystick {
    public:
        enum { Count       = 8,  ButtonCount = 32, AxisCount   = 8 };
        enum Axis { X, Y, Z, R, U, V, PovX, PovY  };
        struct Identification {
            Identification();
            String name;
            unsigned int vendorId;
            unsigned int productId;
            };
        static bool isConnected(unsigned int joystick);
        static unsigned int getButtonCount(unsigned int joystick);
        static bool hasAxis(unsigned int joystick, Axis axis);
        static bool isButtonPressed(unsigned int joystick, unsigned int button);
        static float getAxisPosition(unsigned int joystick, Axis axis);
        static Identification getIdentification(unsigned int joystick);
        static void update();
    };

typedef unsigned char Uint8;
typedef unsigned int Uint32;

// Sensor -> SFML2.5
class Sensor {
    public:
        enum Type { Accelerometer, Gyroscope, Magnetometer, Gravity, UserAcceleration, Orientation, Count };
        static bool isAvailable(Type sensor);
        static void setEnabled(Type sensor, bool enabled);
        static Vector3f getValue(Type sensor);
    };

// Event -> SFML2.5
class Event {
    public :
        struct SizeEvent {
            unsigned int width, height;
            };
        struct KeyEvent {
            Keyboard::Key code;
            bool alt, control, shift, system;
            };
        struct TextEvent {
            Uint32 unicode;
            };
        struct MouseMoveEvent {
            int x, y;
            };
        struct MouseButtonEvent {
            Mouse::Button button;
            int x, y;
            };
        struct MouseWheelEvent {
            int delta, x, y;
            };
        struct MouseWheelScrollEvent {
            Mouse::Wheel wheel;
            float delta;
            int x,y;
            };
        struct JoystickConnectEvent {
            unsigned int joystickId;
            };
        struct JoystickMoveEvent {
            unsigned int joystickId;
            Joystick::Axis axis;
            float position;
            };
        struct JoystickButtonEvent {
            unsigned int joystickId, button;
            };
        struct TouchEvent {
            unsigned int finger;
            int x, y;
            };
        struct SensorEvent {
            Sensor::Type type;
            float x, y, z;
            };

        enum EventType {
            Closed, Resized, LostFocus, GainedFocus, TextEntered, KeyPressed, KeyReleased,
            MouseWheelMoved, MouseWheelScrolled, MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseEntered, MouseLeft, JoystickButtonPressed, JoystickButtonReleased, JoystickMoved, JoystickConnected, JoystickDisconnected, TouchBegan, TouchMoved, TouchEnd, SensorChanged, Count
            };

        EventType type;

        union {
            SizeEvent        size;
            KeyEvent		 key;
            TextEvent		 text;
            MouseMoveEvent	 mouseMove;
            MouseButtonEvent mouseButton;
            MouseWheelEvent  mouseWheel;
            MouseWheelScrollEvent mouseWheelScroll;
            JoystickMoveEvent	 joystickMove;
            JoystickButtonEvent	 joystickButton;
            JoystickConnectEvent    joystickConnect;
            TouchEvent       touch;
            SensorEvent     sensor;
            };
    };

} // namespace sf


#ifdef USE_MINI_SFML
// we also need some the definition of sf::RenderWindow to compile our SFML example


#include <queue>

namespace sf {

class Input;
class Drawable;
typedef void* WindowHandle;
namespace priv {
class WindowImpl;
}

class WindowListener {
    public :
        virtual void OnEvent(const Event& EventReceived) = 0;
    protected :
        virtual ~WindowListener();
    };

class VideoMode {
    public :
        VideoMode(unsigned int ModeWidth, unsigned int ModeHeight, unsigned int ModeBpp = 32);
        unsigned int Width, Height, BitsPerPixel;
    };

namespace Style {
enum { None = 0, Titlebar = 1 << 0, Resize = 1 << 1, Close = 1 << 2, Fullscreen = 1 << 3 };
}

struct WindowSettings {
    explicit WindowSettings(unsigned int Depth = 24, unsigned int Stencil = 8, unsigned int Antialiasing = 0);
    unsigned int DepthBits, StencilBits, AntialiasingLevel;
    };

class Clock {
    public :
        Clock();
        float GetElapsedTime() const;
        void Reset();
    private :
        double myStartTime;
    };

class Input : public WindowListener {
    private :
        virtual void OnEvent(const Event& EventReceived);
        bool  myKeys[Key::Count];
        bool  myMouseButtons[Mouse::Count];
        int   myMouseX;
        int   myMouseY;
        bool  myJoystickButtons[Joy::Count][Joy::ButtonCount];
        float myJoystickAxis[Joy::Count][Joy::AxisCount];
    };

class Window : public WindowListener {
    public :
        Window(VideoMode Mode, const std::string& Title, unsigned long WindowStyle = Style::Resize | Style::Close, const WindowSettings& Params = WindowSettings());
        virtual ~Window();
        void Close();
        bool IsOpened() const;
        unsigned int GetWidth() const;
        unsigned int GetHeight() const;
        bool GetEvent(Event& EventReceived);
        void Display();
    private :
        virtual void OnCreate();
        virtual void OnEvent(const Event& EventReceived);
        priv::WindowImpl* myWindow;
        std::queue<Event> myEvents;
        Input			  myInput;
        Clock			  myClock;
        WindowSettings	  mySettings;
        float			  myLastFrameTime;
        bool			  myIsExternal;
        unsigned int	  myFramerateLimit;
        int				  mySetCursorPosX;
        int				  mySetCursorPosY;
    };

template <typename T> class Vector2 {
    public :
        T x, y;
    };
typedef Vector2<float> Vector2f;

template <typename T> class Rect {
    public :
        T Left, Top, Right, Bottom;
    };
typedef Rect<float> FloatRect;

class Matrix3 {
    private :
        float myData[16];
    };

class View {
    private :
        sf::Vector2f myCenter;
        sf::Vector2f myHalfSize;
        FloatRect	 myRect;
        Matrix3		 myMatrix;
        bool		 myNeedUpdate;
    };

class RenderTarget {
    public :
        virtual ~RenderTarget();
        virtual void Draw(const Drawable& Object);
        virtual unsigned int GetWidth() const = 0;
        virtual unsigned int GetHeight() const = 0;
        void PreserveOpenGLStates(bool Preserve);
    private :
        virtual bool Activate(bool Active) = 0;
        View		myDefaultView;
        const View* myCurrentView;
        bool		myPreserveStates;
        bool		myIsDrawing;
    };

class RenderWindow : public Window, public RenderTarget {
    public :
        RenderWindow(VideoMode Mode, const std::string& Title, unsigned long WindowStyle = Style::Resize | Style::Close, const WindowSettings& Params = WindowSettings());
        virtual ~RenderWindow();
        virtual unsigned int GetWidth() const;
        virtual unsigned int GetHeight() const;
    private :
        virtual void OnCreate();
        virtual bool Activate(bool Active);
    };

} // namespace sf

#endif // USE_MINI_SFML

#endif // !defined MINI_SFML16_INCLUDED

