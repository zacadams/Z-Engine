/**
 *	@file Z-Engine\Z-Engine\Interfaces\CoreLib\MemoryAlignment.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _MEMORYALIGNMENT_H__Included_1096243225
#define _MEMORYALIGNMENT_H__Included_1096243225


#ifndef _SONY_
# define _ALIGNED_PREFIX( x ) _declspec( align( x ) )
#else
// compilers for Sony don't do the above (different way perhaps).
#define _ALIGNED_PREFIX( x ) __attribute__ ( ( aligned( x ) ) )
# include <stddef.h>	// for size_t
#endif


namespace ZGE
{
	void*	AllocAligned( size_t NumBytes, size_t Alignment );
	void	FreeAligned( void* pMem );

	/**
	 *	Templated class to provide aligned new and delete operators.
	 *	Can be inherited for classes that require.
	 */
	template <int iAlignment> class TAligned
	{
	public:

		// Creates memory in an alignment
		void* operator new( size_t NumBytes )
		{
			return AllocAligned( NumBytes, iAlignment );
		}

		// Creates an array of memory in alignment
		void* operator new[]( size_t NumBytes )
		{
			return AllocAligned( NumBytes, iAlignment );
		}

		// Deletes aligned memory
		void operator delete( void* pMem )
		{
			FreeAligned( pMem );
		}

		// Deletes an aligned array in memoty
		void operator delete[]( void* pMem )
		{
			FreeAligned( pMem );
		}
	};

} // end namespace ZGE



#endif //_MEMORYALIGNMENT_H__Included_1096243225

