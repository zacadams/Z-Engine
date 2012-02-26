/**
 *	@file Z-Engine\Z-Engine\Interfaces\CoreLib\MemoryAlignment.cpp
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/
// Z-Engine includes
#include "CoreLib/Core.h"
// Library includes

// Local includes 


#include "CoreLib/MemoryAlignment.h"

//#define WIN32_LEAN_AND_MEAN
//#include <windows.h>
#include <stdlib.h>

#ifdef _PSP_
#include <sysmem.h>
#endif 

#ifdef __GNUC__
# include <malloc.h>
#endif

void*	ZGE::AllocAligned( size_t NumBytes, size_t Alignment )
{
#ifndef _PSP_
	#ifndef __GNUC__
		return _aligned_malloc( NumBytes, Alignment );
	#else
		return memalign( Alignment, NumBytes );
	#endif
	// return _aligned_malloc( NumBytes, Alignment );
#else
	return memalign( Alignment, NumBytes );
	//return NULL;
#endif
}

void	ZGE::FreeAligned( void* pMem )
{
#ifndef _PSP_
	#ifndef __GNUC__
		return _aligned_free( pMem );
	#else
		return free( pMem );
	#endif
#else
	return free( pMem );
	//return _aligned_free( pMem );
#endif
}

