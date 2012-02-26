/**
 *	@file Z-Engine\Z-Engine\Implementations\DX9RendererLib\DX9IndexBuffer.cpp
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2011 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/
#include "CoreLib/Core.h"
#include "DX9RendererLib/DX9Renderer.h"
#include "DX9RendererLib/DX9IndexBuffer.h"
#include <d3dx9.h>

using namespace ZGE;

CDX9IndexBuffer::CDX9IndexBuffer(void)
: m_pDX9IndexBuffer( NULL )
{
}

CDX9IndexBuffer::~CDX9IndexBuffer(void)
{
	SafeRelease( m_pDX9IndexBuffer );
}


// Locks the index buffer for writing.
// _kuStart index The offset into the buffer to start from.
// _kuOffset The number of indices to lock from the start offset,
bool CDX9IndexBuffer::Lock( const uint32 _kuStartIndex, const uint32 _kuOffset, void*& _pIndices, bool _bReadOnly )
{
	DWORD dwUsage = _bReadOnly ? D3DLOCK_READONLY : 0;
	if( FAILED( m_pDX9IndexBuffer->Lock( _kuStartIndex, _kuOffset, &_pIndices, dwUsage ) ) )
	{
		assert_now( "Failed to lock the index buffer!" );
		return false;
	}
	return true;
}

// Unlocks the index buffer.
bool CDX9IndexBuffer::Unlock ( )
{
	if( FAILED( m_pDX9IndexBuffer->Unlock( ) ) )
	{
		assert_now( "Failed to unlock index buffer!" );
		return false;
	}
	return true;;
}

// Initialise 
bool CDX9IndexBuffer::Initialise( const uint32 _kuIndexCount, const EIndexType _keIndexType,  bool _bDynamic )
{
	m_uIndexCount = _kuIndexCount;
	m_eIndexType = _keIndexType;
	m_uSize = _kuIndexCount * ( _keIndexType == IT_32 ? 32 : 16 ); 

	// Usage
	DWORD dwUsage =  _bDynamic ? D3DUSAGE_DYNAMIC : D3DUSAGE_WRITEONLY;

	// static look up table for index types.
	D3DFORMAT pFormats[2] = 
	{
		D3DFMT_INDEX32,
		D3DFMT_INDEX16,
	};
	if( FAILED( CDX9Renderer::GetDevice( )->CreateIndexBuffer( m_uSize, dwUsage, pFormats[_keIndexType], D3DPOOL_DEFAULT, &m_pDX9IndexBuffer, NULL ) ) )
	{
		assert_now( "Failed to create index buffer!" );
		return false;
	}
	return true;
}

// Applies the index buffer onto the device.
bool CDX9IndexBuffer::Apply( )
{
	assert_msg( m_pDX9IndexBuffer, "IndexBuffer is not initialised!" );
	if( FAILED( CDX9Renderer::GetDevice( )->SetIndices( m_pDX9IndexBuffer ) ) )
	{
		assert_now( "Failed to set the indices om the device" );
		return false;
	}
	return true;
}