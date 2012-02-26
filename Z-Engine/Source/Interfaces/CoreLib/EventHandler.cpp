/**
 *	@file Z-Engine\Z-Engine\Interfaces\CoreLib\ObserverManager.cpp
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/
// Z-Engine includes
#include "CoreLib/Core.h"

// Library includes
#include "CoreLib/Observer.h"

// Local includes 
#include "CoreLib/Event.h"
#include "CoreLib/EventHandler.h"



using namespace ZGE;

IEventHandler::IEventHandler(void)
{
}

IEventHandler::~IEventHandler(void)
{
}

/**
 * To be implemented by an event handler instance
 * Param _pObserver : The observer to register to the event
 * Param _kuEvent   : The event id to register for
 * Return : Success
 */
bool IEventHandler::RegisterForEvent( IObserver* _pObserver, const uint32 _kuEvent )
{
	ObserverList& rList = m_ObserversMap[_kuEvent];
	rList.push_back( _pObserver );
	return true;
}

/**
 * Fires a triggered event to all observers
 */
void IEventHandler::FireEvent( IEvent* _pEvent, const uint32 _kuEventMessage )
{
	ObserverList& rList = m_ObserversMap[_kuEventMessage];
	ObserverList::iterator iter = rList.begin( );
	for( iter; iter != rList.end( ); ++iter )
	{
		(*iter)->OnEvent( _pEvent, _kuEventMessage, m_uEventDomain );
	}
}


