/**
 *	@file Z-Engine\Z-Engine\Interfaces\CoreLib\ChangeState.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _CHANGESTATE_H__Included_204912972
#define _CHANGESTATE_H__Included_204912972

#include "CoreLib/zList.h"
#include "CoreLib/TypeDefines.h"

namespace ZGE
{
	class IObserver;

	/**
	 * The base class for an event
	 */
	class IEvent
	{
	public:
		IEvent(void);
		virtual ~IEvent(void);
	public:
		uint32	m_uEventId;	//!< The events Id.

	};
}

#endif //_CHANGESTATE_H__Included_204912972

