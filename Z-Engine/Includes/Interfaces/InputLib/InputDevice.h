/**
 *	@file Z-Engine\Z-Engine\Interfaces\InputLib\InputDevice.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _INPUTDEVICE_H__Included_1997545381
#define _INPUTDEVICE_H__Included_1997545381

#include "InputLib/InputChangeStates.h"

namespace ZGE
{
	/*
	* Represents a input device
	*/
	class IInputDevice
	{
	public:
		IInputDevice(void);
		virtual ~IInputDevice(void);

		/**
		 * Updates the input device, this fire any registered events to imput states.
		 * @return Success.
		 */
		virtual bool Update( const float32 _kfDeltaTick ) = 0;

		// Returns the input devices down state observer.
		virtual CInputChangeState& GetDownStateObserver( );
		
		// Returns the input devices up state observer.
		virtual CInputChangeState& GetUpStateObserver( );

		// returns the devices change state observer.
		virtual CInputChangeState& GetChangeStateObserver( );
	protected:
		CInputChangeState m_DownStateObserver;
		CInputChangeState m_UpStateObserver;
		CInputChangeState m_ChangeStateObserver;
	};
}

#endif //_INPUTDEVICE_H__Included_1997545381

