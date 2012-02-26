/**
 *	@file Z-Engine\Z-Engine\Interfaces\InputLib\InputChangeStates.cpp
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2011 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/
#include "CoreLib/Core.h"
#include "CoreLib/Observer.h"
#include "CoreLib/EventHandler.h"
#include "InputLib/InputChangeStates.h"
using namespace ZGE;
/**
 * Checks if the specified state is being observer.
 * @param _kustste The target state.
 * @return true if the key is being observed.
 */
bool CInputChangeState::IsStateObserved( const uint32 _kuState )
{
	// Find the state
	MapIter iter = m_mapObservers.find( _kuState );
	if( iter != m_mapObservers.end( ) )
	{
		// found the state.
		return m_mapObservers[_kuState].size( ) > 0;
	}
	//assert_now( "State is not being observerd!" );
	return false;
}
/**
 * Returms the obdervers to the specified state.
 * @param _kuState The target state.
 * @return The observers aobserving the specified state. 
 */
CInputChangeState::ObserverList* CInputChangeState::GetOberversToState( const uint32 _kuState )
{
	if( IsStateObserved( _kuState ) )
	{
		MapIter iter = m_mapObservers.find( _kuState );
		return &( iter->second );
	}
	assert_now( "Key does not exist!" );
	return NULL;
}
/**
 * Adds an observer to the specified state.
 * @param _kuState The target state.
 * @param _pObserver The observer to the state.
 * @return Success.
 */
bool CInputChangeState::RegisterObserverToState( IObserver* _pObserver, const uint32 _kuState )
{
	m_mapObservers[_kuState].push_back( _pObserver );
	return true;
}
/**
 * Removes an observer from a state.
 * @param _kuState the target state.
 * @param _pObserver The observer to remove.
 * @return Success.
 */
bool CInputChangeState::RemoveObserverFromState( IObserver* _pObserver, const uint32 _kuState )
{
	m_mapObservers[_kuState].remove( _pObserver );
	return false;
}
/**
 * Registers a key state in the map.
 */
bool CInputChangeState::RegisterState( const uint32 _kuState)
{
	// Check if the state alread exist.
	MapIter iter = m_mapObservers.find( _kuState );
	if( iter != m_mapObservers.end( ) )
	{
		// State already exists.
		assert_now( "State already exists!" );
		return false;
	}
	// Add the state.
	m_mapObservers[_kuState] = ObserverList( );
	return true;
}
/**
 * Fires an input state change event to its observers. 
 */
void CInputChangeState::FireStateChange( IEvent* _pEvent, uint32 _kuState )
{

	CInputEvent* pInputEvent = reinterpret_cast< CInputEvent* >( _pEvent );
	pInputEvent->m_eKeyState = m_eKeyState;

	ObserverIter iter = m_mapObservers[_kuState].begin( );
	for( iter; iter != m_mapObservers[_kuState].end( ); ++iter )
	{
		(*iter)->OnEvent( _pEvent, m_eKeyState, ED_INPUT );
	}
}


/**
 *	Sets the key state.
 */
void CInputChangeState::SetKeyState( const EKeyState _keKeyState )
{
	m_eKeyState = _keKeyState;
}
