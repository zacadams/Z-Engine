/**
 *	@file Z-Engine\Z-Engine\Source\Interfaces\SceneLib\2DActor.cpp
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - 2011 - Team Poly Gone. All Rights Reserved.
 *	
 *********************************************************************************************/


#include "CoreLib/Core.h"
#include "RendererLib/RendererInterface.h"
#include "RendererLib/RenderList.h"
#include "RendererLib/RenderEffect.h"
#include "SpriteLib/2DRenderAsset.h"

#ifdef USING_DIRECT_DRAW
#include "SpriteLib/Sprite.h"
#include "SpriteLib/2DRenderAsset.h"
#endif

#include "SceneLib/RTTIActorRegistry.h"
#include "CoreLib/RTTIRegistrar.h"
#include "SpriteLib/2DActor.h"

using namespace ZGE;

C2DActor::C2DActor(void)
: m_fWorldOrientation( 0.0f )
, m_fLocalOrientation( 0.0f )
{
	m_vScale = CFVec3( 1.0f, 1.0f, 1.0f );
}

C2DActor::~C2DActor(void)
{
	if( m_pRenderAsset )
	{
		SafeDelete( m_pRenderAsset );
	}
}

// Empty process function, to be overidden by derived classes.
bool C2DActor::Update( const float32 _kfDeltaTick )
{
	bool bSuccess = false;
	bool bChildren = UpdateChildren( _kfDeltaTick );
	return bSuccess && bChildren;
}

// Empty draw function, to be overidden by derived classes.
bool C2DActor::Draw(  )
{
	bool bSuccess = false;
	if( m_bRenderFlag )
	{
//#define DIRECT_DRAW
#ifndef USING_DIRECT_DRAW
	if( m_pRenderAsset )
	{
		C2DRenderAsset* pRenderAsset = reinterpret_cast< C2DRenderAsset* >( m_pRenderAsset );
		pRenderAsset->vWorldPosition = m_vWorldPosition;
		pRenderAsset->vScale = m_vScale;
		pRenderAsset->fWorldOrientation = m_fWorldOrientation;
		ZEngine::GetRendererInterface( )->GetRenderList( IRenderList::RLT_2D )->AddRenderAsset( pRenderAsset );
	}
#else
	if( m_pRenderAsset )
	{
		C2DRenderAsset* pRenderAsset = reinterpret_cast< C2DRenderAsset* >( m_pRenderAsset );
		pRenderAsset->pSprite->DrawEx( m_vWorldPosition, CFVec2( m_vScale.x( ), m_vScale.y( ) ), m_fWorldOrientation );
	}
#endif
	}
	
	bool bChildren = DrawChildren( );
	return  bSuccess && bChildren; 
}


// This is a pre update.
bool C2DActor::PreUpdate( const float32 _kfDeltaTick )
{
	bool bSuccess = false;
	if( m_pParent )
	{	
		CFVec3 vTemp = m_vLocalPosition;
		vTemp.RotateZ( reinterpret_cast< C2DActor* >( m_pParent )->GetWorldOrientation( ) );
		m_vWorldPosition = m_pParent->GetWorldPosition( ) + vTemp;
		m_fWorldOrientation = m_fLocalOrientation + reinterpret_cast< C2DActor* >( m_pParent )->GetWorldOrientation( );
	}
	else
	{
		m_vWorldPosition = m_vLocalPosition;
		m_fWorldOrientation = m_fLocalOrientation;
	}
	bool bChildrenUpdated =  PreUpdateChildren( _kfDeltaTick );
	return bSuccess && bChildrenUpdated;
}


REGISTER_DYNAMIC_CREATE(C2DActor, CRTTIActorRegistry );