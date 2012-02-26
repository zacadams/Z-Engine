/**
 *	@file Z-Engine\Z-Engine\Interfaces\InputLib\Mouse.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2011 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _MOUSE_H__Included_1821464623
#define _MOUSE_H__Included_1821464623

#include "InputLib/InputDevice.h"
#include "InputLib/InputStateDefines.h"
#include "CoreLib/Event.h"
namespace ZGE
{
	/**
	 * This class represents a computer mouse.
	 */
	class IMouse : public IInputDevice
	{
	public:
		IMouse(void);
		~IMouse(void);

	};
}

#endif //_MOUSE_H__Included_1821464623

