/**
 *	@file Z-Engine\Z-Engine\Implementations\COLLADAModelParser\Source.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2011 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _SOURCE_H__Included_562893606
#define _SOURCE_H__Included_562893606

namespace ZGE
{
	/**
	 * Represents a vertex elemen source. i.e position, normals. uv.ect
	 */
	class CSource
	{
	public:
		CSource(void);
		~CSource(void);

		/**
		 * Copies data from the source into the destination.
		 * @param _pcDest The pointer topopulate with the data.
		 * @param _kuSourceIndex The start index to copy from.
		 * @return Success.
		 */
		bool MemCopy( unsigned char* _pcDest, const uint32 _kuSourceIndex );

	public:
		// Members made pupblic
		float32* m_pValues;	//!< The sources values.
		uint32	 m_uStride;	//!< The accessor stride into the stream.
		uint32	 m_uSourceCount;	//!< The number of values in the source.
	};
}// end namespace 

#endif //_SOURCE_H__Included_562893606

