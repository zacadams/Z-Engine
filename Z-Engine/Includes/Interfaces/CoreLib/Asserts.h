/**
 *	@file Z-Engine\Z-Engine\Interfaces\CoreLib\Asserts.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _ASSERTS_H__Included_836796999
#define _ASSERTS_H__Included_836796999

#include "Z-Engine/ZPlatformDefines.h"
#ifdef Z_PLATFORM_WIN
	#include <windows.h>
	#include <cassert>
#endif
#include "TypeDefines.h"



namespace ZGE
{
	// Asserts 

	// Validations

	#define Validate(a) ( NULL != a ) //!< Returns if the pointer is valid
	#define Failed(a)   { false == a  } 
#define DEBUG_BREAK _asm{ int 3 }

#ifdef Z_PLATFORM_WIN
// Instantly throws an assertion
// Will assert the message when assert fires.
#define assert_now( message )\
{\
	uint32 uSelection = MessageBoxA( NULL, message, "assert!", MB_YESNOCANCEL | MB_ICONERROR );\
	switch( uSelection )\
	{\
	case IDYES:\
		{\
			DEBUG_BREAK;\
		}\
		break;\
	case IDNO:\
		{\
		}\
		break;\
	case IDCANCEL:\
		{\
		}\
	default:break;\
	}\
}

// Assets if the condition is false.
// Will assert the message when assert fires.
#define assert_msg( condition, message )\
{\
	if( condition )\
	{\
		uint32 uSelection = MessageBoxA( NULL, message, "assert!", IDYES | IDNO | IDCANCEL );\
		switch( uSelection )\
		{\
		case IDOK:\
			{\
				DEBUG_BREAK;\
			}\
			break;\
		case IDNO:\
			{\
			}\
			break;\
		case IDCANCEL:\
			{\
			}\
		default:break;\
		}\
	}\
}
#endif
}
#endif //_ASSERTS_H__Included_836796999

