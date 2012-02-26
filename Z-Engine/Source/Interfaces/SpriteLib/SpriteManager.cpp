/**
 *	@file Z-Engine\Z-Engine\Projects\Windows\Interfaces\SpriteLib\SpriteManager.cpp
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - 2011 - Team Poly Gone. All Rights Reserved.
 *	
 *********************************************************************************************/
// Z-Engine includes
#include "CoreLib/Core.h"
#include "SpriteLib/Sprite.h"
#include "SpriteLib/ISpriteParser.h"
// Library includes

// Local includes
#include "SpriteLib/SpriteManager.h"
using namespace ZGE;

CSpriteManager::CSpriteManager(void)
{
}

CSpriteManager::~CSpriteManager(void)
{
}

/**
 *	Initialises the sprite manager.
 *	@return Success.
 */
bool CSpriteManager::Initialise(   )
{
	// Create the sprite parser based on the platform.
	return false;
}


		/**
 *	To be overriden to load assets of a derived manager.
 *	Param _rAssetId : The assets id, ( could be the file name ).
 *	Param _pAsset   : To be populated with the loaded asset.
 *	Return : Success.
 */
bool CSpriteManager::LoadAssetImplementation( CAssetId& _rAssetId, tAsset*& _pAsset )
{
	// Parse the asset from file.
	if( NULL == m_pSpriteParser )
	{
		assert_now( "Sprite manager does not have a sprite parser instance!" );
		return false;
	}

	bool bSuccess = m_pSpriteParser->ParseSprite( _rAssetId.GetFileName( ), _pAsset );
	if( bSuccess )
	{
		_pAsset->SetAssetId( _rAssetId );
	}
	return bSuccess;
}

/**
 *	To be overidden to release a managers assets.
 *	Param _pAsset : The asset to release.
 *	Return : Success.
 */
bool CSpriteManager::ReleaseAsset( tAsset* _pAsset )
{
	delete _pAsset;
	_pAsset= NULL;
	return true;
}

/**
 *	Creates a sprite manualy.
 *	@param _rAssetId The sprites asset id.
 *	@return The sprite created.
 */
CSprite* CSpriteManager::CreateSprite( CAssetId& _rAssetId )
{
	//// Does the sprite exist?
 //	tAsset* pSprite = NULL;
	CSprite* pSprite = NULL;
	//pSprite = GetAssetById( _rAssetId );
	//if( pSprite )
	//{
	//	// Exists, increase reference count and return.
	//	pSprite->AddRef( );
	//	return pSprite;
	//}

	// Does not exist, create it.
	pSprite = new CSprite( );
	//AddPreCreatedAsset( _rAssetId, pSprite );
	return pSprite;
}