
#include "TwPrecomp.h"
#include "TwGraph.h"

#include "TwOpenGL.h"
#include "TwOpenGLCore.h"

#ifdef ANT_WINDOWS
#include "TwDirect3D9.h"
#include "TwDirect3D10.h"
#include "TwDirect3D11.h"
#endif

// Don't link anything - we just need an enum!
#ifndef TW_STATIC
#define TW_STATIC
#endif
#ifndef TW_NO_LIB_PRAGMA
#define TW_NO_LIB_PRAGMA
#endif
#include "../../TweakBar/include/AntTweakBar.h"

char const* ITwGraph::g_ErrorState = NULL;

ITwGraph* ITwGraph::Create(IUnknown* _D3DDevice)
{
	if ( _D3DDevice == NULL )
		return CreateForAPI(TW_OPENGL_CORE);

	void* dev;
	dev = CTwGraphDirect3D11::DetectDevice(_D3DDevice);
	if (dev != NULL) return CreateForAPI(TW_DIRECT3D11, dev);
	dev = CTwGraphDirect3D10::DetectDevice(_D3DDevice);
	if (dev != NULL) return CreateForAPI(TW_DIRECT3D10, dev);
	dev = CTwGraphDirect3D9::DetectDevice(_D3DDevice);
	if (dev != NULL) return CreateForAPI(TW_DIRECT3D9, dev);
	return CreateForAPI(-1, NULL); // invalid & raises an error
}

ITwGraph* ITwGraph::CreateForAPI(int _GraphAPI, void* _D3DDevice)
{
    ITwGraph* result;
    g_ErrorState = NULL;

    switch( _GraphAPI )
    {
    case TW_OPENGL:
        result = new CTwGraphOpenGL;
        break;
    case TW_OPENGL_CORE:
        result = new CTwGraphOpenGLCore;
        break;
#ifdef ANT_WINDOWS
    case TW_DIRECT3D9:
        result = new CTwGraphDirect3D9( _D3DDevice );
        break;
    case TW_DIRECT3D10:
        result = new CTwGraphDirect3D10( _D3DDevice );
        break;
    case TW_DIRECT3D11:
        result = new CTwGraphDirect3D10( _D3DDevice );
        break;
#endif
    default:
        result = NULL;
    }

    if ( result == NULL )
    {
        g_ErrorState = "Graphics API not supported by this build.";
    }
    else if ( ! result->Init() )
    {
        delete result;
        result = NULL;
    }

    return result;
}

bool ITwGraph::Delete(ITwGraph* obj)
{
    bool result = obj->Shut() != 0;
    delete obj;
    return result;
}

char const* ITwGraph::GetErrorState()
{
    return g_ErrorState;
}

ITwGraph::~ITwGraph()
{
}

