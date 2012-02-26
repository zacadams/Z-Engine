/**
 *	@file Z-Engine\Z-Engine\Projects\Windows\Interfaces\SpriteLib\AnimatedSpriteManager.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - 2011 - Team Poly Gone. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _ANIMATEDSPRITEMANAGER_H__Included_1488043510
#define _ANIMATEDSPRITEMANAGER_H__Included_1488043510

#include "CoreLib/AssetManager.h"

namespace ZGE
{
	class CAnimatedSprite;
	class IAnimatedSpriteParser;
	/**
	 *	Manages anmated sprite assets.
	 */
	class CAnimatedSpriteManager : public CAssetManager< CAnimatedSprite >
	{
	public:
		CAnimatedSpriteManager(void);
		~CAnimatedSpriteManager(void);

		/**
		 *	Initialises the animated sprite manager.
		 *	@return Success.
		 */
		bool Initialise( );

		/**
		 *	Creates an animated sprite.
		 *	@param _rAssetId The animated sprites asset id.
		 *	@return The animated sprite created.
		 */
		CAnimatedSprite* CreateAnimatedSprite( CAssetId& _rAssetId );

	protected:
		/**
		 *	To be overriden to load assets of a derived manager.
		 *	Param _rAssetId : The assets id, ( could be the file name ).
		 *	Param _pAsset   : To be populated with the loaded asset.
		 *	Return : Success.
		 */
		virtual bool LoadAssetImplementation( CAssetId& _rAssetId, tAsset*& _pAsset ) ;

		/**
		 *	To be overidden to release a managers assets.
		 *	Param _pAsset : The asset to release.
		 *	Return : Success.
		 */
		virtual bool ReleaseAsset( tAsset* _pAsset );
	protected:
		IAnimatedSpriteParser*	m_pAnimatedSpriteParser;
	};
}

#endif //_ANIMATEDSPRITEMANAGER_H__Included_1488043510

