
#include "TwPrecomp.h"
#include "TwGraph.h"

#include "TwOpenGL.h"
#include "TwOpenGLCore.h"
#include "TwDirect3D9.h"
#include "TwDirect3D10.h"
#include "TwDirect3D11.h"

// Don't link anything - we just need an enum!
#ifndef TW_STATIC
#define TW_STATIC
#endif
#ifndef TW_NO_LIB_PRAGMA
#define TW_NO_LIB_PRAGMA
#endif
#include "../../TweakBar/include/AntTweakBar.h"

namespace AntTweakBar {

char const* ITwGraph::g_ErrorState = NULL;

ITwGraph* ITwGraph::Create(IUnknown* _D3DDevice)
{
#if !defined ANT_TW_NO_CORE_GL
	if ( _D3DDevice == NULL )
	{
		ITwGraph* result = CreateForAPI(TW_OPENGL_CORE);
		if ( result != 0l ) return result;
	}
#elif !defined ANT_TW_NO_LEGACY_GL
	if ( _D3DDevice == NULL )
		return CreateForAPI(TW_OPENGL);
#endif
	void* dev = NULL;
#if !defined ANT_TW_NO_D3D11
	dev = CTwGraphDirect3D11::DetectDevice(_D3DDevice);
	if (dev != NULL) return CreateForAPI(TW_DIRECT3D11, dev);
#endif
#if !defined ANT_TW_NO_D3D10
	dev = CTwGraphDirect3D10::DetectDevice(_D3DDevice);
	if (dev != NULL) return CreateForAPI(TW_DIRECT3D10, dev);
#endif
#if !defined ANT_TW_NO_D3D9
	dev = CTwGraphDirect3D9::DetectDevice(_D3DDevice);
	if (dev != NULL) return CreateForAPI(TW_DIRECT3D9, dev);
#endif
	(void) dev;
	return CreateForAPI(-1, NULL); // invalid & raises an error
}

ITwGraph* ITwGraph::CreateForAPI(int _GraphAPI, void* _D3DDevice)
{
	ITwGraph* result;
	g_ErrorState = NULL;

	switch( _GraphAPI )
	{
#if !defined ANT_TW_NO_LEGACY_GL
	case TW_OPENGL:
		result = new CTwGraphOpenGL;
		break;
#endif
#if !defined ANT_TW_NO_CORE_GL
	case TW_OPENGL_CORE:
		result = new CTwGraphOpenGLCore;
		break;
#endif
#if !defined ANT_TW_NO_D3D9
	case TW_DIRECT3D9:
		result = new CTwGraphDirect3D9( _D3DDevice );
		break;
#endif
#if !defined ANT_TW_NO_D3D10
	case TW_DIRECT3D10:
		result = new CTwGraphDirect3D10( _D3DDevice );
		break;
#endif
#if !defined ANT_TW_NO_D3D11
	case TW_DIRECT3D11:
		result = new CTwGraphDirect3D11( _D3DDevice );
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

} // namespace
