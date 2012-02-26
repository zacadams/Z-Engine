/**
 *	@file Z-Engine\Z-Engine\Interfaces\SpriteLib\AnimationFrame.cpp
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2011 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/
#include "CoreLib/Core.h"
#include "CoreLib/Observer.h"
#include "SpriteLib/AnimationFrame.h"
using namespace ZGE;
CAnimationFrame::CAnimationFrame(void)
: m_fDuration( 1.0f ) // ! by default, this is so the animation controllers play back speed
					  // can determin the actual speed of this frame. i.e 1 * 0.5 = 0.5;
{
	// Initialise the texture rect.
	m_sTextureRect.m_fX = 0.0f;
	m_sTextureRect.m_fY = 0.0f;
	m_sTextureRect.m_fWidth = 0.0f;
	m_sTextureRect.m_fHeight = 0.0f;
}

CAnimationFrame::~CAnimationFrame(void)
{
	// The events are not allocated using new, so they do not
	// need to be deleted.
}

/**
 *	Registers an event onto the frame, this event wil be fired when the frame begins.
 *	@param _pEvent The event to be registered.
 *	@return Success.
 */
bool CAnimationFrame::RegisterBeginEvent( IEvent& _rEvent )
{
	// Make sure the event is not already registered.
	// We dont really need to do that, but it would be nice to know an event
	// is not being added multiple times.
#ifdef _DEBUG
	for( uint32 i = 0; i < m_vecBeginEvents.size( ); ++i )
	{
		if( _rEvent.m_uEventId == m_vecBeginEvents[i].m_uEventId )
		{
			assert_now( "Event already registered!" );
			return false; // return failure.
		}
	}
#endif
	m_vecBeginEvents.push_back( _rEvent );
	return true;
}
/**
 * Registers an event onto thr framne, this event will be fired when the frame ends.
 * @param _pEvent the event to register.
 * @return Success.
 */
bool CAnimationFrame::RegisterEndEvent( IEvent& _rEvent )
{
	// Make sure the event is not already registered.
	// We dont really need to do that, but it would be nice to know an event
	// is not being added multiple times.
#ifdef _DEBUG
	for( uint32 i = 0; i < m_vecEndEvents.size( ); ++i )
	{
		if( _rEvent.m_uEventId == m_vecEndEvents[i].m_uEventId )
		{
			assert_now( "Event already registered!" );
			return false; // return failure.
		}
	}
#endif
	m_vecEndEvents.push_back( _rEvent );
	return true;
}

// Begins the frame, this will fire any registered events. 
void CAnimationFrame::OnFrameBegin( IObserver* _pObserver )
{
	// Fire all registered events to the beginning of this frame.
	uint32 uEventCount = m_vecBeginEvents.size( );
	for( uint32 i = 0; i < uEventCount; ++i )
	{
		// Fire this event.
		_pObserver->OnEvent( &m_vecBeginEvents[i], m_vecBeginEvents[i].m_uEventId, /*Animation domain*/0 );
	}
}

// Ends the frame, this will fire any registered events.
void CAnimationFrame::OnFrameEnd( IObserver* _pObserver )
{
	// Fire all registered events to the end of this frame.
	uint32 uEventCount = m_vecEndEvents.size( );
	for( uint32 i = 0; i < uEventCount; ++i )
	{
		// Fire this event.
		_pObserver->OnEvent( &m_vecEndEvents[i], m_vecEndEvents[i].m_uEventId, /*Animation domain*/0 );
	}
}
