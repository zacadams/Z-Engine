/**
 *	@file Z-Engine\Z-Engine\Interfaces\SpriteLib\AnimationController.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2011 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _ANIMATIONCONTROLLER_H__Included_1557242827
#define _ANIMATIONCONTROLLER_H__Included_1557242827

#include "CoreLib/Observer.h"
#include <list>

namespace ZGE
{
	class CAnimationSequence;
	class CAnimationFrame;
	class IObserver;

	/**
	 * This class is responsible for playing back animations.
	 */
	class CAnimationController : public IObserver
	{
	public:
		CAnimationController(void);
		~CAnimationController(void);

		/**
		 * Initilaises the animation controller.
		 * @param _pAnimationSequence The animation sequence to play.
		 * @return Success.
		 */
		bool Initialise( CAnimationSequence* _pAnimationSequence );
		
		// Sets the animations play back modifier.
		inline void SetPlayBackSpeedModofier( const float32 _kfModifier ){ m_fPlayBacSpeedkModifier = _kfModifier; }

		// Sets the animations looping state.
		inline void SetLoopingState( const bool _b ){ m_bLoopAnimation = _b; }

		// Sets  the animations pause state.
		inline void SetPauseState( const bool _b ){  m_bPaused = _b; }

		// Updates the animation.
		bool Update( const float32 _kfTimeElapsed );

		// Returns the current frame.
		 CAnimationFrame& GetCurrentFrame( );

		 // Adds an observer to this animation.
		 bool AddObserver( IObserver* _pObserver );

		 // Removes an observer from the animation controller.
		 bool RemoveObserver( IObserver* _pObserver );

		 // Playes the animation
		 bool Play( CAnimationSequence* _pAnimation );

		 // Resets the animation controls states.
		 void Reset( );

		 		/**
		 * To be overridden by a derived class
		 */
		virtual void OnEvent( IEvent* _pEvent, const uint32 _kuMessage, const uint32 _kuEventDomain  );

	protected:
		CAnimationSequence* m_pAnimationSequence;	//!< The animation sequence to play.
		typedef std::list< IObserver* > ObserverList;
		ObserverList m_lObservers;					//!< Animation controllers observers.
		uint32	m_uCurrentFrame;					//!< The current frame index.
		float32	m_fTimeElapsed;						//!< The current time elapsed through the animation.
		float32	m_fFrameTimeElapsed;				//!< The time elpased from this frame.
		float32 m_fPlayBacSpeedkModifier;			//!< The play back speed modifier, used to speed up / slow down animation play back speeds.
		bool	m_bLoopAnimation;					//!< Determins if the animation is looping.
		bool	m_bPaused;							//!< Determins if the animation is paused.

	public:
		/**
		 * Animation events, these events are base animation playback events.
		 * i.e. to notify obervers when an animation begins and ends.
		 */
		enum EEvents
		{
			ANIM_BEGIN = 0, //<! Animation begin event.
			ANIM_END,		//!< Animation end event.
			ANIM_LOOPED,    //!< ANimation looped event.
		};

	};
}

#endif //_ANIMATIONCONTROLLER_H__Included_1557242827

