/**
 *	@file Z-Engine\Z-Engine\Projects\Windows\Interfaces\InputLib\InputInterface.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - 2011 - Team Poly Gone. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _INPUTINTERFACE_H__Included_1978576442
#define _INPUTINTERFACE_H__Included_1978576442

// NOTE: use define for what input is supported , i.e. #define USING_MOUSE_INPUT in the ZDefines header.

namespace ZGE
{
	class IMouse;
	class IKeyBoard;
	/**
	 *	
	 */
	class CInputInterface
	{
	public:
		CInputInterface(void);
		~CInputInterface(void);

		// Initialises the input interface.
		bool Initialise( IKeyBoard* _pKeyBoard, IMouse* _pMouse  );

		// Returns the mouse input device.
		inline IMouse* GetMouse( ){ return m_pMouse; }

		// Returns the keyboard input device.
		inline IKeyBoard* GetKeyBoard( ){ return m_pKeyBoard; };


	protected:
		IMouse*    m_pMouse;	//!< The input interfaces mouse device.
		IKeyBoard* m_pKeyBoard; //!< The input interfaces key board device.
	};
}

#endif //_INPUTINTERFACE_H__Included_1978576442

