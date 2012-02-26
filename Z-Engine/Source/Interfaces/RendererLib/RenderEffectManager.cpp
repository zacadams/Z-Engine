/**
 *	@file Z-Engine\Z-Engine\Projects\Windows\Interfaces\RendererLib\RenderEffectManager.cpp
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - 2011 - Team Poly Gone. All Rights Reserved.
 *	
 *********************************************************************************************/
// Z-Engine includes
#include "CoreLib/Core.h"
#include "RendererLib/RenderEffectIO.h"
// Library includes

// Local includes 
#include "RendererLib/RenderEffectManager.h"
using namespace ZGE;
CRenderEffectManager::CRenderEffectManager(void)
{
}

CRenderEffectManager::~CRenderEffectManager(void)
{
}
/*
bool CRenderEffectManager::Initialise( IRenderEffectIO* _pRenderEffectIO )
{
	//m_pRenderEffecIO = _pRenderEffectIO;
	return false;
}
*/

/**
 *	To be overriden to load assets of a derived manager.
 *	Param _rAssetId : The assets id, ( could be the file name ).
 *	Param _pAsset   : To be populated with the loaded asset.
 *	Return : Success.
 */
bool CRenderEffectManager::LoadAssetImplementation( CAssetId& _rAssetId, tAsset*& _pAsset )
{
		/*
	if( false == m_pRenderEffecIO->ParseRenderEffect( _rAssetId.GetFileName( ), _pAsset ) )
	{
		assert_now( "Failed to parse the render effect from file." );
	}
	*/
	return true;
}

/**
 *	To be overidden to release a managers assets.
 *	Param _pAsset : The asset to release.
 *	Return : Success.
 */
bool CRenderEffectManager::ReleaseAsset( tAsset* _pAsset )
{
	delete reinterpret_cast< IRenderEffect* >( _pAsset ); 
	return true;
}
