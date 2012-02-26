/**
 *	@file Z-Engine\Z-Engine\Projects\Windows\Interfaces\SpriteLib\AnimatedSpriteManager.cpp
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - 2011 - Team Poly Gone. All Rights Reserved.
 *	
 *********************************************************************************************/
// Z-Engine includes
#include "CoreLib/Core.h"
#include "SpriteLib/AnimatedSprite.h"
// Library includes

// Local includes 
#include "SpriteLib/AnimatedSpriteManager.h"
using namespace ZGE; 
CAnimatedSpriteManager::CAnimatedSpriteManager(void)
{
}

CAnimatedSpriteManager::~CAnimatedSpriteManager(void)
{
}

/**
 *	Initialises the animated sprite manager.
 *	@return Success.
 */
bool CAnimatedSpriteManager::Initialise( )
{
	return false;
}

/**
 *	Creates an animated sprite.
 *	@param _rAssetId The animated sprites asset id.
 *	@return The animated sprite created.
 */
CAnimatedSprite* CAnimatedSpriteManager::CreateAnimatedSprite( CAssetId& _rAssetId )
{
	// Does the asset exist?
	CAnimatedSprite* pSprite = NULL;
	pSprite = GetAssetById( _rAssetId );
	if( pSprite )
	{
		pSprite->AddRef( );
		return pSprite;
	}

	pSprite = new CAnimatedSprite( );
	AddPreCreatedAsset( _rAssetId, pSprite );
	return pSprite;
}
/**
 *	To be overriden to load assets of a derived manager.
 *	Param _rAssetId : The assets id, ( could be the file name ).
 *	Param _pAsset   : To be populated with the loaded asset.
 *	Return : Success.
 */
bool CAnimatedSpriteManager::LoadAssetImplementation( CAssetId& _rAssetId, tAsset*& _pAsset )
{
	UNUSED_VAR( _rAssetId );
	UNUSED_VAR( _pAsset );
	return false;
}
/**
 *	To be overidden to release a managers assets.
 *	Param _pAsset : The asset to release.
 *	Return : Success.
 */
bool CAnimatedSpriteManager::ReleaseAsset( tAsset* _pAsset )
{
	delete _pAsset;
	_pAsset = NULL;
	return true;
}
