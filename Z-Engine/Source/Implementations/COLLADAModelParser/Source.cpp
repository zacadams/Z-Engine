/**
 *	@file Z-Engine\Z-Engine\Implementations\COLLADAModelParser\Source.cpp
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2011 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/

#include "CoreLib/Core.h"

#include "Source.h"

using namespace ZGE;
CSource::CSource(void)
: m_pValues( NULL )
, m_uStride( 0 )
, m_uSourceCount( 0 )
{
}

CSource::~CSource(void)
{
	SafeDeleteArray( m_pValues );
}

/**
 * Copies data from the source into the destination.
 * @param _pcDest The pointer topopulate with the data.
 * @param _kuSourceIndex The start index to copy from.
 * @return Success.
 */
bool CSource::MemCopy( unsigned char* _pcDest, const uint32 _kuSourceIndex )
{
	memcpy( _pcDest, &m_pValues[ _kuSourceIndex * m_uStride ], 4 * m_uStride );
	return false;
}
