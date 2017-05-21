//	---------------------------------------------------------------------------
//
//	@file		TwGLCoreSDL.c
//	@brief		An example that uses AntTweakBar with OpenGL Core Profile
//				and SDL 1.3.
//
//				AntTweakBar: http://anttweakbar.sourceforge.net/doc
//				OpenGL:		 http://www.opengl.org
//				SDL:		 http://www.libsdl.org
//
//	@author		Philippe Decaudin
//
//	---------------------------------------------------------------------------


#include <AntTweakBar.h>

#ifdef USE_SDL2
#	include <SDL2/SDL.h>
#	include <SDL2/SDL_opengl.h>
#else
#	include <SDL/SDL.h>
#	include <SDL/SDL_opengl.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// #define USE_OPENGL_ES 2
// #define USE_OPENGL_ES 3

// In this example, we draw a simple rotating square using the OpenGL core profile
// (which requires much more code than with the compatibility profile).
// A tweak bar is created to allow the user to change the color of the
// rectangle and see its rotation.

// We have to retrieve the core functions using SDL_GL_GetProcAddress.
// These functions are prefixed by underscore to avoid possible confict
// if a modified gl.h has been installed.

#ifndef APIENTRY
#	define APIENTRY
#endif
typedef void (APIENTRY *PFNGLClear)(GLbitfield mask);
typedef void (APIENTRY *PFNGLClearColor)(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
typedef void (APIENTRY *PFNGLDisable)(GLenum cap);
typedef void (APIENTRY *PFNGLDrawArrays)(GLenum mode, GLint first, GLsizei count);
typedef GLenum (APIENTRY *PFNGLGetError)(void);
typedef void (APIENTRY *PFNGLViewport)(GLint x, GLint y, GLsizei width, GLsizei height);
typedef GLuint (APIENTRY *PFNGLCreateShader)(GLenum type);
typedef void (APIENTRY *PFNGLDeleteShader)(GLuint shader);
typedef void (APIENTRY *PFNGLShaderSource)(GLuint shader, GLsizei count, const char* *str, const GLint *length);
typedef void (APIENTRY *PFNGLCompileShader)(GLuint shader);
typedef void (APIENTRY *PFNGLAttachShader)(GLuint program, GLuint shader);
typedef GLuint (APIENTRY *PFNGLCreateProgram)(void);
typedef void (APIENTRY *PFNGLLinkProgram)(GLuint program);
typedef void (APIENTRY *PFNGLUseProgram)(GLuint program);
typedef void (APIENTRY *PFNGLDeleteProgram)(GLuint program);
typedef void (APIENTRY *PFNGLGenBuffers)(GLsizei n, GLuint *buffers);
typedef void (APIENTRY *PFNGLBindBuffer)(GLenum target, GLuint buffer);
typedef void (APIENTRY *PFNGLVertexAttribPointer)(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid *pointer);
typedef void (APIENTRY *PFNGLEnableVertexAttribArray)(GLuint index);
typedef void (APIENTRY *PFNGLGenVertexArrays)(GLsizei n, GLuint *arrays);
typedef void (APIENTRY *PFNGLBindVertexArray)(GLuint array);
typedef void (APIENTRY *PFNGLDeleteVertexArrays)(GLsizei n, const GLuint *arrays);
typedef GLint (APIENTRY *PFNGLGetAttribLocation)(GLuint program, const char *name);
typedef GLint (APIENTRY *PFNGLGetUniformLocation)(GLuint program, const char *name);
typedef void (APIENTRY *PFNGLUniform1f)(GLint location, GLfloat v0);
typedef void (APIENTRY *PFNGLUniform3f)(GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
typedef void (APIENTRY *PFNGLBufferData)(GLenum target, ptrdiff_t size, const GLvoid *data, GLenum usage);
typedef void (APIENTRY *PFNGLDeleteBuffers)(GLsizei n, const GLuint *buffers);
PFNGLClear _glClear;
PFNGLClearColor _glClearColor;
PFNGLDisable _glDisable;
PFNGLDrawArrays _glDrawArrays;
PFNGLGetError _glGetError;
PFNGLViewport _glViewport;
PFNGLCreateShader _glCreateShader;
PFNGLDeleteShader _glDeleteShader;
PFNGLShaderSource _glShaderSource;
PFNGLCompileShader _glCompileShader;
PFNGLAttachShader _glAttachShader;
PFNGLCreateProgram _glCreateProgram;
PFNGLLinkProgram _glLinkProgram;
PFNGLUseProgram _glUseProgram;
PFNGLDeleteProgram _glDeleteProgram;
PFNGLGenBuffers _glGenBuffers;
PFNGLBindBuffer _glBindBuffer;
PFNGLVertexAttribPointer _glVertexAttribPointer;
PFNGLEnableVertexAttribArray _glEnableVertexAttribArray;
PFNGLGenVertexArrays _glGenVertexArrays;
PFNGLBindVertexArray _glBindVertexArray;
PFNGLDeleteVertexArrays _glDeleteVertexArrays;
PFNGLGetAttribLocation _glGetAttribLocation;
PFNGLGetUniformLocation _glGetUniformLocation;
PFNGLUniform1f _glUniform1f;
PFNGLUniform3f _glUniform3f;
PFNGLBufferData _glBufferData;
PFNGLDeleteBuffers _glDeleteBuffers;
#ifndef GL_ARRAY_BUFFER
#	define GL_ARRAY_BUFFER		0x8892
#endif
#ifndef GL_STATIC_DRAW
#	define GL_STATIC_DRAW		0x88E4
#endif
#ifndef GL_VERTEX_SHADER
#	define GL_VERTEX_SHADER		0x8B31
#endif
#ifndef GL_FRAGMENT_SHADER
#	define GL_FRAGMENT_SHADER	0x8B30
#endif

int LoadGLCoreFunctions()
{
	_glClear = (PFNGLClear)SDL_GL_GetProcAddress("glClear");
	_glClearColor = (PFNGLClearColor)SDL_GL_GetProcAddress("glClearColor");
	_glDisable = (PFNGLDisable)SDL_GL_GetProcAddress("glDisable");
	_glDrawArrays = (PFNGLDrawArrays)SDL_GL_GetProcAddress("glDrawArrays");
	_glGetError = (PFNGLGetError)SDL_GL_GetProcAddress("glGetError");
	_glViewport = (PFNGLViewport)SDL_GL_GetProcAddress("glViewport");
	_glCreateShader = (PFNGLCreateShader)SDL_GL_GetProcAddress("glCreateShader");
	_glDeleteShader = (PFNGLDeleteShader)SDL_GL_GetProcAddress("glDeleteShader");
	_glShaderSource = (PFNGLShaderSource)SDL_GL_GetProcAddress("glShaderSource");
	_glCompileShader = (PFNGLCompileShader)SDL_GL_GetProcAddress("glCompileShader");
	_glAttachShader = (PFNGLAttachShader)SDL_GL_GetProcAddress("glAttachShader");
	_glCreateProgram = (PFNGLCreateProgram)SDL_GL_GetProcAddress("glCreateProgram");
	_glLinkProgram = (PFNGLLinkProgram)SDL_GL_GetProcAddress("glLinkProgram");
	_glUseProgram = (PFNGLUseProgram)SDL_GL_GetProcAddress("glUseProgram");
	_glDeleteProgram = (PFNGLDeleteProgram)SDL_GL_GetProcAddress("glDeleteProgram");
	_glGenBuffers = (PFNGLGenBuffers)SDL_GL_GetProcAddress("glGenBuffers");
	_glBindBuffer = (PFNGLBindBuffer)SDL_GL_GetProcAddress("glBindBuffer");
	_glVertexAttribPointer = (PFNGLVertexAttribPointer)SDL_GL_GetProcAddress("glVertexAttribPointer");
	_glEnableVertexAttribArray = (PFNGLEnableVertexAttribArray)SDL_GL_GetProcAddress("glEnableVertexAttribArray");
	_glGenVertexArrays = (PFNGLGenVertexArrays)SDL_GL_GetProcAddress("glGenVertexArrays");
	_glBindVertexArray = (PFNGLBindVertexArray)SDL_GL_GetProcAddress("glBindVertexArray");
	_glDeleteVertexArrays = (PFNGLDeleteVertexArrays)SDL_GL_GetProcAddress("glDeleteVertexArrays");
	_glGetAttribLocation = (PFNGLGetAttribLocation)SDL_GL_GetProcAddress("glGetAttribLocation");
	_glGetUniformLocation = (PFNGLGetUniformLocation)SDL_GL_GetProcAddress("glGetUniformLocation");
	_glUniform1f = (PFNGLUniform1f)SDL_GL_GetProcAddress("glUniform1f");
	_glUniform3f = (PFNGLUniform3f)SDL_GL_GetProcAddress("glUniform3f");
	_glBufferData = (PFNGLBufferData)SDL_GL_GetProcAddress("glBufferData");
	_glDeleteBuffers = (PFNGLDeleteBuffers)SDL_GL_GetProcAddress("glDeleteBuffers");

	if (_glCreateShader == NULL || _glDeleteShader == NULL || _glShaderSource == NULL || _glCompileShader == NULL
		|| _glAttachShader == NULL || _glCreateProgram == NULL || _glLinkProgram == NULL || _glUseProgram  == NULL
		|| _glDeleteProgram == NULL || _glGenBuffers == NULL || _glBindBuffer == NULL || _glVertexAttribPointer == NULL
		|| _glEnableVertexAttribArray == NULL || _glGenVertexArrays == NULL || _glBindVertexArray == NULL
		|| _glDeleteVertexArrays == NULL || _glGetAttribLocation == NULL || _glGetUniformLocation == NULL
		|| _glUniform1f == NULL || _glUniform3f == NULL || _glBufferData == NULL || _glDeleteBuffers == NULL)
		return 0;
	else
		return 1;
}

void checkGlError()
{
	GLenum error;
	if ((error = _glGetError()) != GL_NO_ERROR)
		fprintf(stderr, "GL error detected: 0x%04X\n", error);
}


// Shaders globals
GLuint vshader, fshader, program, varray, buffer;
GLint cosa, sina, colorloc;
float angle = 0, quat[4];
float color[] = {0.8f, 1.0f, 0.2f};
float FLOAT_PI = 3.14159265f;

void InitRender()
{
#ifdef USE_OPENGL_ES
	// Note: Using GLSL ES 2 shaders, ES 3 provides backward compatibility.

	// Vertex shader
	char const*vsource[] = {
		"#version 100\n"
		"precision highp float;"
		"uniform float cosa, sina;"
		"attribute vec3 vertex;"
		"void main() { gl_Position = vec4(cosa*vertex.x-sina*vertex.y, sina*vertex.x+cosa*vertex.y, 0., 1.); }"
	};
	// Fragment shader
	char const*fsource[] = {
		"#version 100\n"
		"precision mediump float;"
		"uniform vec3 color;"
		"void main() { gl_FragColor = vec4(color, 1.); }"
	};
#else
	// Vertex shader
	char const*vsource[] = {
		"#version 150 core\n"
		"precision highp float;"
		"uniform float cosa, sina;"
		"in vec3 vertex;"
		"void main() { gl_Position = vec4(cosa*vertex.x-sina*vertex.y, sina*vertex.x+cosa*vertex.y, 0., 1.); }"
	};
	// Fragment shader
	char const*fsource[] = {
		"#version 150 core\n"
		"precision mediump float;"
		"uniform vec3 color;"
		"out vec4 fColor;"
		"void main() { fColor = vec4(color, 1.); }"
	};
#endif
	// Geometry vertex array
	GLfloat vertices[] = {
		-0.5f,	0.5f, 0,
		-0.5f, -0.5f, 0,
		 0.5f,	0.5f, 0,
		 0.5f, -0.5f, 0
	};
	GLint vlocation;

	// Compile and bind shaders
	vshader = _glCreateShader(GL_VERTEX_SHADER);
	fshader = _glCreateShader(GL_FRAGMENT_SHADER);
	program = _glCreateProgram();
	_glShaderSource(vshader, 1, vsource, NULL);
	_glShaderSource(fshader, 1, fsource, NULL);
	_glCompileShader(vshader);
	_glCompileShader(fshader);
	_glAttachShader(program, vshader);
	_glAttachShader(program, fshader);
	_glLinkProgram(program);
	_glUseProgram(program);

	cosa = _glGetUniformLocation(program, "cosa");
	sina = _glGetUniformLocation(program, "sina");
	colorloc = _glGetUniformLocation(program, "color");

	// Create and bind vertex buffer
	_glGenVertexArrays(1, &varray);
	_glBindVertexArray(varray);
	_glGenBuffers(1, &buffer);
	_glBindBuffer(GL_ARRAY_BUFFER, buffer);
	_glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	vlocation = _glGetAttribLocation(program, "vertex");
	_glVertexAttribPointer(vlocation, 3, GL_FLOAT, GL_TRUE, 0, NULL);
	_glEnableVertexAttribArray(vlocation);

	// GL states
	_glDisable(GL_DEPTH_TEST);
	_glDisable(GL_CULL_FACE);

	checkGlError();
}

void UninitRender()
{
	_glDeleteProgram(program);
	_glDeleteShader(fshader);
	_glDeleteShader(vshader);
	_glDeleteBuffers(1, &buffer);
	_glDeleteVertexArrays(1, &varray);
}

void Render()
{
	_glUniform1f(cosa, (float)cos(angle));
	_glUniform1f(sina, (float)sin(angle));
	_glUniform3f(colorloc, color[0], color[1], color[2]);
	_glBindVertexArray(varray);
	_glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	checkGlError();
}


TwBar *CreateTweakBar()
{
	TwBar *bar;

	// Create a tweak bar
	bar = TwNewBar("TweakBar");
	TwDefine(" GLOBAL help='This example shows how to integrate AntTweakBar with SDL and OpenGL Core Profile.\n' "); // Message added to the help bar.

	// Add variables
	TwAddVarRW(bar, "Rotation", TW_TYPE_QUAT4F, &quat, " opened=true help='Rectangle rotation' ");
	TwAddVarRW(bar, "Color", TW_TYPE_COLOR3F, &color, " opened=true help='Rectangle color' ");

	return bar;
}

int main( int argc, char* argv[] )
{
#if SDL_MAJOR_VERSION >= 2
	SDL_Window		*window;
	SDL_GLContext	*context;
#else
	const SDL_VideoInfo* video = NULL;
	int bpp, flags;
#endif
	int width  = 480, height = 480;
	int quit = 0;

	// Initialize SDL, then get the current video mode and use it to create a SDL window.
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		fprintf(stderr, "Video initialization failed: %s\n", SDL_GetError());
		SDL_Quit();
		return 1;
	}
#if SDL_MAJOR_VERSION > 1 || SDL_MINOR_VERSION >= 3
	// Note: There's no way to request that with SDL < 1.3, so in that case
	// it comes down to whether the graphics driver gives us a sufficiently
	// capable OpenGL context.

#	ifndef USE_OPENGL_ES
	// Request GL context to be OpenGL 3.2 Core Profile
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(
			SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
#	else
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, USE_OPENGL_ES);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
	SDL_GL_SetAttribute(
			SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
#	endif

#endif

	// Other GL attributes
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
	//SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

#if SDL_MAJOR_VERSION >= 2

	window = SDL_CreateWindow("AntTweakBar+GLCore+SDL2",
				SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height,
				SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN |SDL_WINDOW_RESIZABLE);
	if (!window)
	{
		fprintf(stderr, "Window creation failed: %s\n", SDL_GetError());
		SDL_Quit();
		return 1;
	}

	context = SDL_GL_CreateContext(window);
	if (!window)
	{
		fprintf(stderr, "GL context creation failed: %s\n", SDL_GetError());
		SDL_Quit();
		return 1;
	}

#else
	video = SDL_GetVideoInfo();
	if (!video)
	{
		fprintf(stderr, "Video query failed: %s\n", SDL_GetError());
		SDL_Quit();
		return 1;
	}
	bpp = video->vfmt->BitsPerPixel;
	flags = SDL_OPENGL | SDL_HWSURFACE | SDL_RESIZABLE;
	if (!SDL_SetVideoMode(width, height, bpp, flags))
	{
		fprintf(stderr, "Video mode set failed: %s\n", SDL_GetError());
		SDL_Quit();
		return 1;
	}

	SDL_WM_SetCaption("AntTweakBar example using OpenGL Core Profile and SDL", "AntTweakBar+GLCore+SDL");

	// Enable SDL unicode and key-repeat
	SDL_EnableUNICODE(1);
	SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);
#endif

	// Load some OpenGL core functions
	if (!LoadGLCoreFunctions())
	{
		fprintf(stderr, "OpenGL 3.2 not supported.\n");
		SDL_Quit();
		exit(1);
	}

	// Initialize AntTweakBar
	if (!TwInit(TW_OPENGL_CORE, NULL)) {
		fprintf(stderr, "AntTweakBar initialization failed: %s\n", TwGetLastError());
		SDL_Quit();
		exit(1);
	}
	// Tell the window size to AntTweakBar
	TwWindowSize(width, height);
	// Create a tweak bar
	CreateTweakBar();

	// Set OpenGL viewport
	_glViewport(0, 0, width, height);

	// Prepare GL shaders and programs for drawing
	InitRender();

	// Main loop:
	// - Draw scene
	// - Process events
	while (!quit)
	{
		SDL_Event event;
		int handled;

		// Clear screen
		_glClearColor(0.5f, 0.75f, 0.8f, 1);
		_glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

		// Update angle and draw geometry
		angle = (float)SDL_GetTicks()/25.0f * (FLOAT_PI/180.0f);
		quat[0] = quat[1] = 0;
		quat[2] = (float)sin(angle/2.0f);
		quat[3] = (float)cos(angle/2.0f);
		Render();

		// Draw tweak bars
		TwDraw();

#if SDL_MAJOR_VERSION >= 2
		SDL_GL_SwapWindow(window);
#else
		// Present frame buffer
		SDL_GL_SwapBuffers();
#endif

		// Process incoming events
		while (SDL_PollEvent(&event))
		{
			// Send event to AntTweakBar
			handled = TwEventSDL(&event, SDL_MAJOR_VERSION, SDL_MINOR_VERSION);

			// If event has not been handled by AntTweakBar, process it
			if (!handled)
			{
				switch (event.type)
				{
				case SDL_QUIT:	// Window is closed
					quit = 1;
					break;

#if SDL_MAJOR_VERSION >= 2
				case SDL_WINDOWEVENT:
					if (event.window.event != SDL_WINDOWEVENT_SIZE_CHANGED) break;
					SDL_GL_GetDrawableSize(window, &width, &height);

#else
				case SDL_VIDEORESIZE:	// Window size has changed
					// Resize SDL video mode
					width = event.resize.w;
					height = event.resize.h;
					if (!SDL_SetVideoMode(width, height, bpp, flags))
						fprintf(stderr, "WARNING: Video mode set failed: %s\n", SDL_GetError());
#endif

					// Resize OpenGL viewport
					_glViewport(0, 0, width, height);

					// Restore OpenGL states
					InitRender();
					// TwWindowSize has been called by TwEventSDL,
					// so it is not necessary to call it again here.

					break;
				}
			}
		}


	} // End of main loop

	// Terminate AntTweakBar
	TwTerminate();

	// Delete GL shaders and buffer
	UninitRender();

	// Terminate SDL
	SDL_Quit();

	return 0;
}

