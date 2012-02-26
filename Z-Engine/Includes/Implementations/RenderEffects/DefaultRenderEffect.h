/**
 *	@file Z-Engine\Z-Engine\Implementations\RenderEffects\DefaultRenderEffect.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _DEFAULTRENDEREFFECT_H__Included_180049873
#define _DEFAULTRENDEREFFECT_H__Included_180049873

#include "RendererLib/RenderEffect.h"

namespace ZGE
{
	class CDefaultRenderEffect : public IRenderEffect
	{
	public:
		CDefaultRenderEffect( );
		~CDefaultRenderEffect( void );

		// Renders a mesh with its materials and textures.
		virtual void DrawMesh( CMesh* _pMesh, IRendererInterface* _pRenderer );	
		// 
		virtual void BeginEffect( );
		//
		virtual void EndEffect( );
	};
}

#endif //_DEFAULTRENDEREFFECT_H__Included_180049873

