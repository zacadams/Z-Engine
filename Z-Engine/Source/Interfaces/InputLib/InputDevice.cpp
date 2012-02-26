/**
 *	@file Z-Engine\Z-Engine\Interfaces\InputLib\InputDevice.cpp
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2011 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/
#include "CoreLib/Core.h"
#include "InputLib/InputDevice.h"

using namespace ZGE;
IInputDevice::IInputDevice(void)
{
}

IInputDevice::~IInputDevice(void)
{
}

// Returns the input devices down state observer.
inline CInputChangeState& IInputDevice::GetDownStateObserver( )
{
	return m_DownStateObserver;
}

// Returns the input devices up state observer.
inline CInputChangeState& IInputDevice::GetUpStateObserver( )
{
	return m_UpStateObserver;
}

// returns the devices change state observer.
inline CInputChangeState& IInputDevice::GetChangeStateObserver( )
{
	return m_ChangeStateObserver;
}