/**
 *	@file Z-Engine\Z-Engine\Projects\Windows\Interfaces\SpriteLib\SpriteManager.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - 2011 - Team Poly Gone. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _SPRITEMANAGER_H__Included_1571875490
#define _SPRITEMANAGER_H__Included_1571875490

#include "CoreLib/AssetManager.h"

namespace ZGE
{
	class ISpriteParser;
	class CSprite;
	/**
	 *	This class is responsible for sprite managment.
	 */
	class CSpriteManager : public CAssetManager< CSprite >
	{
	public:
		CSpriteManager(void);
		~CSpriteManager(void);

		/**
		 *	Initialises the sprite manager.
		 *	@return Success.
		 */
		bool Initialise(  );


		/**
		 *	Creates a sprite manualy.
		 *	@param _rAssetId The sprites asset id.
		 *	@return The sprite created.
		 */
		CSprite* CreateSprite( CAssetId& _rAssetId ); 

		// Sets the spites managers sprite parser implementation.
		inline void SetSpriteParser( ISpriteParser* _pParser ){ m_pSpriteParser = _pParser; }
	protected:
						/**
		 *	To be overriden to load assets of a derived manager.
		 *	Param _rAssetId : The assets id, ( could be the file name ).
		 *	Param _pAsset   : To be populated with the loaded asset.
		 *	Return : Success.
		 */
		virtual bool LoadAssetImplementation( CAssetId& _rAssetId, tAsset*& _pAsset );

		/**
		 *	To be overidden to release a managers assets.
		 *	Param _pAsset : The asset to release.
		 *	Return : Success.
		 */
		virtual bool ReleaseAsset( tAsset* _pAsset );
	protected:
		ISpriteParser* m_pSpriteParser;
	};
}

#endif //_SPRITEMANAGER_H__Included_1571875490

