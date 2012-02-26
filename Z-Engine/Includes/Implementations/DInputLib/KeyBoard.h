/**
 *	@file Z-Engine\Z-Engine\Includes\Implementations\DInputLib\KeyBoard.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2011 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _KEYBOARD_H__Included_508930233
#define _KEYBOARD_H__Included_508930233

#include "InputLib/KeyBoard.h"

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
				   					  
namespace ZGE
{
	class CKeyBoard : public IKeyBoard
	{
	public:
		CKeyBoard(void);
		~CKeyBoard(void);

		/**
		 * Updates the input device, this fire any registered events to imput states.
		 * @return Success.
		 */
		virtual bool Update( const float32 _kfDeltaTick );

	protected:
		LPDIRECTINPUTDEVICE8 m_pDIDevice;		//!< Pointer to the Direct Input Device.
		LPDIRECTINPUT8		 m_pDirectInput;	//!< Pointer to the instance of Direct Input.
		char8				 m_pPreviousKeyStates[256];
		char8                m_pCurrentKeyStates[256];
		bool				 m_bObserverdKeys[KB_COUNT];

	};
}

#endif //_KEYBOARD_H__Included_508930233

