/**
 *	@file Z-Engine\Z-Engine\Projects\Windows\Interfaces\InputLib\InputInterface.cpp
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - 2011 - Team Poly Gone. All Rights Reserved.
 *	
 *********************************************************************************************/
// Z-Engine includes
#include "CoreLib/Core.h"


//#ifdef Z_PLATFORM_WIN
//	// Windows platform, windows supports mouse and keyboard
//	#ifdef USING_MOUSE_INPUT
//		#include "DInputLib/DMouse.h"
//	#endif
//	#ifdef USING_KEYBOARD_INPUT
//		#include "DInputLib/KeyBoard.h"
//	#endif
//	// Create the mouse input
//#endif



// Library includes

// Local includes 
#include "InputLib/InputInterface.h"
using namespace ZGE;
CInputInterface::CInputInterface(void)
{
}

CInputInterface::~CInputInterface(void)
{
//	#ifdef Z_PLATFORM_WIN
//	// Windows platform, windows supports mouse and keyboard
//	#ifdef USING_MOUSE_INPUT
//			// Using mouse.
//	SafeDelete( m_pMouse );
//	#endif
//	#ifdef USING_KEYBOARD_INPUT
//	SafeDelete(	m_pKeyBoard );
//	#endif
//	// Create the mouse input
//#endif
}

// Initialises the input interface.
bool CInputInterface::Initialise( IKeyBoard* _pKeyBoard, IMouse* _pMouse  )
{
//	// Create the correct devices stated in the ZEngine defines.
//#ifdef Z_PLATFORM_WIN
//	// Windows platform, windows supports mouse and keyboard
//	#ifdef USING_MOUSE_INPUT
//			// Using mouse.
//			m_pMouse = new CDMouse( );
//	#endif
//	#ifdef USING_KEYBOARD_INPUT
//			m_pKeyBoard = new CKeyBoard( );
//	#endif
//	// Create the mouse input
//#endif

	m_pKeyBoard = _pKeyBoard;
	m_pMouse = _pMouse;

	return true;
}