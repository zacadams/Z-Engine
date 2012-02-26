/**
 *	@file Z-Engine\Z-Engine\Interfaces\InputLib\KeyBoard.cpp
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2011 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/
#include "CoreLib/Core.h"
#include "InputLib/KeyBoard.h"
using namespace ZGE;

IKeyBoard::IKeyBoard( )
{
	// Registers all keyboard state onto its state observers.

	uint32 uKeyState = KB_A;
	for( uint32 i = 0; i < KB_COUNT; ++i )
	{
		m_DownStateObserver.RegisterState( uKeyState ); 
		m_UpStateObserver.RegisterState( uKeyState ); 
		m_ChangeStateObserver.RegisterState( uKeyState++ ); 
	}
}

IKeyBoard::~IKeyBoard( )
{
}

