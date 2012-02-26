/**
 *	@file Z-Engine\Z-Engine\Interfaces\InputLib\InputChangeStates.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2011 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _INPUTCHANGESTATES_H__Included_2049077528
#define _INPUTCHANGESTATES_H__Included_2049077528

#include <map>
#include <list>
#include "InputLib/InputStateDefines.h"

namespace ZGE
{
	class IObserver;
	class IEvent;

	// 
	class CInputChangeState
	{
	public:

		CInputChangeState( ){ }
		~CInputChangeState( ){ }

		typedef std::list< IObserver* > ObserverList;
		typedef ObserverList::iterator ObserverIter;

		/**
		 * Checks if the specified state is being observer.
		 * @param _kustste The target state.
		 * @return true if the key is being observed.
		 */
		bool IsStateObserved( const uint32 _kuState );
		/**
		 * Returms the obdervers to the specified state.
		 * @param _kuState The target state.
		 * @return The observers aobserving the specified state. 
		 */
		ObserverList* GetOberversToState( const uint32 _kuState );
		/**
		 * Adds an observer to the specified state.
		 * @param _kuState The target state.
		 * @param _pObserver The observer to the state.
		 * @return Success.
		 */
		bool RegisterObserverToState( IObserver* _pObserver, const uint32 _kuState );
		/**
		 * Removes an observer from a state.
		 * @param _kuState the target state.
		 * @param _pObserver The observer to remove.
		 * @return Success.
		 */
		bool RemoveObserverFromState( IObserver* _pObserver, const uint32 _kuState );
		/**
		 * Registers a key state in the map.
		 */
		bool RegisterState( const uint32 _kuState);
		/**
		 * Fires an input state change event to its observers. 
		 */
		void FireStateChange( IEvent* _pEvent, uint32 _kuState );

		/**
		 *	Sets the key state.
		 */
		void SetKeyState( const EKeyState _keKeyState );

	protected:
		
		typedef std::map< uint32, ObserverList > ObserverMap;
		typedef ObserverMap::iterator MapIter;
		ObserverMap m_mapObservers;

		EKeyState m_eKeyState; 
	};
}

#endif //_INPUTCHANGESTATES_H__Included_2049077528

