/**
 *	@file Z-Engine\Z-Engine\Interfaces\CoreLib\TypeDefines.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _TYPEDEFINES_H__Included_1180008905
#define _TYPEDEFINES_H__Included_1180008905

namespace ZGE
{

	typedef unsigned int uint32;	// Unsigned 32 bit integer  
	typedef signed int sint32;		// Signed 32 bit integer
	typedef float float32;			// 32 bit real number 
	typedef double float64;			// 64 bit real number 
	typedef char char8;			// 8 bit number 
	typedef long sint64;
	typedef unsigned long uint64;
	#define null 0 

// structures

	struct SFRect
	{
		float32 m_fX;	  //!< The rectangles x coordinate.
		float32 m_fY;	  //!< The rectangles y coordinate.
		float32 m_fWidth; //!< The rectangles width.
		float32 m_fHeight;//!< The rectangles height.
	};
}

#endif //_TYPEDEFINES_H__Included_1180008905

