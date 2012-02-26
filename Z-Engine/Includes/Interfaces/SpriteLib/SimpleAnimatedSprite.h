/**
 *	@file Z-Engine\Z-Engine\Interfaces\SpriteLib\AnimatedSprite.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _ANIMATEDSPRITE_H__Included_1620471589
#define _ANIMATEDSPRITE_H__Included_1620471589

#include "CoreLib/TypeDefines.h"

namespace ZGE
{
	class CSprite;

	/*
	* Represents an animated sprite.
	*/
	class CSimpleAnimatedSprite
	{
	public:
		CSimpleAnimatedSprite(void);
		~CSimpleAnimatedSprite(void);

		/*
		* Initialises the animated sprite
		* Param _kpSprite : The anim sprite.
		*/
		bool Initialise( CSprite* _pSprite, const uint32 _kuFrameCount );

		/*
		* Updates the animated sprite
		* Param _kfDeltaTick : The time elapsed since last frame
		*/
		void Update( const float32 _kfDeltaTick );

		/*
		* Sets the sprite to loop.
		* Param _bLoop : True  -> Loops the animation,
		*				 False -> Stops looping an animation
		*/
		void SetLoopState( bool _bLoop );

		/*
		* Sets the animated sprite to ping pong.
		* Ping pong -> When the anim is finished it playes it backwards and visa versa
		* Param _bPingPong : True  -> Ping pongs the animation
		*					 False -> Stops ping ponging the animation
		*/
		void SetPingPongState( bool _bPingPong );

		/*
		* Sets the play back speed of the animation
		* Param _kfPlayBackSpeed : The play back speed to set
		*/
		void SetPlayBackSpeed( const float32 _kfPlayBackSpeed );

		/*
		* Reteurn the animatedsprites sprite
		*/ 
		CSprite* GetSprite( ) const;

		/*
		* Sets the current direction for the ping pong sprite
		* Param _b : true  -> play the animation forward
		*			 false -> play animation backwards
		*/
		void PlayAnimationForward( bool _b );

	protected:

		/*
		* Processes looping the animation
		*/
		void LoopAnim( const float32 _kfDeltaTick );

		/*
		* Processes ping ponging the animation
		*/
		void PingPongAnim( const float32 _kfDeltaTick );

	protected:

		CSprite* m_pSprite;			//!< The sprite.
		bool	 m_bLoopAnim;		//!< Determins if the animation is looping
		bool     m_bPingPongAnim;	//!< Determins if the animation is ping ponging
		bool     m_bFinishedAnim;	//!< Dtermns if the animation is finished
		bool     m_bPlayingForward;	//!< Setermins if the animation is playing forward 
		bool	 m_bPlayingBackwards; //!< Determins if the animation is playing backward
		float32	 m_fPlayBackSpeed;	//!< The speed of the animation
		float32  m_fTimeElapsed;	//!< The time elapsed sinc ethe last framme change
		uint32	 m_uFrameCount;
		uint32   m_uCurrentFrame;
		SFRect   m_sInitialFrame;
	};
}

#endif //_ANIMATEDSPRITE_H__Included_1620471589

