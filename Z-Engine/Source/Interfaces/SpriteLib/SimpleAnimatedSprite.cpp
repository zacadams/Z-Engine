/**
 *	@file Z-Engine\Z-Engine\Interfaces\SpriteLib\AnimatedSprite.cpp
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/

// Z-Engine inludes
#include "CoreLib/Core.h"
#include "RendererLib/Texture.h"

#include "SpriteLib/Sprite.h"

#include "SpriteLib/SimpleAnimatedSprite.h"

using namespace ZGE;

CSimpleAnimatedSprite::CSimpleAnimatedSprite(void)
: m_pSprite			( NULL )			
, m_bLoopAnim			( false )
, m_bPingPongAnim		( false )
, m_bPlayingForward		( true )	
, m_fPlayBackSpeed		( 0.0f )	
, m_fTimeElapsed		( 0.0f )
, m_uFrameCount			( 0 )
, m_uCurrentFrame		( 0 )

{
}

CSimpleAnimatedSprite::~CSimpleAnimatedSprite(void)
{
	//SafeRelease( m_pSprite );
	SafeDelete( m_pSprite );
}
/*
* Initialises the animated sprite
* Param _kpSprite : The anim sprite.
*/
bool CSimpleAnimatedSprite::Initialise( CSprite* _pSprite, const uint32 _kuFrameCount  )
{
	m_pSprite = _pSprite;
	m_uFrameCount = _kuFrameCount;
	m_sInitialFrame = m_pSprite->GetTextureRect( );
	return true;
}
/*
* Sets the sprite to loop.
* Param _bLoop : True  -> Loops the animation,
*				 False -> Stops looping an animation
*/
void CSimpleAnimatedSprite::SetLoopState( bool _bLoop )
{
	m_bLoopAnim = _bLoop;
	m_bPingPongAnim = false;
}
/*
* Sets the animated sprite to ping pong.
* Ping pong -> When the anim is finished it playes it backwards and visa versa
* Param _bPingPong : True  -> Ping pongs the animation
*					 False -> Stops ping ponging the animation
*/
void CSimpleAnimatedSprite::SetPingPongState( bool _bPingPong )
{
	m_bPingPongAnim = _bPingPong;
	m_bLoopAnim = false;
}
/*
* Sets the play back speed of the animation
* Param _kfPlayBackSpeed : The play back speed to set
*/
void CSimpleAnimatedSprite::SetPlayBackSpeed( const float32 _kfPlayBackSpeed )
{
	m_fPlayBackSpeed = _kfPlayBackSpeed;
}
/*
* Updates the animated sprite
* Param _kfDeltaTick : The time elapsed since last frame
*/
void CSimpleAnimatedSprite::Update( const float32 _kfDeltaTick )
{
	if( m_bLoopAnim )
	{
		LoopAnim( _kfDeltaTick );
	}
	if( m_bPingPongAnim )
	{
		PingPongAnim( _kfDeltaTick );
	}
}
/*
* Processes looping the animation
*/
void CSimpleAnimatedSprite::LoopAnim( const float32 _kfDeltaTick )
{
	UNUSED_VAR( _kfDeltaTick );

	// Update the time elapsed
	m_fTimeElapsed += _kfDeltaTick;
	
	

	// Is it time to update the sprite?
	if( m_fTimeElapsed > m_fPlayBackSpeed )
	{
		m_uCurrentFrame++;
		if( m_uCurrentFrame == m_uFrameCount )
		{
			// Reset the anims frame
			m_pSprite->SetTextureRect( m_sInitialFrame );
			m_uCurrentFrame = 0;
			m_fTimeElapsed = 0.0f;
			return;
		}
		// Get the sprites texture rect
		SFRect sTexRect = m_pSprite->GetTextureRect( ); 
		
		// Are we on the last frame of a line?

		ITexture* pTexture = m_pSprite->GetTexture( );
		float32 fTexWidth  = static_cast< float32 >( pTexture->GetWidth( ) );
		//float32 fTexHeight = static_cast< float32 >( pTexture->GetHeight( ) );

		// Are we at the end of the texture 

		if( ( sTexRect.m_fX + sTexRect.m_fWidth ) >= fTexWidth )
		{
			sTexRect.m_fY += sTexRect.m_fHeight;
			sTexRect.m_fX = 0.0f;
		}
		else
		{
			sTexRect.m_fX += sTexRect.m_fWidth;
		}
		m_fTimeElapsed = 0.0f;

		m_pSprite->SetTextureRect( sTexRect );
	}
}
/*
* Processes ping ponging the animation
*/
void CSimpleAnimatedSprite::PingPongAnim( const float32 _kfDeltaTick )
{
		UNUSED_VAR( _kfDeltaTick );

	// Update the time elapsed
	m_fTimeElapsed += _kfDeltaTick;
	
	// Is it time to update the sprite?
	if( m_fTimeElapsed > m_fPlayBackSpeed )
	{
		m_bPlayingForward ? m_uCurrentFrame++ : m_uCurrentFrame--;	
		
		if( m_uCurrentFrame == m_uFrameCount )
		{
			// Reset the anims frame
			m_bPlayingForward = false;
			--m_uCurrentFrame;
		}
		if( m_uCurrentFrame == 0 )
		{
			m_bPlayingForward = true;
		}

		// Get the sprites texture rect
		SFRect sTexRect = m_pSprite->GetTextureRect( ); 
		
		// Are we on the last frame of a line?

		ITexture* pTexture = m_pSprite->GetTexture( );
		float32 fTexWidth  = static_cast< float32 >( pTexture->GetWidth( ) );
		//float32 fTexHeight = static_cast< float32 >( pTexture->GetHeight( ) );

		// Are we at the end of the texture 
		if( m_bPlayingForward )
		{
			if( ( sTexRect.m_fX + sTexRect.m_fWidth ) == fTexWidth )
			{
				sTexRect.m_fY += sTexRect.m_fHeight;
				sTexRect.m_fX = 0.0f;
			}
			else
			{
				sTexRect.m_fX += sTexRect.m_fWidth;
			}
		}
		else
		{
			if( ( sTexRect.m_fX /*- sTexRect.m_fWidth*/ ) == 0.0f )
			{
				sTexRect.m_fY -= sTexRect.m_fHeight;
				sTexRect.m_fX = fTexWidth - sTexRect.m_fWidth;
			}
			else
			{
				sTexRect.m_fX -= sTexRect.m_fWidth;
			}
		}
		m_pSprite->SetTextureRect( sTexRect );
		m_fTimeElapsed = 0.0f;


		
	}
}
/*
* Reteurn the animatedsprites sprite
*/ 
CSprite* CSimpleAnimatedSprite::GetSprite( ) const
{
	return m_pSprite;
}
/*
* Sets the current direction for the ping pong sprite
* Param _b : true  -> play the animation forward
*			 false -> play animation backwards
*/
void CSimpleAnimatedSprite::PlayAnimationForward( bool _b )
{
	m_bPlayingForward = _b;
}