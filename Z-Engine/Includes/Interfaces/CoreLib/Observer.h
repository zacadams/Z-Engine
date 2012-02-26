/**
 *	@file Z-Engine\Z-Engine\Interfaces\CoreLib\Observer.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _OBSERVER_H__Included_1256159925
#define _OBSERVER_H__Included_1256159925

namespace ZGE
{

class IEvent;
	/**
	 * Base interface to an observer
	 */
	class IObserver
	{
	public:
		IObserver(void);
		virtual ~IObserver(void);

		/**
		 * To be overridden by a derived class
		 */
		virtual void OnEvent( IEvent* _pEvent, const uint32 _kuMessage, const uint32 _kuEventDomain  ) = 0;

	protected:

	};
}

#endif //_OBSERVER_H__Included_1256159925

