/**
 *	@file Z-Engine\Z-Engine\Interfaces\InputLib\KeyBoard.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _KEYBOARD_H__Included_1079438249
#define _KEYBOARD_H__Included_1079438249

#include "CoreLib/Event.h"
#include "InputLib/InputDevice.h"
#include "InputLib/InputStateDefines.h"


namespace ZGE
{

	/**
	 * 
	 */
	class IKeyBoard : public IInputDevice
	{
	public:
		IKeyBoard( );
		virtual ~IKeyBoard( );
		// Get
	};

}

#endif //_KEYBOARD_H__Included_1079438249

