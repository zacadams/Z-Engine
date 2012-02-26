/**
 *	@file Z-Engine\Z-Engine\Interfaces\SpriteLib\ComplexAnimatedSprite.cpp
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2011 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/
#include "CoreLib/Core.h"
#include "SpriteLib/Sprite.h"
#include "SpriteLib/AnimationFrame.h"
#include "SpriteLib/AnimatedSprite.h"
using namespace ZGE;
CAnimatedSprite::CAnimatedSprite(void)
{
}

CAnimatedSprite::~CAnimatedSprite(void)
{
	SafeDelete( m_pSprite );
}

/**
 * Initilaises the animated sprite.
 * @return Succes.	
 */
bool CAnimatedSprite::Initialise( CSprite* _pSprite )
{
	m_pSprite = _pSprite;
	return true;
}
/**
 * Adds an animation to the animated sprite, this function will generate an animation controller
 * from the supplied animation sequence.
 * @param _kpcAnimationId The animation name.
 * @param _rAnimationSequence The animation sequence to add.
 * @return Success.
 */
bool CAnimatedSprite::AddAnimation( const char8* _kpcAnimationId, CAnimationSequence* _pAnimationSequence )
{
	// Make sure the animation does not already exist.
	if( DoesAnimationExist( _kpcAnimationId ) )
	{
		// Animation allready exists.
		assert_now( "Animation allready exist!" );
		return false;
	}
	// Animation does not exist yet.
	m_mapAnimations[_kpcAnimationId] = _pAnimationSequence;
	return true;
}
/**
 * Makes the animated sprite play the sepcified animation.
 * @param _kpcAnimationId The animation to play.
 * @param _pAnimController To be populated with the controller to the playing animation controller.
 * @return Success.
 */
bool CAnimatedSprite::PlayAnimation( const char8* _kpcAnimationId, CAnimationController* _pAnimController )
{
	// Check if the animation exists.
	if( false == DoesAnimationExist( _kpcAnimationId ) )
	{
		// Animation does not exist.
		assert_now( "Animation does not exist!" );
		return false;
	}
	// Animation exists.
	//_pAnimController->Initialise( m_mapAnimations[_kpcAnimationId];
	_pAnimController->Play( m_mapAnimations[_kpcAnimationId] );
	return true;
}

// Checks if the target animation exist.
bool CAnimatedSprite::DoesAnimationExist( const char* _kpcAnimationId )
{
	// Make sure the animation does not already exist.
	AnimationMap::iterator iter;
	iter =m_mapAnimations.find( _kpcAnimationId );
	if( iter != m_mapAnimations.end( ) )
	{
		// Animation exists.
		return true;
	}
	// Does not exist
	return false;
}