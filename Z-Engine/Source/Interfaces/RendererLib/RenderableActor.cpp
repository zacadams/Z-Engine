/**
 *	@file Z-Engine\Z-Engine\Projects\Windows\Interfaces\RendererLib\RenderableActor.cpp
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2011 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/
#include "CoreLib/Core.h"
#include "RendererLib/RenderEffect.h"
#include "RendererLib/RenderAsset.h"
#include "RendererLib/RenderableActor.h"

using namespace ZGE;

#define VALIDATE_RENDER_ASSET if( NULL == m_pRenderAsset ) { /*assert_now( "Actor does not have a render asset!" );*/ return; }

CRenderableActor::CRenderableActor(void)
: m_pRenderAsset( NULL )
{
}

CRenderableActor::~CRenderableActor(void)
{
}
/** 
 *	Sets the renderable actors render effect.
 *	@param pRenderEffect The effect used to render the actor.
 */
void CRenderableActor::SetRenderEffect( IRenderEffect* pRenderEffect )
{
	VALIDATE_RENDER_ASSET
	m_pRenderAsset->m_pRenderEffect = pRenderEffect;
}

IRenderEffect* CRenderableActor::GetRenderEffect( ) const 
{
	if( m_pRenderAsset )
	{
		return m_pRenderAsset->m_pRenderEffect;
	}
	return NULL;
}