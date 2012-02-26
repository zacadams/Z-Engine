/**
 *	@file Z-Engine\Z-Engine\Interfaces\SpriteLib\AnimationController.cpp
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2011 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/
#include "CoreLib/Core.h"
#include "CoreLib/Observer.h"
#include "SpriteLib/AnimationSequence.h"
#include "SpriteLib/AnimationController.h"
using namespace ZGE;
CAnimationController::CAnimationController(void)
: m_pAnimationSequence		( NULL )			
, m_uCurrentFrame			( 0 )				// start at frame 0.
, m_fTimeElapsed			( 0.0f )	
, m_fFrameTimeElapsed		( 0.0f )			
, m_fPlayBacSpeedkModifier	( 1.0f )			// default the speed modifier to 1.
, m_bLoopAnimation			( false )			// default to not looping.
, m_bPaused					( true )			// set the default pause state to true.
{
}

CAnimationController::~CAnimationController(void)
{
}
/**
 * Initilaises the animation controller.
 * @param _pAnimationSequence The animation sequence to play.
 * @return Success.
 */
bool CAnimationController::Initialise( CAnimationSequence* _pAnimationSequence )
{
	m_pAnimationSequence = _pAnimationSequence;
	return false;
}
// Updates the animation.
bool CAnimationController::Update( const float32 _kfTimeElapsed )
{
	if( m_bPaused )
	{
		return true;;
	}

	// Update the animation timer.
	m_fTimeElapsed += _kfTimeElapsed * m_fPlayBacSpeedkModifier;
	// Update the frame timer.
	m_fFrameTimeElapsed += _kfTimeElapsed * m_fPlayBacSpeedkModifier;

	// Check if we are at the end of the frame.
	if( m_fFrameTimeElapsed >= m_pAnimationSequence->GetAnimationFrame( m_uCurrentFrame ).GetDuration( ) )
	{
		// This frame is finished, go to the next frame.
		m_pAnimationSequence->GetAnimationFrame( m_uCurrentFrame ).OnFrameEnd( this );
		m_fFrameTimeElapsed = 0.0f;
		// Check if their is a next frame.
		if( m_uCurrentFrame == m_pAnimationSequence->GetFrameCount( ) -1 )
		{
			// We are at the end of the animation, do we loop?
			if( m_bLoopAnimation )
			{
				m_uCurrentFrame = 0;
				// Fire looped event to all observers.
				ObserverList::iterator iter = m_lObservers.begin( );
				for( iter; iter != m_lObservers.end( ); ++iter )
				{
					(*iter)->OnEvent( NULL, ANIM_LOOPED, 0 );
				}
			}
			else
			{
				m_bPaused =	true;
				// finished, stop the animation.
				// Fire finished event to all observers.
				ObserverList::iterator iter = m_lObservers.begin( );
				for( iter; iter != m_lObservers.end( ); ++iter )
				{
					(*iter)->OnEvent( NULL, ANIM_END, 0 );
				}
				
			}
			m_pAnimationSequence->GetAnimationFrame( m_uCurrentFrame ).OnFrameBegin( this );
		}
		else
		{
			++m_uCurrentFrame;
		}
	}

	return false;
}

// Returns the current frame.
CAnimationFrame& CAnimationController::GetCurrentFrame( )
{
	return m_pAnimationSequence->GetAnimationFrame( m_uCurrentFrame );
}
 // Adds an observer to this animation.
bool CAnimationController::AddObserver( IObserver* _pObserver ) 
{
	ObserverList::iterator iter = m_lObservers.begin( );
	for( iter; iter != m_lObservers.end( ); ++iter )
	{
		if( (*iter) == _pObserver )
		{
			// Observer allrady added.
			return false;
		}
	}
	m_lObservers.push_back( _pObserver );
	return true;
}

 // Removes an observer from the animation controller.
 bool CAnimationController::RemoveObserver( IObserver* _pObserver )
 {
	m_lObservers.remove( _pObserver );
	return false;
 }
 // Playes the animation
 bool CAnimationController::Play( CAnimationSequence* _pAnimation )
{
	m_pAnimationSequence->GetAnimationFrame( 0 ).OnFrameBegin( this );
	m_pAnimationSequence = _pAnimation;
	m_uCurrentFrame = 0;
	m_fTimeElapsed = 0.0f;
	m_fFrameTimeElapsed = 0.0f;
	m_bPaused = false;
	// notify observers that the animation is started.
	ObserverList::iterator iter = m_lObservers.begin( );
	for( iter; iter != m_lObservers.end( ); ++iter )
	{
		(*iter)->OnEvent( NULL, ANIM_BEGIN, 0 );
	}
	
	return NULL != m_pAnimationSequence;
}
 // Resets the animation controls states.
 void CAnimationController::Reset( )
 {
	m_uCurrentFrame = 0;
	m_fTimeElapsed = 0.0f;
	m_fFrameTimeElapsed = 0.0f;
	m_bPaused = true;
 }

 		/**
 * To be overridden by a derived class
 */
 void CAnimationController::OnEvent( IEvent* _pEvent, const uint32 _kuMessage, const uint32 _kuEventDomain  )
{
	// We only receive events from animation frames.
	ObserverList::iterator iter = m_lObservers.begin( );
	for( iter; iter != m_lObservers.end( ); ++iter )
	{
		(*iter)->OnEvent( _pEvent, _kuMessage, /*Animation domain*/0 );
	}
}