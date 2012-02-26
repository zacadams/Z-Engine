/**
 *	@file Z-Engine\Z-Engine\Interfaces\SpriteLib\AnimationManager.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2011 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _ANIMATIONMANAGER_H__Included_1568682598
#define _ANIMATIONMANAGER_H__Included_1568682598

#include "CoreLib/AssetManager.h"

namespace ZGE
{
	class CAnimationSequence;
	class ITexture;

	/**
	 * This class is responsible for the managment of animation sequences.
	 */	
	class CAnimationManager : public CAssetManager< CAnimationSequence >
	{
	public:
		CAnimationManager(void);
		~CAnimationManager(void);

		/**
		 * Creates a custom animation sequence.
		 * @param _rAssetId The animation sequences id.
		 * @param _rsInitialRect The initial texture rect.
		 *						 fX = the start U position, fY = the start V position
	     *						 fWidth = the width of the sprite frames, fHeight = the height of the sprite frames.
		 * @param _kuFrameCount The number of frames to generate.
		 * @param _pTexture The texture containing the animation sequence.
		 * @param _pAsset To be populated with the created asset.
		 * @return Success.
		 */
		bool CreateCustomAnimation( CAssetId& _rAssetId,
									const SFRect& _rsInitialRect,
									const uint32 _kuFrameCount,
									ITexture* _pTexture,
									CAnimationSequence*& _pAsset );

	protected:
		/**
		 *	Overriden to load animation from files.
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
	};
}

#endif //_ANIMATIONMANAGER_H__Included_1568682598

