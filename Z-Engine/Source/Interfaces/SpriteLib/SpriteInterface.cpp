/**
 *	@file Z-Engine\Z-Engine\Projects\Windows\Interfaces\SpriteLib\SpriteInterface.cpp
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - 2011 - Team Poly Gone. All Rights Reserved.
 *	
 *********************************************************************************************/
// Z-Engine includes
#include "CoreLib/Core.h"
#include "SpriteLib/SpriteManager.h"
#include "SpriteLib/AnimatedSpriteManager.h"
#include "SpriteLib/AnimationManager.h"

// Library includes

// Local includes 
#include "SpriteLib/SpriteInterface.h"

using namespace ZGE;

// Initialises the sprite interface.
bool CSpriteInterface::InitialiseSpriteInterface( )
{
	CreateSpriteManager( );
	CreateAnimatedSpriteManager( );
	CreateAnimationManager( );
	return false;
}

// Deinitialises the sprite interface.
bool CSpriteInterface::DeinitilaiseSpriteInterface( )
{
	if( m_pSpriteManager )
	{
		delete m_pSpriteManager;
		m_pSpriteManager = NULL;
	}
	if( m_pAnimatedSpriteManager )
	{
		delete m_pAnimatedSpriteManager;
		m_pAnimatedSpriteManager = NULL;
	}
	if( m_pAnimationManager )
	{
		delete m_pAnimationManager;
		m_pAnimationManager = NULL;
	}
	return false;
}

// @return The sprite manager instance.
CSpriteManager* CSpriteInterface::GetSpriteManager( )
{
	return m_pSpriteManager;
}

//@return The animated sprite interface.
CAnimatedSpriteManager*  CSpriteInterface::GetAnimatedSpriteManager( )
{
	return m_pAnimatedSpriteManager;
}

//@return the sprite animation manager
CAnimationManager* CSpriteInterface::GetAnimationManager( )
{
	return m_pAnimationManager;
}

// Creates the sprite manager.
void CSpriteInterface::CreateSpriteManager( )
{
	if( NULL == m_pSpriteManager )
	{
		m_pSpriteManager = new CSpriteManager( );
		
		// Based on the platform defines crate he appropriate sprite parser.
	}
}

// Creates the animated sprite manager.
void CSpriteInterface::CreateAnimatedSpriteManager( )
{
	if( NULL == m_pAnimatedSpriteManager )
	{
		m_pAnimatedSpriteManager = new CAnimatedSpriteManager( );
		// Based on the platform defines crate he appropriate animated sprite parser.
	}
}

// Creates the animation manager.
void CSpriteInterface::CreateAnimationManager( )
{	
	if( NULL == m_pAnimationManager )
	{
		m_pAnimationManager = new CAnimationManager( );
		// Based on the platform defines crate he appropriate animation parser.
	}
}

void CSpriteInterface::SetSpriteParser( ISpriteParser* _pParser )
{
	m_pSpriteManager->SetSpriteParser( _pParser );
}