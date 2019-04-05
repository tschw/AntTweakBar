//	---------------------------------------------------------------------------
//
//	@file		TwDirect3D10.h
//	@brief		Direct3D10 graph functions
//	@author		Philippe Decaudin
//	@license	This file is part of the AntTweakBar library.
//				For conditions of distribution and use, see License.txt
//
//	note:		Private header
//
//	---------------------------------------------------------------------------

#if !defined ANT_TW_DIRECT3D10_INCLUDED
#define ANT_TW_DIRECT3D10_INCLUDED

#if !defined ANT_TW_NO_D3D10

#include "TwGraph.h"

struct ID3D10Device;
struct ID3D10ShaderResourceView;
struct ID3D10DepthStencilState;
struct ID3D10BlendState;
struct ID3D10RasterizerState;
struct ID3D10Effect;
struct ID3D10EffectTechnique;
struct ID3D10InputLayout;
struct ID3D10Buffer;
struct ID3D10EffectShaderResourceVariable;
struct ID3D10EffectVectorVariable;

namespace AntTweakBar {

//	---------------------------------------------------------------------------

class CTwGraphDirect3D10 : public ITwGraph
{
public:

	explicit CTwGraphDirect3D10(void* _D3DDevice);
	static void*				DetectDevice(IUnknown*);

	virtual int					Init();
	virtual int					Shut();
	virtual void				BeginDraw(int _WndWidth, int _WndHeight);
	virtual void				EndDraw();
	virtual bool				IsDrawing();
	virtual void				Restore();
	virtual void				DrawLine(int _X0, int _Y0, int _X1, int _Y1, color32 _Color0, color32 _Color1, bool _AntiAliased=false);
	virtual void				DrawLine(int _X0, int _Y0, int _X1, int _Y1, color32 _Color, bool _AntiAliased=false) { DrawLine(_X0, _Y0, _X1, _Y1, _Color, _Color, _AntiAliased); }
	virtual void				DrawRect(int _X0, int _Y0, int _X1, int _Y1, color32 _Color00, color32 _Color10, color32 _Color01, color32 _Color11);
	virtual void				DrawRect(int _X0, int _Y0, int _X1, int _Y1, color32 _Color) { DrawRect(_X0, _Y0, _X1, _Y1, _Color, _Color, _Color, _Color); }
	virtual void				DrawTriangles(int _NumTriangles, int *_Vertices, color32 *_Colors, Cull _CullMode);

	virtual void *				NewTextObj();
	virtual void				DeleteTextObj(void *_TextObj);
	virtual void				BuildText(void *_TextObj, const std::string *_TextLines, color32 *_LineColors, color32 *_LineBgColors, int _NbLines, const CTexFont *_Font, int _Sep, int _BgWidth);
	virtual void				DrawText(void *_TextObj, int _X, int _Y, color32 _Color, color32 _BgColor);

	virtual void				ChangeViewport(int _X0, int _Y0, int _Width, int _Height, int _OffsetX, int _OffsetY);
	virtual void				RestoreViewport();
	virtual void				SetScissor(int _X0, int _Y0, int _Width, int _Height);

protected:
	ID3D10Device *				m_D3DDev;
	unsigned int				m_D3DDevInitialRefCount;
	bool						m_Drawing;
	const CTexFont *			m_FontTex;
	ID3D10ShaderResourceView *	m_FontD3DTexRV;
	int							m_WndWidth;
	int							m_WndHeight;
	int							m_OffsetX;
	int							m_OffsetY;
	void *						m_ViewportInit;
	RECT						m_ViewportAndScissorRects[2];

	struct CLineRectVtx
	{
		float					m_Pos[3];
		color32					m_Color;
	};
	struct CTextVtx
	{
		float					m_Pos[3];
		color32					m_Color;
		float					m_UV[2];
	};

	struct CTextObj
	{
		struct ID3D10Buffer *	m_TextVertexBuffer;
		struct ID3D10Buffer *	m_BgVertexBuffer;
		int						m_NbTextVerts;
		int						m_NbBgVerts;
		int						m_TextVertexBufferSize;
		int						m_BgVertexBufferSize;
		bool					m_LineColors;
		bool					m_LineBgColors;
	};

	struct CState10 *				m_State;
	ID3D10DepthStencilState *		m_DepthStencilState;
	ID3D10BlendState *				m_BlendState;
	ID3D10RasterizerState *			m_RasterState;
	ID3D10RasterizerState *			m_RasterStateAntialiased;
	ID3D10RasterizerState *			m_RasterStateCullCW;
	ID3D10RasterizerState *			m_RasterStateCullCCW;
	ID3D10Effect *					m_Effect;
	ID3D10EffectTechnique*			m_LineRectTech;
	ID3D10EffectTechnique*			m_LineRectCstColorTech;
	ID3D10InputLayout *				m_LineRectVertexLayout;
	ID3D10Buffer *					m_LineVertexBuffer;
	ID3D10Buffer *					m_RectVertexBuffer;
	ID3D10Buffer *					m_TrianglesVertexBuffer;
	int								m_TrianglesVertexBufferCount;
	ID3D10EffectTechnique*			m_TextTech;
	ID3D10EffectTechnique*			m_TextCstColorTech;
	ID3D10InputLayout *				m_TextVertexLayout;
	ID3D10EffectShaderResourceVariable *m_FontD3DResVar;
	ID3D10EffectVectorVariable *	m_OffsetVar;
	ID3D10EffectVectorVariable *	m_CstColorVar;
};

//	---------------------------------------------------------------------------
}
#endif // !defined ANT_TW_NO_D3D10
#endif // !defined ANT_TW_DIRECT3D10_INCLUDED
