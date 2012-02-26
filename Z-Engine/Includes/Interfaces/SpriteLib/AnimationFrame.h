/**
 *	@file Z-Engine\Z-Engine\Interfaces\SpriteLib\AnimationFrame.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2011 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _ANIMATIONFRAME_H__Included_1344202921
#define _ANIMATIONFRAME_H__Included_1344202921

#include "CoreLib/Event.h"
#include <vector>

namespace ZGE
{
	class IEvent;

	/**
	 * This class represents a frame in an animation.
	 */
	class CAnimationFrame
	{
	public:
		CAnimationFrame(void);
		~CAnimationFrame(void);

		/**
		 *	Registers an event onto the frame, this event wil be fired when the frame begins.
		 *	@param _rEvent The event to be registered.
		 *	@return Success.
		 */
		bool RegisterBeginEvent( IEvent& _rEvent );
		/**
		 * Registers an event onto thr framne, this event will be fired when the frame ends.
		 * @param _rEvent the event to register.
		 * @return Success.
		 */
		bool RegisterEndEvent( IEvent& _rEvent );

		// Begins the frame, this will fire any registered events. 
		void OnFrameBegin( IObserver* _pObserver );

		// Ends the frame, this will fire any registered events.
		void OnFrameEnd( IObserver* _pObserver );

		// Retunrs the duration of the frame.
		inline float32 GetDuration( ) const { return m_fDuration; }

		// Returns the frames texture rect 
		inline const SFRect& GetTextureRect( ) { return m_sTextureRect ; }

		// Sets the frames texture rect.
		inline void SetTextureRect( const SFRect& _krRect ) { m_sTextureRect = _krRect; }

	protected:
		std::vector< IEvent > m_vecBeginEvents;//!< The events registered to be fired when the frame begins.
		std::vector< IEvent > m_vecEndEvents;	//!< The events regustered to be fired when the frame ends.	
		SFRect				   m_sTextureRect;	//!< The frames uv coordinates into its respective texture.
		float32				 m_fDuration;		//!< The duration of this frame.
	};
}

#endif //_ANIMATIONFRAME_H__Included_1344202921

