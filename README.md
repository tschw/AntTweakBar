# AntTweakBar library

AntTweakBar is a small and easy-to-use C/C++ library that allows programmers
to quickly add a light and intuitive GUI into OpenGL and DirectX(9, 10, 11) based 
graphic programs to interactively tweak parameters.

This package includes the source version of the AntTweakBar library and some
program examples.

**The original author, Philippe Decaudin, does no longer maintain the code, so
this fork is an attempt to combine the updates that can be found in other
(divergent) forks.**

Documentation: http://anttweakbar.sourceforge.net/doc

## Dependencies

All dependencies are optional, but you need to fulfill at least one if you
want to build one of the examples.

* GLFW ( http://www.glfw.org )
* GLUT ( http://opengl.org/resources/libraries/glut )
* SDL ( http://www.libsdl.org )
* SFML ( http://www.sfml-dev.org )
* DirectX SDK ( http://msdn.microsoft.com/directx )


## Compiling
Due to error in file D3DShader.cmake the .h files, see below, from TwDirect3D11.hlsl with fxc are created in the path AntTweakBar-master\build\Renderer and not in AntTweakBar-master\Renderer\compile. Manual copying the files to AntTweakBar-master\Renderer\compile works for compiling.
TwDirect3D11_LineRectCstColorVS.h
TwDirect3D11_LineRectPS.h
TwDirect3D11_LineRectVS.h
TwDirect3D11_TextCstColorVS.h
TwDirect3D11_TextPS.h
TwDirect3D11_TextVS.h
