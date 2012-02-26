/**
 *	@file Z-Engine\Z-Engine\Interfaces\CoreLib\ObserverManager.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _OBSERVERMANAGER_H__Included_1343100364
#define _OBSERVERMANAGER_H__Included_1343100364

#include <list>
#include <map>
#include "CoreLib/TypeDefines.h"

namespace ZGE
{
	class IObserver;
	class IEvent;

	/**
	 *	Enumeration for event domains.
	 */
	enum EEventDomain
	{
		ED_INPUT,
		ED_ANIMATION,
		ED_GUI,
		ED_COUNT,
	};

	/**
	 * Interface for an observer manager. 
	 */
	class IEventHandler
	{
	public:
		IEventHandler(void);
		virtual ~IEventHandler(void);

		/**
		 * To be implemented by an event handler instance
		 * Param _pObserver : The observer to register to the event
		 * Param _kuEvent   : The event id to register for
		 * Return : Success
		 */
		virtual bool RegisterForEvent( IObserver* _pObserver, const uint32 _kuEvent );

		/**
		 * Fires a triggered event to all observers
		 */
		void FireEvent( IEvent* _pEvent, const uint32 _kuEventMessage );

	protected:

		typedef std::list< IObserver* > ObserverList;			// Convienient typedef 
		typedef std::map< uint32, ObserverList > ObserverMap;	// Convienient typedef
		ObserverMap m_ObserversMap;	//!< The observer map.
		uint32 m_uEventDomain;
	};
}

#endif //_OBSERVERMANAGER_H__Included_1343100364
