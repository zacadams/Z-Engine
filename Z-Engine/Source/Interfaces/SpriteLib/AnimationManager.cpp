/**
 *	@file Z-Engine\Z-Engine\Interfaces\SpriteLib\AnimationManager.cpp
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2011 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/
#include "CoreLib/Core.h" 
#include "SpriteLib/AnimationSequence.h"
#include "RendererLib/Texture.h"
#include "SpriteLib/AnimationManager.h"

using namespace ZGE;
CAnimationManager::CAnimationManager(void)
{
   m_kpcManagerId = "Animated sprite manager";
}

CAnimationManager::~CAnimationManager(void)
{
}
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
bool CAnimationManager::CreateCustomAnimation( CAssetId& _rAssetId,
											   const SFRect& _rsInitialRect,
											   const uint32 _kuFrameCount,
											   ITexture* _pTexture,
											   CAnimationSequence*& _pAsset )
{

	// Check if the animation exists
	_pAsset = GetAssetById( _rAssetId );
	if( _pAsset )
	{
		_pAsset->AddRef( );
		return true;
	}

	// Create the animation sequence.
	_pAsset = new CAnimationSequence( );

	SFRect sRect = _rsInitialRect;
	const float32 kfTextureWidth = static_cast<float32>(_pTexture->GetWidth( ));

	// Create the frames.
	for( uint32 i = 0; i < _kuFrameCount; ++i )
	{
		// Create the frame
		CAnimationFrame Frame;
		Frame.SetTextureRect( sRect );

		// Check if we are at the end of the texture.
		if( ( sRect.m_fX + sRect.m_fWidth ) == kfTextureWidth )
		{
			// Yes move t the start and sown a line.
			sRect.m_fX = 0.0f;
			sRect.m_fY += sRect.m_fHeight;
		}
		else
		{
			// Not at the end, we can now increment the u coordinate.
			sRect.m_fX += sRect.m_fWidth;
		}
		// Add the frame to the sequence.
		_pAsset->AddAnimationFrame( Frame );
	}

	// Created the anmation, add it to the managers asset list.
	AddPreCreatedAsset( _rAssetId, _pAsset );
	// manualy increment the reference count.
	_pAsset->AddRef( );

	return true;
}

/**
 *	Overriden to load animation from files.
 *	Param _rAssetId : The assets id, ( could be the file name ).
 *	Param _pAsset   : To be populated with the loaded asset.
 *	Return : Success.
 */
bool CAnimationManager::LoadAssetImplementation( CAssetId& _rAssetId, tAsset*& _pAsset )
{
	UNUSED_VAR( _rAssetId );
	UNUSED_VAR( _pAsset );
	assert_now( "Unimplemented function!" );
	return false;
}

/**
 *	To be overidden to release a managers assets.
 *	Param _pAsset : The asset to release.
 *	Return : Success.
 */
bool CAnimationManager::ReleaseAsset( tAsset* _pAsset )
{
	delete reinterpret_cast< CAnimationSequence* >( _pAsset );
	_pAsset = NULL;
	return true;
}